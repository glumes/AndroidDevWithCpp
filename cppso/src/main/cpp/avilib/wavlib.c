/*
 * wavlib.c - simple WAV I/O library interface
 * Copyright (C) 2006-2010 Francesco Romani <fromani at gmail dot com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "wavlib.h"
#include "platform.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
#include <stdlib.h>
#include <errno.h>

/*************************************************************************
 * utilties                                                              *
 *************************************************************************/

#define WAV_BUF_SIZE        (1024)

#if (!defined HAVE_BYTESWAP && defined WAV_BIG_ENDIAN)

static uint16_t bswap_16(uint16_t x)
{
    return (((x & 0xff00) >> 8) | ((x & 0x00ff) << 8));
}

static uint32_t bswap_32(uint32_t x)
{
    return (((x & 0xff000000UL) >> 24) |
            ((x & 0x00ff0000UL) >>  8) |
            ((x & 0x0000ff00UL) <<  8) |
            ((x & 0x000000ffUL) << 24));
}

static uint64_t bswap_64(uint64_t x)
{
    return (((x & 0xff00000000000000ULL) >> 56) |
            ((x & 0x00ff000000000000ULL) >> 40) |
            ((x & 0x0000ff0000000000ULL) >> 24) |
            ((x & 0x000000ff00000000ULL) >>  8) |
            ((x & 0x00000000ff000000ULL) <<  8) |
            ((x & 0x0000000000ff0000ULL) << 24) |
            ((x & 0x000000000000ff00ULL) << 40) |
            ((x & 0x00000000000000ffULL) << 56));
}
#endif

#if (!defined WAV_BIG_ENDIAN && !defined WAV_LITTLE_ENDIAN)
#error "you must define either LITTLE_ENDIAN or BIG_ENDIAN"
#endif

#if (defined WAV_BIG_ENDIAN && defined WAV_LITTLE_ENDIAN)
#error "you CAN'T define BOTH LITTLE_ENDIAN and BIG_ENDIAN"
#endif

#if defined WAV_BIG_ENDIAN
#define htol_16(x) bswap_16(x)
#define htol_32(x) bswap_32(x)
#define htol_64(x) bswap_64(x)

#elif defined WAV_LITTLE_ENDIAN

#define htol_16(x) (x)
#define htol_32(x) (x)
#define htol_64(x) (x)

#endif

/* often used out-of-order */
#define make_wav_get_bits(s) \
static inline uint##s##_t wav_get_bits##s(uint8_t *d) \
{ \
    return htol_##s(*((uint##s##_t*)d)); \
}

