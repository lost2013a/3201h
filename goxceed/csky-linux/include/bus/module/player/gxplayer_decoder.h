#ifndef __GXPLAYER_DECODER_H__
#define __GXPLAYER_DECODER_H__

typedef enum {
	AVCODEC_STOPPED = 0x1000000,
	AVCODEC_RUNNING,
	AVCODEC_PAUSED,
	AVCODEC_FINISHED,
	AVCODEC_UNSUPPORT,
	AVCODEC_BUSY,
	AVCODEC_ERROR,
	AVCODEC_READY,
} AVCodecState;

typedef enum {
	AVCODEC_ERR_NONE,
	AVCODEC_ERR_ESBUF_OVERFLOW,
	AVCODEC_ERR_CODECTYPE_UNSUPPORT,
	AVCODEC_ERR_SIZE_UNSUPPORT,//width or height, vcodec only
	AVCODEC_ERR_SIZE_CHANGED,//width or height change, vcodec only
} AVCodecErrcode;

typedef struct {
	AVCodecState   state;
	AVCodecErrcode err_code;
} AVCodecStatus;

typedef enum {
	VIDEO_CODEC_MPEG12  = (1 << 0),
	VIDEO_CODEC_MPEG4   = (1 << 1),
	VIDEO_CODEC_H263    = (1 << 2),
	VIDEO_CODEC_H264    = (1 << 3),
	VIDEO_CODEC_REAL    = (1 << 4),
	VIDEO_CODEC_AVS     = (1 << 5),
	VIDEO_CODEC_H265    = (1 << 6),
	VIDEO_CODEC_VC1     = (1 << 7),
	VIDEO_CODEC_MJPEG   = (1 << 8),
	VIDEO_CODEC_UNKNOWN = (0xFFFFFFFF),
} VideoCodecType;

typedef enum {
	AUDIO_CODEC_MPEG1     = (1 << 0),
	AUDIO_CODEC_MPEG2     = (1 << 1),
	AUDIO_CODEC_AAC_LATM  = (1 << 2),
	AUDIO_CODEC_AAC_ADTS  = (1 << 3),
	AUDIO_CODEC_OGG       = (1 << 4),
	AUDIO_CODEC_AC3       = (1 << 5),
	AUDIO_CODEC_AVS       = (1 << 6),
	AUDIO_CODEC_PCM       = (1 << 7),
	AUDIO_CODEC_EAC3      = (1 << 8),
	AUDIO_CODEC_DTS       = (1 << 9),
	AUDIO_CODEC_DRA1      = (1 << 10),
	AUDIO_CODEC_DTS_HD    = (1 << 11),
	AUDIO_CODEC_REAL      = (1 << 12),
	AUDIO_CODEC_RA_AAC    = (1 << 13),
	AUDIO_CODEC_RA_RA8LBR = (1 << 14),

	AUDIO_CODEC_UNKNOWN   = (0xFFFFFFFF),
} AudioCodecType;

#endif
