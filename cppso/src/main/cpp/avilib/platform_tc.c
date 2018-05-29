/*
 * platform_tc.c -- platform wrapper over libtc functions.
 * (C) 2007-2010 - Francesco Romani <fromani -at- gmail -dot- com>
 *
 * This file is part of transcode, a video stream processing tool.
 *
 * transcode is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * transcode is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "platform.h"

#include "libtc/xio.h"
#include "libtc/libtc.h"

#include <string.h>
#include <stdarg.h>
#include <errno.h>


int plat_open(const char *pathname, int flags, int mode)
{
    return xio_open(pathname, flags, mode);
}

int plat_close(int fd)
{
    return xio_close(fd);
}

ssize_t plat_read(int fd, void *buf, size_t count)
{
    return tc_pread(fd, buf, count);
}

ssize_t plat_write(int fd, const void *buf, size_t count)
{
    return tc_pwrite(fd, buf, count);
}

int64_t plat_seek(int fd, int64_t offset, int whence)
{
    return xio_lseek(fd, offset, whence);
}

int plat_ftruncate(int fd, int64_t length)
{
    return xio_ftruncate(fd, length);
}



void *_plat_malloc(const char *file, int line, size_t size)
{
    return _tc_malloc(file, line, size);
}

void *_plat_zalloc(const char *file, int line, size_t size)
{
    return _tc_zalloc(file, line, size);
}

void *_plat_realloc(const char *file, int line, void *ptr, size_t size)
{
    return _tc_realloc(file, line, ptr, size);
}

void plat_free(void *ptr)
{
    return tc_free(ptr);
}



int plat_log_open(void)
{
    return 0;
}

int plat_log_send(PlatLogLevel level,
                  const char *tag, const char *fmt, ...)
{
    static const TCLogLevel trans_tab[] = {
        TC_LOG_MSG,  /* PLAT_LOG_DEBUG   */
        TC_LOG_INFO, /* PLAT_LOG_INFO    */
        TC_LOG_WARN, /* PLAT_LOG_WARNING */
        TC_LOG_ERR,  /* PLAT_LOG_ERROR   */
    };
    char buffer[TC_BUF_MAX];
    va_list ap;

    va_start(ap, fmt);
    tc_vsnprintf(buffer, TC_BUF_MAX, fmt, ap);
    va_end(ap);

    return tc_log(trans_tab[level], tag, "%s", buffer);
}

int plat_log_close(void)
{
    return 0;
}

// EOF
