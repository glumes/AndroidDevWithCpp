
#ifndef _STATIC_WAVLIB_H_
#define _STATIC_WAVLIB_H_

#include "avilib/wavlib.h"
void dummy_wavlib(void);
void dummy_wavlib(void) {
        WAV wav = NULL;
        WAVError err;

        wav = wav_open(NULL, WAV_READ, &err);
        wav_close(wav);
}

#endif // _STATIC_WAVLIB_H_