/* often used sequentially */
#define make_wav_put_bits(s) \
static inline uint8_t *wav_put_bits##s(uint8_t *d, uint##s##_t u) \
{ \
    *((uint##s##_t*)d) = htol_##s(u); \
    return (d + (s / 8)); \
}

make_wav_get_bits(16)
make_wav_get_bits(32)
make_wav_get_bits(64)

make_wav_put_bits(16)
make_wav_put_bits(32)
make_wav_put_bits(64)

static inline uint32_t make_tag(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    return (a | (b << 8) | (c << 16) | (d << 24));
}

/*************************************************************************
 * header data                                                           *
 *************************************************************************/

/*
 * WAVE header:
 *
 * TAG: 'RIFF'  4   bytes
 * LENGTH:      4   bytes
 * TAG: 'WAVE'  4   bytes
 *
 * TAG: 'fmt '  4   bytes
 * LENGTH:      4   bytes
 *
 *                        +
 * FORMAT:      2   bytes |
 * CHANNELS:    2   bytes |
 * SAMPLES:     4   bytes | simple WAV format:
 * AVGBYTES:    4   bytes | 16 byte
 * BLKALIGN:    2   bytes |
 * BITS:        2   bytes |
 *                        +
 *
 * TAG: 'data'  4   bytes
 * LENGTH:      4   bytes
 *
 * ----------------------------
 * TOTAL wav header: 44 bytes
 */

#define WAV_HEADER_LEN      (44)
#define WAV_FORMAT_LEN      (16)

#define PCM_ID              (0x1)

/*************************************************************************
 * core data/routines                                                    *
 *************************************************************************/

#define WAV_SET_ERROR(errp, code) \
        if (errp != NULL) { \
            *errp = code; \
        }

struct wav_ {
    int fd;

    int header_done;
    int close_fd;
    int has_pipe;

    WAVMode mode;
    WAVError error;

    uint32_t len;

    uint32_t bitrate;
    uint16_t bits;
    uint16_t channels;
    uint32_t rate;

    uint16_t block_align;
};

const char *wav_strerror(WAVError err)
{
    const char *s = NULL;

    switch (err) {
      case WAV_SUCCESS:
        s = "no error";
        break;
      case WAV_NO_MEM:
        s = "can't acquire the needed amount of memory";
        break;
      case WAV_IO_ERROR:
        s = "error while performing I/O operation";
        break;
      case WAV_BAD_FORMAT:
        s = "incorrect/unrecognized WAV data";
        break;
      case WAV_BAD_PARAM:
        s = "bad/unknown parameter for this operation";
        break;
      case WAV_UNSUPPORTED:
        s = "not yet supported by wavlib";
        break;
      default:
        s = NULL;
        break;
    }
    return s;
}

static int wav_parse_header(WAV handle, WAVError *err)
{
    uint8_t hdr[WAV_HEADER_LEN];
    ssize_t r = 0;
    uint16_t wav_fmt = 0;
    uint32_t fmt_len = 0;

    if (!handle || handle->fd == -1 || !(handle->mode & WAV_READ)) {
        return -1;
    }

    r = plat_read(handle->fd, hdr, WAV_HEADER_LEN);
    if (r != WAV_HEADER_LEN) {
        WAV_SET_ERROR(err, WAV_BAD_FORMAT);
        goto bad_wav;
    }
    if ((wav_get_bits32(hdr) != make_tag('R', 'I', 'F', 'F'))
     || (wav_get_bits32(hdr + 8) != make_tag('W', 'A', 'V', 'E'))
     || (wav_get_bits32(hdr + 12) != make_tag('f', 'm', 't', ' '))) {
        WAV_SET_ERROR(err, WAV_BAD_FORMAT);
        goto bad_wav;
    }

    fmt_len = wav_get_bits32(hdr + 16);
    wav_fmt = wav_get_bits16(hdr + 20);
    if (fmt_len != WAV_FORMAT_LEN || wav_fmt != PCM_ID) {
        WAV_SET_ERROR(err, WAV_UNSUPPORTED);
        goto bad_wav;
    }

    handle->len = wav_get_bits32(hdr + 4);
    handle->channels = wav_get_bits16(hdr + 22);
    handle->rate = wav_get_bits32(hdr + 24);
    handle->bitrate = (wav_get_bits32(hdr + 28) * 8) / 1000;
    handle->block_align = wav_get_bits16(hdr + 32);
    handle->bits = wav_get_bits16(hdr + 34);
    /* skip 'data' tag (4 bytes) */
    handle->len = wav_get_bits32(hdr + 40);

    return 0;

bad_wav:
    lseek(handle->fd, 0, SEEK_SET);
    return 1;
}

int wav_write_header(WAV handle, int force)
{
    uint8_t hdr[WAV_HEADER_LEN];
    uint8_t *ph = hdr;
    off_t pos = 0, ret = 0;
    ssize_t w = 0;

    if (!handle) {
        return -1;
    }
    if (!force && handle->header_done) {
        return 0;
    }
    if (handle->bits != 0
      && (handle->bits != 8 && handle->bits != 16)) {
        /* bits == 0 -> not specified (so it's good) */
        WAV_SET_ERROR(&(handle->error), WAV_UNSUPPORTED);
        return -1;
    }

    if (!handle->has_pipe) {
        pos = lseek(handle->fd, 0, SEEK_CUR);
        ret = lseek(handle->fd, 0, SEEK_SET);
        if (ret == (off_t)-1) {
            return 1;
        }
    }
        
    ph = wav_put_bits32(ph, make_tag('R', 'I', 'F', 'F'));
    ph = wav_put_bits32(ph, handle->len + WAV_HEADER_LEN - 8);
    ph = wav_put_bits32(ph, make_tag('W', 'A', 'V', 'E'));

    ph = wav_put_bits32(ph, make_tag('f', 'm', 't', ' '));
    ph = wav_put_bits32(ph, WAV_FORMAT_LEN);

    /* format */
    ph = wav_put_bits16(ph, PCM_ID);
    /* wave format, only plain PCM supported, yet */
    ph = wav_put_bits16(ph, handle->channels);
    /* number of channels */
    ph = wav_put_bits32(ph, handle->rate);
    /* sample rate */
    ph = wav_put_bits32(ph, (handle->bitrate * 1000)/8);
    /* average bytes per second (aka bitrate) */
    ph = wav_put_bits16(ph, ((handle->channels * handle->bits) / 8));
    /* block alignment */
    ph = wav_put_bits16(ph, handle->bits);
    /* bits for sample */

    ph = wav_put_bits32(ph, make_tag('d', 'a', 't', 'a'));
    ph = wav_put_bits32(ph, handle->len);

    w = plat_write(handle->fd, hdr, WAV_HEADER_LEN);

    if (!handle->has_pipe) {
        ret = lseek(handle->fd, pos, SEEK_CUR);
        if (ret == (off_t)-1) {
            return 1;
        }
    }

    if (w != WAV_HEADER_LEN) {
        return 2;
    }
    handle->header_done = 1;
    return 0;
}

WAV wav_open(const char *filename, WAVMode mode, WAVError *err)
{
    int oflags = (mode & WAV_READ) ?O_RDONLY :O_TRUNC|O_CREAT|O_WRONLY;
    int fd = -1;
    WAV wav = NULL;

    if (!filename || !strlen(filename)) {
        WAV_SET_ERROR(err, WAV_BAD_PARAM);
    } else {
        fd = plat_open(filename, oflags,
                       S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
        wav = wav_fdopen(fd, mode, err);
        if (!wav) {
            plat_close(fd);
        } else {
            wav->close_fd = 1;
        }
    }
    return wav;
}

#define DEL_WAV(wav) do { \
    plat_free((wav)); \
    (wav) = NULL; \
} while (0)

WAV wav_fdopen(int fd, WAVMode mode, WAVError *err)
{
    WAV wav = plat_zalloc(sizeof(struct wav_));

    if (!wav) {
        WAV_SET_ERROR(err, WAV_NO_MEM);
    } else {
        wav->fd = fd;
        wav->mode = mode;
        wav->close_fd = 0;
        wav->has_pipe = (mode & WAV_PIPE) ?1 :0;

        if (mode & WAV_READ) {
            if (0 != wav_parse_header(wav, err)) {
                DEL_WAV(wav);
            } else {
                wav->header_done = 1; /* skip write_header */
            }
        } else if (mode & WAV_WRITE) {
            /* reserve space for header by writing a fake one */
            if (!wav->has_pipe && 0 != wav_write_header(wav, 1)) {
                WAV_SET_ERROR(err, wav->error);
                /* only I/O error */
                DEL_WAV(wav);
            }
        } else {
            WAV_SET_ERROR(err, WAV_BAD_PARAM);
            DEL_WAV(wav);
        }
    }
    return wav;
}


#define RETURN_IF_IOERROR(err) \
    if (err != 0) { \
        WAV_SET_ERROR(&(handle->error), WAV_IO_ERROR); \
        return -1; \
    }

int wav_close(WAV handle)
{
    int ret = 0;

    if (!handle) {
        return -1;
    }

    if (!handle->has_pipe && handle->mode & WAV_WRITE) {
        ret = wav_write_header(handle, 1);
        RETURN_IF_IOERROR(ret);
    }

    if (handle->close_fd) {
        ret = plat_close(handle->fd);
        RETURN_IF_IOERROR(ret);
    }
    plat_free(handle);

    return 0;
}

#undef RETURN_IF_IOERROR

uint32_t wav_chunk_size(WAV handle, double fps)
{
    uint32_t size = 0;
    double fch;

    if (!handle || !fps) {
        return -1;
    }

    fch = handle->rate / fps;

    /* bytes per audio frame */
    size = (int)(fch * (handle->bits / 8) * handle->channels);
    size = (size>>2)<<2; /* XXX */

    return 0;
}

WAVError wav_last_error(WAV handle)
{
    return (handle) ?(handle->error) :WAV_BAD_PARAM;
}

uint32_t wav_get_bitrate(WAV handle)
{
    return (handle) ?(handle->bitrate) :0;
}

uint16_t wav_get_rate(WAV handle)
{
    return (handle) ?(handle->rate) :0;
}

uint8_t wav_get_channels(WAV handle)
{
    return (handle) ?(handle->channels) :0;
}

uint8_t wav_get_bits(WAV handle)
{
    return (handle) ?(handle->bits) :0;
}

void wav_set_rate(WAV handle, uint16_t rate)
{
    if (handle && handle->mode & WAV_WRITE) {
        handle->rate = rate;
    }
}

void wav_set_channels(WAV handle, uint8_t channels)
{
    if (handle && handle->mode & WAV_WRITE) {
        handle->channels = channels;
    }
}

void wav_set_bits(WAV handle, uint8_t bits)
{
    if (handle && handle->mode & WAV_WRITE) {
        handle->bits = bits;
    }
}

void wav_set_bitrate(WAV handle, uint32_t bitrate)
{
    if (handle && handle->mode & WAV_WRITE) {
        handle->bitrate = bitrate;
    }
}

#ifdef WAV_BIG_ENDIAN

/* assume dlen % 2 == 0 */
static void bswap_buffer(void *data, size_t bytes)
{
    size_t i = 0;
    uint16_t *ptr = data;
    
    for (ptr = data, i = 0; i < bytes; ptr++, i += 2) {
        *ptr = bswap_16(*ptr);
    }
}

#define SWAP_WRITE_CHUNK(data, len) do {       \
        memcpy(conv_buf, (data), (len));       \
        bswap_buffer(conv_buf, (len));         \
        ret = plat_write(fd, conv_buf, (len)); \
} while (0)

static ssize_t wav_bswap_fdwrite(int fd, const uint8_t *buf, size_t len)
{
    uint8_t conv_buf[WAV_BUF_SIZE];
    size_t blocks = len / WAV_BUF_SIZE, rest = len % WAV_BUF_SIZE, i = 0;
    ssize_t ret = 0, tot = 0;

    for (i = 0; i < blocks; i++) {
        SWAP_WRITE_CHUNK(buf + (i * WAV_BUF_SIZE), WAV_BUF_SIZE);
        if (ret != WAV_BUF_SIZE) {
            break;
        }
        tot += ret;
    }

    SWAP_WRITE_CHUNK(buf + (i * WAV_BUF_SIZE), rest);
    return tot + ret;
}

#undef SWAP_WRITE_CHUNK

#endif /* WAV_BIG_ENDIAN */

ssize_t wav_read_data(WAV handle, uint8_t *buffer, size_t bufsize)
{
    ssize_t r = 0;

    if (!handle) {
        return -1;
    }
    if (!buffer || bufsize < 0) {
        WAV_SET_ERROR(&(handle->error), WAV_BAD_PARAM);
        return -1;
    }
    if (!(handle->mode & WAV_READ) || (bufsize % 2 != 0)) {
        WAV_SET_ERROR(&(handle->error), WAV_UNSUPPORTED);
        return -1;
    }
    r = plat_read(handle->fd, buffer, bufsize);

#ifdef WAV_BIG_ENDIAN
    bswap_buffer(buffer, r);
#endif
    return r;
}

ssize_t wav_write_data(WAV handle, const uint8_t *buffer, size_t bufsize)
{
    ssize_t w = 0;

    if (!handle) {
        return -1;
    }
    if (!buffer || bufsize < 0) {
        WAV_SET_ERROR(&(handle->error), WAV_BAD_PARAM);
        return -1;
    }
    if (!(handle->mode & WAV_WRITE) || (bufsize % 2 != 0)) {
        WAV_SET_ERROR(&(handle->error), WAV_UNSUPPORTED);
        return -1;
    }
    if (wav_write_header(handle, 0) != 0) {
        return -1;
    }
#ifdef WAV_BIG_ENDIAN
    w = wav_bswap_fdwrite(handle->fd, buffer, bufsize);
#else
    w = plat_write(handle->fd, buffer, bufsize);
#endif
    if (w == bufsize) {
        handle->len += w;
    }
    return w;
}

