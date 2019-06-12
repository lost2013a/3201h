#ifndef __GXAV_JPEG_PROPERTYTYPES_H__
#define __GXAV_JPEG_PROPERTYTYPES_H__

#include "gxav_vpu_propertytypes.h"

typedef struct {
	void*          buffer;
	unsigned int   width;
	unsigned int   height;
	unsigned int   enable_interlace;
	GxColorFormat  dst_color;
} GxJpegProperty_Create;

typedef GxJpegProperty_Create GxJpegProperty_Destroy;

typedef struct {
	void          *frame_buffer_address;
	unsigned int   frame_buffer_size;
	void	       *display_buffer_address;
	unsigned int   display_buffer_size;
	unsigned int   mode;              // 0,normal mode; 1,clip mode;
	unsigned int   sof_pause;         // 0,no pause; 1,pause on sof;
	unsigned int   slice_pause;       // 0,no pause; 1,pause on slice;
	unsigned int   stride;            // stride
	unsigned int   clip_left;
	unsigned int   clip_upper;
	unsigned int   clip_right;
	unsigned int   clip_lower;
	unsigned int   max_width;         // max width
	unsigned int   max_height;        // max height
	unsigned int   resample_mode;     // 0, ; 1, ; 2, ; 3, ;
	unsigned int   resample_manual_h; // 0,off; 1,1/2 down sampling; 2,1/4 down sampling; 3,1/8 down sampling;
	unsigned int   resample_manual_v; // 0,off; 1,1/2 down sampling; 2,1/4 down sampling; 3,1/8 down sampling;
	GxColorFormat  dst_color;
	unsigned int   enable_interlace;
} GxJpegProperty_Config;

typedef struct {
	unsigned int original_width;
	unsigned int original_height;
	unsigned int width;
	unsigned int height;
	unsigned int source_format;
} GxJpegProperty_Info;

typedef struct{
	unsigned int state;

#define JPEGDEC_STOPED          (1<<0)
#define JPEGDEC_READY           (1<<1)
#define JPEGDEC_RUNNING         (1<<2)
#define JPEGDEC_SOF_OVER        (1<<3)
#define JPEGDEC_OVER            (1<<4)
#define JPEGDEC_ERROR           (1<<5)
#define JPEGDEC_UNSUPPORT       (1<<6)
#define JPEGDEC_BUSY            (1<<7)
#define JPEGDEC_ONE_FRAME       (1<<8)
#define JPEGDEC_DESTROYED       (1<<9)
}GxJpegProperty_State;

typedef struct{
	unsigned int status;
#define NOMAL                 (0)
#define STANDARD_UNSUPPORT    (1 << 0)
#define DECODER_OVER          (1 << 1)
#define DECODER_ERROR         (1 << 2)
#define DECODER_FRAME_ERROR   (1 << 3)
#define SOF_OVER	      (1 << 4)
} GxJpegProperty_Status;

typedef struct{
	unsigned int line_num;
} GxJpegProperty_Line;

#endif /* __GXAV_JPEG_PROPERTYTYPES_H__ */

