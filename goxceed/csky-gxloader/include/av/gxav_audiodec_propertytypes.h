#ifndef __GXAV_AUDIODEC_PROPERTYTYPES_H__
#define __GXAV_AUDIODEC_PROPERTYTYPES_H__

#include "gxav_common.h"

typedef  enum {
	CODEC_MPEG12A = 1,
	CODEC_AVSA,
	CODEC_AC3,
	CODEC_EAC3,
	CODEC_RA_AAC,
	CODEC_RA_RA8LBR,
	CODEC_DRA,
	CODEC_MPEG4_AAC,
	CODEC_WMA,
	CODEC_OGG,
	CODEC_PCM,
	CODEC_DTS,
} GxAudioDecProperty_Type;

typedef enum{
	DECODE_MODE = (1<<0),
	BYPASS_MODE = (1<<1)
} GxAudioDecProperty_Mode;

typedef enum {
	AUDIO_TO_AVOUT  = 0,
	AUDIO_TO_MEMORY,
}GxAudioDecProperty_Sink;

struct real_property {
	unsigned char header[2048];
	unsigned int  header_size;
};

struct mpeg4_aac_property {
	unsigned int  format;
#define LATM_FORMAT 0
#define ADTS_FORMAT 1
	unsigned char header[2048];
	unsigned int  header_size;
};

struct dolby_property {
	int header[100];
	unsigned int header_size;
};

typedef struct {
	GxAudioDecProperty_Type type;
	GxAudioDecProperty_Mode mode;
	GxAudioDecProperty_Sink sink;
	union {
		struct real_property      real;
		struct mpeg4_aac_property mpeg4_aac;
		struct dolby_property     dolby;
	} u;
	unsigned int audioout_id;
    unsigned int down_mix;
	unsigned int anti_error_code;
#define OR_WORK_BUFFER_SIZE (0x124000)
	void* ormem_start;
	unsigned int ormem_size;
} GxAudioDecProperty_Config;

typedef struct {
	GxAvAudioDataType outdata_type;
} GxAudioDecProperty_OutInfo;

typedef enum {
	STEREO       = (1 << 0),
	JOINT_STEREO = (1 << 1),
	DUAL         = (1 << 2),
	SIGLE        = (1 << 3),
	AC3_5_1      = (1 << 4),
	THREE        = (1 << 5),
	FOUR         = (1 << 6),
	FIVE         = (1 << 7),
	SIX          = (1 << 8),
	SEVEN        = (1 << 9),
	EIGHT        = (1 << 10),
} GxAudioDecProperty_Channel;

typedef enum {
	SAMPLEFRE_44KDOT1HZ   = (1 << 0),
	SAMPLEFRE_48KHZ       = (1 << 1),
	SAMPLEFRE_32KHZ       = (1 << 2),
	SAMPLEFRE_22KDOT05HZ  = (1 << 3),
	SAMPLEFRE_24KHZ       = (1 << 4),
	SAMPLEFRE_96KHZ       = (1 << 5),
	SAMPLEFRE_16KHZ       = (1 << 6),
	SAMPLEFRE_12KHZ       = (1 << 7),
	SAMPLEFRE_11KDOT025HZ = (1 << 8),
	SAMPLEFRE_9KDOT6HZ    = (1 << 9),
	SAMPLEFRE_8KHZ        = (1 << 10)
}GxAudioDecProperty_SampleFre;

typedef struct {
	unsigned int               bitrate;
	unsigned int               samplefre;
	GxAudioDecProperty_Channel channel;
} GxAudioDecProperty_FrameInfo;

typedef struct{
	unsigned int pts;
} GxAudioDecProperty_Pts;

typedef enum{
	AUDIODEC_INITED,
	AUDIODEC_READY,
	AUDIODEC_RUNNING,
	AUDIODEC_PAUSED,
	AUDIODEC_STOPED,
	AUDIODEC_ERROR,
	AUDIODEC_OVER
}GxAcodecState;

typedef enum{
	AUDIODEC_ERR_NONE,
	AUDIODEC_ERR_ESA_OVERFLOW,
	AUDIODEC_ERR_UNSUPPORT_CODECTYPE
}GxAcodecErrCode;

typedef struct{
	GxAcodecState state;
	GxAcodecErrCode err_code;
}GxAudioDecProperty_State;

typedef struct {
	unsigned int err_no;
#define STREAM_UNSUPPORT    (1 << 0)
} GxAudioDecProperty_Errno;

typedef struct {
	GxAudioDecProperty_Type      type;
	GxAudioDecProperty_SampleFre samplefre;
	GxAudioDecProperty_Channel   channel;
} GxAudioDecProperty_Capability;


typedef struct {
	int pcm_pts;
	unsigned int pcm_len;    // 样点为单位
	int pcm_samplefre;       // 最高位表示采样率是否改变，1有效
	int pcm_channel;
	int pcm_wordtype;
	int pcm_unit_time;

	unsigned int addr1;  //用户空间地址
	unsigned int size1;
	unsigned int addr2;  //用户空间地址
	unsigned int size2;
} GxAudioDecProperty_FrameData;

typedef struct {
	unsigned int ad_text_tag;
	unsigned long long esa_size;
	unsigned int ad_fade_byte;
	unsigned int ad_pan_byte;
} GxAudioDecProperty_ContrlInfo;

#endif /* __GXAV_AUDIODEC_PROPERTYTYPES_H__ */

