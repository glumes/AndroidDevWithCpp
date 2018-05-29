
#ifndef _STATIC_AVILIB_H_
#define _STATIC_AVILIB_H_

#include "avilib/avilib.h"
void dummy_avilib(void);
void dummy_avilib(void) {
	avi_t *infile = NULL;
	avi_t *outfile = NULL;
	infile = AVI_open_input_file((char *)NULL, 1);
	outfile = AVI_open_output_file((char *)NULL);
	AVI_set_audio_track(outfile, 0);
	AVI_set_audio(outfile, 0, 0, 0, 0, 0);
	AVI_set_audio_vbr(outfile, 0);
	AVI_set_video(outfile, 0, 0, 0.0, NULL);
	AVI_dump((char *)NULL, 0);
	AVI_write_frame(outfile, NULL, 0, 0);
	AVI_write_audio(outfile, NULL, 0);
	AVI_bytes_written(outfile);
	AVI_max_size();
	AVI_strerror();
	AVI_close(infile);
	AVI_close(outfile);
}

#endif // _STATIC_AVILIB_H_
