#ifndef __GXAV_VIDEO_PROPERTYTYPES_H__
#define __GXAV_VIDEO_PROPERTYTYPES_H__

typedef enum {
	CODEC_MPEG2V = 1,
	CODEC_MPEG4V,
	CODEC_H264,
	CODEC_H263,
	CODEC_AVSV,
	CODEC_RV,
	CODEC_RV_BITSTREAM,
	CODEC_HEVC,
	CODEC_YUV,
	CODEC_VC1,
	CODEC_MJPEG,
	CODEC_MAX,
}GxVideoDecoderProperty_Type;

struct mpeg2v_property {
	unsigned int  pts_insert;
};

#define DECODER_WORKBUF_SIZE (380*1024)
typedef struct {
	unsigned int    addr;
	unsigned int    size;
}DecoderWorkbufConfig;

typedef enum {
	VSYNC_FREE_RUN,
	VSYNC_NORNAL,
	VSYNC_SYNC_SLOWLY,
	VSYNC_SYNC_LATER,
} VSyncMode;

typedef VSyncMode GxVideoDecoderProperty_SyncMode;

typedef struct {
	GxVideoDecoderProperty_Type type;

	unsigned int pts_reorder;
	int          fps;
	VSyncMode    pts_sync;
	struct {
		unsigned int max_width;
		unsigned int max_height;
		unsigned int denoise_en;
	} deinterlace;
	struct {
		unsigned int enable;
		unsigned int length;
	} userdata;

	DecoderWorkbufConfig workbuf;
	unsigned int         mosaic_freez;
	unsigned int         err_gate;
} GxVideoDecoderProperty_Config;

typedef struct {
	unsigned int    addr;
	unsigned int    size;
} DecoderColbufConfig;

typedef struct {
	#define MAX_FB_NUM      (32)
	#define FREEZE_FB_ID    (0)
	unsigned int    fb_num;
	struct {
		unsigned int addr;
		unsigned int size;
	}fb[MAX_FB_NUM];
} DecoderFramebufConfig;

typedef struct {
	DecoderColbufConfig     colbuf;
	DecoderFramebufConfig   framebuf;
} GxVideoDecoderProperty_Run;

typedef struct {
	unsigned int	freeze;
} GxVideoDecoderProperty_Stop;

typedef struct {
	unsigned int frame_num;
} GxVideoDecoderProperty_Skip;

typedef enum {
	FAST_SPEED,            /* 快进 */
	SLOW_SPEED,            /* 慢放 */
	STEP_SPEED,            /* 快退 */
	NORMAL_SPEED,          /* 正常 */
}GxVideoDecoderProperty_SpeedMode;

typedef struct  {
	GxVideoDecoderProperty_SpeedMode mode;
} GxVideoDecoderProperty_Speed;

typedef enum {
	FRAMERATE_NONE     = 0,
	FRAMERATE_23976    = (1 << 0),
	FRAMERATE_24       = (1 << 1),
	FRAMERATE_25       = (1 << 2),
	FRAMERATE_29397    = (1 << 3),
	FRAMERATE_299      = (1 << 4),
	FRAMERATE_301      = (1 << 5),
	FRAMERATE_30       = (1 << 6),
	FRAMERATE_50       = (1 << 7),
	FRAMERATE_5994     = (1 << 8),
	FRAMERATE_60       = (1 << 9),
	FRAMERATE_RESERVE  = 0xFF
}GxVideoDecoderProperty_FrameRate;

typedef enum {
	ASPECTRATIO_NONE,
	ASPECTRATIO_1BY1,
	ASPECTRATIO_4BY3,
	ASPECTRATIO_14BY9,
	ASPECTRATIO_16BY9,
	ASPECTRATIO_221BY1,
	ASPECTRATIO_RESERVE
}GxVideoDecoderProperty_AspectRatio;

typedef enum {
	PROGRESSIVE,
	INTERLACE
}GxVideoDecoderProperty_ScanType;

typedef struct {
	unsigned int    width;
	unsigned int    height;

	unsigned int    fb_num;//means just play
	#define ZOOM_EXTRAL_FB_NUM          (3)//for zoom into smaller than 1/4 in I resolution or 1/8 in P resolution
	#define DEINTERLACE_EXTRAL_FB_NUM   (5)//for deinterlace, certainly can support zoom too
	unsigned int    fb_size;
	unsigned int    colbuf_size;

	GxAvFrameStat   stat;
	GxVideoDecoderProperty_ScanType    type;
	GxVideoDecoderProperty_FrameRate   rate;
	GxVideoDecoderProperty_AspectRatio ratio;
} GxVideoDecoderProperty_FrameInfo;

typedef struct {
	unsigned int pts;
} GxVideoDecoderProperty_PTS;

typedef enum {
	VIDEODEC_READY,
	VIDEODEC_RUNNING,
	VIDEODEC_PAUSED,
	VIDEODEC_STOPED,
	VIDEODEC_BUSY,
	VIDEODEC_OVER,
	VIDEODEC_ERROR,
} GxVcodecState;

typedef enum {
	VIDEODEC_ERR_NONE,
	VIDEODEC_ERR_ESV_OVERFLOW,
	VIDEODEC_ERR_SIZE_UNSUPPORT,
	VIDEODEC_ERR_SIZE_CHANGED,
	VIDEODEC_ERR_CODECTYPE_UNSUPPORT,
} GxVcodecErrCode;

typedef struct {
	GxVcodecState   state;
	GxVcodecErrCode err_code;
} GxVideoDecoderProperty_State;

typedef struct {
	GxVideoDecoderProperty_Type type;
	unsigned int min_width;
	unsigned int max_width;
	unsigned int min_height;
	unsigned int max_height;
	GxVideoDecoderProperty_FrameRate frame_rate;
} GxVideoDecoderProperty_Capability;

typedef enum {
	VIDEODEC_MODE_NORMAL = 1,
	VIDEODEC_MODE_IONLY  = 2,
	VIDEODEC_MODE_IPONLY = 3,
}DecodeMode;

typedef struct {
	DecodeMode dec_mode;
} GxVideoDecoderProperty_DecMode;

typedef struct {
	int offset_ms;
} GxVideoDecoderProperty_PtsOffset;

typedef struct {
    int value;
} GxVideoDecoderProperty_Tolerance;

typedef struct {
    int over;
} GxVideoDecoderProperty_OneFrameOver;

#endif

