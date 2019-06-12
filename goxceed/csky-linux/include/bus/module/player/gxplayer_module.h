#ifndef __GX_PLAYER__MODULE_H__
#define __GX_PLAYER__MODULE_H__

#include "gxcore.h"
#include "av/avapi.h"
#include "gxplayer_common.h"
#include "gxplayer_vod.h"
#include "gxplayer_filter.h"
#include "gxplayer_subtitle.h"

__BEGIN_DECLS

#define PLAYER_NAME_LONG                        (31)
#define PLAYER_URL_LONG                         (2047)

#define PLAYER_MAX_TRACK_AUDIO                  (16)
#define PLAYER_MAX_TRACK_SUB                    (16)
#define PLAYER_MAX_TRACK_ADD                    (32)

#define PLAYER_TARCK_LANG_LONG                  (8)
#define PLAYER_TARCK_NAME_LONG                  (32)
#define PLAYER_TARCK_CODEC_LONG                 (32)

#define PLAYER_MAX_SUB_LOAD                     (1)
#define PLAYER_MAX_ENCRYPT_KEY_LEN          (32)

#define PLAYER_CONFIG_PLAY_RESERVED_MEMSIZE     "Play>packet_cache_size"
#define PLAYER_CONFIG_RECORD_CACHED_MEMSIZE     "Play>record_cache_size"
#define PLAYER_CONFIG_NETWORK_CACHED_MEMSIZE    "Play>network_cache_size"
#define PLAYER_CONFIG_DELAY_CACHE_SIZE          "Play>delay_cache_size"
#define PLAYER_CONFIG_DELAY_CACHE_HW_SIZE       "Play>delay_hw_cache_size"
#define PLAYER_CONFIG_DELAY_CACHE_TO_MEMORY     "Play>delay_cache2memory"
#define PLAYER_CONFIG_FLAG_ERROR_STOP           "Play>play_error_stop"
#define PLAYER_CONFIG_SUPPORT_NDS               "Play>play_support_nds"

#define PLAYER_CONFIG_AUTOPLAY_VIDEO_NAME       "AutoPlay>video_name"
#define PLAYER_CONFIG_AUTOPLAY_VIDEO_URL        "AutoPlay>video_url"
#define PLAYER_CONFIG_AUTOPLAY_RADIO_NAME       "AutoPlay>radio_name"
#define PLAYER_CONFIG_AUTOPLAY_RADIO_URL        "AutoPlay>radio_url"
#define PLAYER_CONFIG_AUTOPLAY_RADIO_FLAG       "AutoPlay>radio_flag"
#define PLAYER_CONFIG_AUTOPLAY_PLAY_FLAG        "AutoPlay>play_flag"

#define PLAYER_CONFIG_VIDEO_ESV_SIZE            "Video>esv_size"
#define PLAYER_CONFIG_VIDEO_INTERFACE           "Video>interface"
#define PLAYER_CONFIG_VIDEO_RESOLUTION_HDMI     "Video>resoluton_hdmi"
#define PLAYER_CONFIG_VIDEO_RESOLUTION_YUV      "Video>resoluton_yuv"
#define PLAYER_CONFIG_VIDEO_RESOLUTION_RCA      "Video>resoluton_rca"
#define PLAYER_CONFIG_VIDEO_RESOLUTION_RCA1     "Video>resoluton_rca1"
#define PLAYER_CONFIG_VIDEO_RESOLUTION_SCART    "Video>resoluton_scart"
#define PLAYER_CONFIG_VIDEO_RESOLUTION_SVIDEO   "Video>resoluton_svideo"

#define PLAYER_CONFIG_VIDEO_BRIGHTNESS_HDMI     "Video>brightness_hdmi"
#define PLAYER_CONFIG_VIDEO_BRIGHTNESS_YUV      "Video>brightness_yuv"
#define PLAYER_CONFIG_VIDEO_BRIGHTNESS_RCA      "Video>brightness_rca"
#define PLAYER_CONFIG_VIDEO_BRIGHTNESS_RCA1     "Video>brightness_rca1"
#define PLAYER_CONFIG_VIDEO_BRIGHTNESS_SCART    "Video>brightness_scart"
#define PLAYER_CONFIG_VIDEO_BRIGHTNESS_SVIDEO   "Video>brightness_svideo"

#define PLAYER_CONFIG_VIDEO_SATURATION_HDMI     "Video>saturation_hdmi"
#define PLAYER_CONFIG_VIDEO_SATURATION_YUV      "Video>saturation_yuv"
#define PLAYER_CONFIG_VIDEO_SATURATION_RCA      "Video>saturation_rca"
#define PLAYER_CONFIG_VIDEO_SATURATION_RCA1     "Video>saturation_rca1"
#define PLAYER_CONFIG_VIDEO_SATURATION_SCART    "Video>saturation_scart"
#define PLAYER_CONFIG_VIDEO_SATURATION_SVIDEO   "Video>saturation_svideo"

#define PLAYER_CONFIG_VIDEO_CONTRAST_HDMI     "Video>contrast_hdmi"
#define PLAYER_CONFIG_VIDEO_CONTRAST_YUV      "Video>contrast_yuv"
#define PLAYER_CONFIG_VIDEO_CONTRAST_RCA      "Video>contrast_rca"
#define PLAYER_CONFIG_VIDEO_CONTRAST_RCA1     "Video>contrast_rca1"
#define PLAYER_CONFIG_VIDEO_CONTRAST_SCART    "Video>contrast_scart"
#define PLAYER_CONFIG_VIDEO_CONTRAST_SVIDEO   "Video>contrast_svideo"

#define PLAYER_CONFIG_VIDEO_DISPLAY_SCREEN      "Video>screen"
#define PLAYER_CONFIG_VIDEO_SCREEN_XRES         "Video>xres"
#define PLAYER_CONFIG_VIDEO_SCREEN_YRES         "Video>yres"
#define PLAYER_CONFIG_VIDEO_ASPECT              "Video>aspect"
#define PLAYER_CONFIG_VIDEO_FREEZE_SWITCH       "Video>freeze_switch"
#define PLAYER_CONFIG_VIDEO_DEC_TIMEOUT         "Video>dec_timeout"
#define PLAYER_CONFIG_VIDEO_DEC_USERDATA_ENABLE "Video>userdata_enable"
#define PLAYER_CONFIG_VIDEO_DEC_USERDATA_LENGTH "Video>userdata_length"
#define PLAYER_CONFIG_VIDEO_DEC_MOSAIC_DROP     "Video>mosaic_drop"
#define PLAYER_CONFIG_VIDEO_DEC_MOSAIC_GATE     "Video>mosaic_gate"
#define PLAYER_CONFIG_VIDEO_DEC_SYNC_FLAG       "Video>sync_flag"
#define PLAYER_CONFIG_VIDEO_SUPPORT_PPZOOM      "Video>support_ppzoom"
#define PLAYER_CONFIG_VIDEO_AUTO_ADAPT          "Video>auto_adapt"
#define PLAYER_CONFIG_VIDEO_AUTO_PAL            "Video>auto_pal"
#define PLAYER_CONFIG_VIDEO_AUTO_NTSC           "Video>auto_ntsc"
#define PLAYER_CONFIG_VIDEO_PP_MAX_WIDTH        "Video>pp_max_width"
#define PLAYER_CONFIG_VIDEO_PP_MAX_HEIGHT       "Video>pp_max_height"
#define PLAYER_CONFIG_VIDEO_FB_MAX_SIZE         "Video>fb_max_size"

#define PLAYER_CONFIG_AUDIO_ANTI_ERROR_CODE     "Audio>anti_error_code"
#define PLAYER_CONFIG_AUDIO_DMX_FULL_GATE       "Audio>dmx_full_gate"
#define PLAYER_CONFIG_AUDIO_INTERFACE           "Audio>interface"
#define PLAYER_CONFIG_AUDIO_SPDIF_SOURCE        "Audio>spd_source"
#define PLAYER_CONFIG_AUDIO_HDMI_SOURCE         "Audio>hdmi_source"
#define PLAYER_CONFIG_AUDIO_VOLUME_PRIV         "Audio>volume_priv"
#define PLAYER_CONFIG_AUDIO_VOLUME              "Audio>volume"
#define PLAYER_CONFIG_AUDIO_TRACK               "Audio>track"
#define PLAYER_CONFIG_AUDIO_AC3_MODE            "Audio>ac3mode"
#define PLAYER_CONFIG_AUDIO_AC3_ENABLE          "Audio>ac3enable"
#define PLAYER_CONFIG_AUDIO_AAC_ENABLE          "Audio>aacenable"
#define PLAYER_CONFIG_AUDIO_DOWNMIX             "Audio>downmix"
#define PLAYER_CONFIG_AUDIO_SYNC_FLAG           "Audio>sync_flag"
#define PLAYER_CONFIG_AUDIO_SPEED_MUTE          "Audio>speed_mute"

#define PLAYER_CONFIG_PVR_TIME_SHIFT_FLAG       "PVR>shift_flag"
#define PLAYER_CONFIG_PVR_TIME_SHIFT_FILE       "PVR>shift_file"
#define PLAYER_CONFIG_PVR_TIME_SHIFT_DMXID      "PVR>shift_dmxid"

#define PLAYER_CONFIG_PVR_RECORD_VOLUME_SIZE    "PVR>record_volume_sizemb"
#define PLAYER_CONFIG_PVR_RECORD_VOLUME_MAX     "PVR>record_volume_maxnum"
#define PLAYER_CONFIG_PVR_RECORD_VOLUME_FULLSTOP "PVR>record_volume_fullstop"
#define PLAYER_CONFIG_PVR_RECORD_RESERVE_SIZE   "PVR>record_reserve_sizemb"

#define PLAYER_CONFIG_ETS_FILE_ENCRYPT_FLAG		"FILE>ets_encrypt_flag"
#define PLAYER_CONFIG_ETS_FILE_ENCRYPT_LEN		"FILE>ets_encrypt_len"
#define PLAYER_CONFIG_ETS_FILE_ENCRYPT_KEY		"FILE>ets_encrypt_key"

extern void GxPlayer_ModuleRegisterALL(void);

extern void GxPlayer_ModuleRegisterStreamDVB(void);
extern void GxPlayer_ModuleRegisterStreamMEM(void);
extern void GxPlayer_ModuleRegisterStreamFILE(void);
extern void GxPlayer_ModuleRegisterStreamFIFO(void);
extern void GxPlayer_ModuleRegisterStreamRINGMEM(void);
extern void GxPlayer_ModuleRegisterStreamHTTP(void);
extern void GxPlayer_ModuleRegisterStreamM3U8(void);
extern void GxPlayer_ModuleRegisterStreamRTMP(void);
extern void GxPlayer_ModuleRegisterStreamUDP(void);
extern void GxPlayer_ModuleRegisterStreamRTP(void);
extern void GxPlayer_ModuleRegisterStreamRTSP(void);
extern void GxPlayer_ModuleRegisterStreamWFD(void);
extern void GxPlayer_ModuleRegisterStreamCRYPTO(void);

extern void GxPlayer_ModuleRegisterDemuxerMP3(void);
extern void GxPlayer_ModuleRegisterDemuxerMP4(void);
extern void GxPlayer_ModuleRegisterDemuxerAVI(void);
extern void GxPlayer_ModuleRegisterDemuxerES(void);
extern void GxPlayer_ModuleRegisterDemuxerMKV(void);
extern void GxPlayer_ModuleRegisterDemuxerFLV(void);
extern void GxPlayer_ModuleRegisterDemuxerAAC(void);
extern void GxPlayer_ModuleRegisterDemuxerSWTS(void);
extern void GxPlayer_ModuleRegisterDemuxerHWTS(void);
extern void GxPlayer_ModuleRegisterDemuxerPS (void);
extern void GxPlayer_ModuleRegisterDemuxerLOGO(void);
extern void GxPlayer_ModuleRegisterDemuxerRMVB(void);

extern void GxPlayer_ModuleRegisterSubtitleDVB(void);
extern void GxPlayer_ModuleRegisterSubtitleInside(void);
extern void GxPlayer_ModuleRegisterSubtitleOutside(void);


typedef enum
{
	VIDEO_OUTPUT_RCA       = (1 << 0) ,
	VIDEO_OUTPUT_RCA1      = (1 << 1) ,
	VIDEO_OUTPUT_YUV       = (1 << 2) ,
	VIDEO_OUTPUT_SCART     = (1 << 3) ,
	VIDEO_OUTPUT_SVIDEO    = (1 << 4) ,
	VIDEO_OUTPUT_HDMI      = (1 << 5) ,
}VideoOutputInterface;

typedef enum
{
	// RCA/SCART/SVIDEO
	VIDEO_OUTPUT_PAL                 = 1 ,  //-PAL
	VIDEO_OUTPUT_PAL_M               = 2 ,
	VIDEO_OUTPUT_PAL_N               = 3 ,
	VIDEO_OUTPUT_PAL_NC              = 4 ,
	VIDEO_OUTPUT_NTSC_M              = 5 ,  //-NTSC
	VIDEO_OUTPUT_NTSC_443            = 6 ,

	//YUV
	VIDEO_OUTPUT_YCBCR_480I          = 7 ,
	VIDEO_OUTPUT_YCBCR_576I          = 8 ,

	VIDEO_OUTPUT_YCBCR_1080I_50HZ    = 9 ,
	VIDEO_OUTPUT_YCBCR_1080I_60HZ    = 10 ,

	VIDEO_OUTPUT_YPBPR_480P          = 11 ,
	VIDEO_OUTPUT_YPBPR_576P          = 12 ,

	VIDEO_OUTPUT_YPBPR_720P_50HZ     = 13 ,
	VIDEO_OUTPUT_YPBPR_720P_60HZ     = 14 ,
	VIDEO_OUTPUT_YPBPR_1080P_50HZ    = 15 ,
	VIDEO_OUTPUT_YPBPR_1080P_60HZ    = 16 ,

	//HDMI
	VIDEO_OUTPUT_HDMI_480I           ,
	VIDEO_OUTPUT_HDMI_576I           ,
	VIDEO_OUTPUT_HDMI_480P           ,
	VIDEO_OUTPUT_HDMI_576P           ,
	VIDEO_OUTPUT_HDMI_720P_50HZ      ,
	VIDEO_OUTPUT_HDMI_720P_60HZ      ,
	VIDEO_OUTPUT_HDMI_1080I_50HZ     ,
	VIDEO_OUTPUT_HDMI_1080I_60HZ     ,
	VIDEO_OUTPUT_HDMI_1080P_50HZ     ,
	VIDEO_OUTPUT_HDMI_1080P_60HZ     ,

	VIDEO_OUTPUT_MODE_MAX
}VideoOutputMode;

typedef struct {
	VideoOutputInterface    interface;
	VideoOutputMode         mode;
}VideoOutputConfig;

typedef struct {
	int enable;
	int length;
}VideoUserdataConfig;

typedef enum {
	AUDIO_OUTPUT_DAC_IN     = (1 << 0) ,
	AUDIO_OUTPUT_DAC_OUT    = (1 << 1) ,
	AUDIO_OUTPUT_SPDIF      = (1 << 2) ,
	AUDIO_OUTPUT_HDMI       = (1 << 3) ,
}AudioOutputInterface;

typedef enum {
	AUDIO_OUTPUT_PCM,
	AUDIO_OUTPUT_AC3,
	AUDIO_OUTPUT_EAC3,
	AUDIO_OUTPUT_SMART,
	AUDIO_OUTPUT_SAFE,
	AUDIO_OUTPUT_RAW,
	AUDIO_OUTPUT_DTS,
	AUDIO_OUTPUT_NOTANY,
}AudioOutputDataType;

typedef struct {
	VideoOutputInterface    interface;

	int                     brightness;
	int                     saturation;
	int                     contrast;
}VideoColor;

typedef struct {
	VideoOutputInterface    interface;

	int                     enable;
}VideoOutDefault;

typedef VideoOutDefault VideoOutPower;

typedef struct {
	AudioOutputDataType     output_data;
	AudioOutputInterface    output_port;
}AudioOutputConfig;

typedef enum
{
	AUDIO_TRACK_MONO        , // all mono
	AUDIO_TRACK_LEFT        , // all left
	AUDIO_TRACK_RIGHT       , // all right
	AUDIO_TRACK_STEREO      , // left->left, right->right
	AUDIO_TRACK_RIGHT_MUTE_LEFT, // left->mute, right->right
	AUDIO_TRACK_LEFT_MUTE_RIGHT, // left->left, right->mute
	AUDIO_TRACK_MONO_MUTE_LEFT,//right->mono, other->mute 
	AUDIO_TRACK_MONO_MUTE_RIGHT, //left ->mono, other->mute
	//DOLBY TEST
	AUDIO_TRACK_SPDIF_LR    ,
	AUDIO_TRACK_SPDIF_LsRs  ,
	AUDIO_TRACK_SPDIF_CS    ,
	AUDIO_TRACK_SPDIF_X1X2  ,
}AudioTrack;

typedef enum
{
	AUDIO_PRIMARY_TRACK    ,
	AUDIO_DESCRIPTOR_TRACK ,
	AUDIO_FULL_MIX_TRACK
}AudioDecriptorTrack;

typedef enum
{
	AUDIO_AC3_DECODE_MODE = (1<<0),
	AUDIO_AC3_BYPASS_MODE = (1<<1),
	AUDIO_AC3_FULL_MODE   = AUDIO_AC3_DECODE_MODE|AUDIO_AC3_BYPASS_MODE,
}AudioAc3Mode;

typedef enum {
	ASPECT_NORMAL       = 0 ,
	ASPECT_PAN_SCAN         ,
	ASPECT_LETTER_BOX       ,
	ASPECT_RAW_SIZE         ,
	ASPECT_RAW_RATIO        ,
	ASPECT_4X3_PULL         ,
	ASPECT_4X3_CUT          ,
	ASPECT_16X9_PULL        ,
	ASPECT_16X9_CUT         ,
	ASPECT_4X3              ,
	ASPECT_16X9             ,
}VideoAspect;

typedef struct {
	int aspect;
#define DISPLAY_SCREEN_4X3   0
#define DISPLAY_SCREEN_16X9  1
	int xres;
	int yres;
}DisplayScreen;

typedef struct {
	int enable;
	VideoOutputMode pal;
	VideoOutputMode ntsc;
}PlayerVideoAutoAdapt;

typedef struct {
	PlayerStatus   status;
	PlayerError    error;
	AVCodecStatus  acodec;
	AVCodecStatus  vcodec;
}PlayerStatusInfo;

typedef struct {
	uint64_t current;
	uint64_t totle;
	uint64_t seek_min;
}PlayTimeInfo;

typedef enum {
	PLAYER_SUB_TYPE_CC      ,
	PLAYER_SUB_TYPE_DVB     ,
	PLAYER_SUB_TYPE_FILE    ,
	PLAYER_SUB_TYPE_INSIDE  ,
}PlayerSubType;

typedef enum {
	PLAYER_SUB_RENDER_SPP   ,
	PLAYER_SUB_RENDER_OSD   ,
}PlayerSubRender;

typedef struct {
	int32_t                 pid;
	int16_t                 major;
	int16_t                 minor;
}PlayerSubPID;

typedef struct {
	int                     id;
	char                    lang[PLAYER_TARCK_LANG_LONG];
	char                    track_name[PLAYER_TARCK_NAME_LONG];
	char                    codec_id[PLAYER_TARCK_CODEC_LONG];
	PlayerSubEncode         encode;
	PlayerSubType           type;
	PlayerSubPID            pid;
}PlayerSubTrack;

typedef struct{
	PlayerSubType           type;
	PlayerSubRender         render;
	const char*             file_name;
	PlayerSubPID            pid;
	int                     inside_draw;    //only for spp subtitle
	int                     (*init)(PlayerWindow* rect,int type);
	void                    (*destory)(int handle);
	int                     (*show)(int handle);
	int                     (*hide)(int handle);
	int                     (*draw)(void* data, int num,int type);
	void                    (*clear)(int handle);
}PlayerSubPara;

typedef struct  {
	void*                   sub_hdr;
	int                     sub_num;
	PlayerSubTrack          track[PLAYER_MAX_TRACK_SUB];
}PlayerSubtitle;

#pragma pack(1)
typedef struct {
	char                    Header[4+1];   // 标签头必须是"TAG"否则认为没有标签,3字节
	char                    Title[30+1];   // 标题,30字节
	char                    Artist[30+1];  // 作者,30字节
	char                    Album[30+1];   // 专集,30字节
	char                    Year[4+1];     // 出品年代,4字节
	char                    Comment[28+1]; // 备注,28字节
	char                    Reserve[1];    // 保留,1字节
	char                    Track[1+1];    // 音轨,1字节
	char                    Genre[1+1];    // 类型,1字节
}PlayerID3V1;
#pragma pack()

#pragma pack(1)
typedef struct id3_v2
{
	char                    fName[4+1];
	char*                   pFBody;
	int                     size;
	struct                  id3_v2 *pNext;
}PlayerID3V2;
#pragma pack()

typedef struct {
	PlayerID3V1*            v1;
	PlayerID3V2*            v2;
}PlayerID3Info;

typedef enum {
	SNAP_LAYER_OSD          ,
	SNAP_LAYER_VPP          ,
	SNAP_LAYER_SPP          ,
	SNAP_LAYER_BKG          ,
	SNAP_LAYER_MIX          ,
}PlayerLayer;

typedef struct {
	PlayerLayer             layer;
	PlayerWindow            rect;
	void*                   surface;
}PlayerSnapshot;

typedef struct {
	char                    codec_id[PLAYER_TARCK_CODEC_LONG]  ; // 视频编码格式
	char                    track_name[PLAYER_TARCK_NAME_LONG] ;//轨道 名称
	uint32_t                width   ; // 视频帧宽
	uint32_t                height  ; // 视频帧高
	uint32_t                bitrate ; // 视频的比特率
	uint32_t                interlace;// 隔行编码
	float                   fps     ; // 视频帧率
	float                   aspect  ; // 视频的宽高比
	VideoCodecType          codec_type;
}PlayerVideoTrack;

typedef struct {
	uint32_t                id;
	char                    lang[PLAYER_TARCK_LANG_LONG];
	char                    codec_id[PLAYER_TARCK_CODEC_LONG]  ; // 音频的编码格式
	char                    track_name[PLAYER_TARCK_NAME_LONG] ; //轨道 名称
	uint32_t                bitrate    ;  // 音频的比特率
	uint32_t                samplerate ;  // 音频的采样率
	uint32_t                channels   ;  // 音频的声道数
	AudioCodecType          codec_type;
	AudioDecriptorTrack     track_type;
}PlayerAudioTrack;

typedef struct {
	char                    url[PLAYER_URL_LONG+1];
	uint64_t                file_size;
	uint64_t                duration ;
	PlayerVideoTrack        video;
	PlayerAudioTrack        audio[PLAYER_MAX_TRACK_AUDIO];
	PlayerSubTrack          sub[PLAYER_MAX_TRACK_SUB];
	uint32_t                bitrate;  // 流的比特率
	unsigned int            bandwidth[GXPLAYER_MAX_BAND_WIDTH];
	int                     audio_num;
	int                     sub_num;
	int                     bandwidth_num;
	int                     is_radio;
	int                     cur_sub_id;
	int                     cur_audio_id;
	int                     cur_bandwidth_id;
	uint64_t				rec_filesize;
	uint64_t				rec_duration;
	int                     net_speed;
	int                     buf_percent;
	int                     buffering;
	GxDemuxerRecordExtInfo  tsinfo;
	GxAvFrameStat           video_stat;
	GxAvFrameStat           audio_stat;
	unsigned int            switch_cost_timems;
}PlayerProgInfo;

typedef struct {
	int                     cur_id;
	int                     num;
	unsigned int            value[GXPLAYER_MAX_BAND_WIDTH];
}PlayerBandwidth;

typedef struct {
	int                     buffering;
	int                     net_speed;
	int                     buf_percent;
	int64_t                 restart_time;
	PlayerBandwidth         bandwidth;
}PlayerNetInfo;

typedef struct {
	GxDemuxerRecordExtInfo  ext_info;
	GxDemuxerRecordUserInfo ext_data;
}PlayerRecordConfig;

typedef struct {
	int                     cache2mem;
	int                     cachesize;
	unsigned char           cachedir[PLAYER_URL_LONG+1];
}PlayerDelayConfig;

typedef struct {
	GxDemuxerPlayTsExtInfo ext_ts_info;
}PlayerPlayConfig;

typedef struct {
	int                     volume_sizemb;
	int                     volume_maxnum;
	int                     volume_fullstop;
	int                     reserve_sizemb;
}PlayerPVRConfig;

typedef struct {
	unsigned char           url[PLAYER_URL_LONG+1];
	int                     enable;
	int                     shift_dmxid;
}PlayerShiftConfig;

typedef enum
{
	PLAYER_EVENT_SPEED_REPORT      ,
	PLAYER_EVENT_STATUS_REPORT     ,
	PLAYER_EVENT_AVCODEC_REPORT    ,
	PLAYER_EVENT_RESOLUTION_REPORT ,
	PLAYER_EVENT_RECORD_OVERFLOW   ,
}PlayerEventID;

typedef struct {
	char                          player[PLAYER_NAME_LONG+1];
	char                          url[PLAYER_URL_LONG+1];
	PlayerStatus                  status;
	int                           error;
}PlayerEventStatus;

typedef struct {
	char                          player[PLAYER_NAME_LONG+1];
	char                          url[PLAYER_URL_LONG+1];
	AVCodecStatus                 vcodec;
	AVCodecStatus                 acodec;
}PlayerEventAVCodec;

typedef struct {
	VideoOutputMode               resolution;
}PlayerEventResolution;

typedef struct {
	char                          player[PLAYER_NAME_LONG+1];
	float                         speed;
}PlayerEventSpeed;

typedef struct {
	char                          player[PLAYER_NAME_LONG+1];
}PlayerEventRecordOverflow;

typedef struct {
	int64_t start;
	int volume;
	int audio_pid;
	int audio1_pid;
	int video_pid;
	int sub_pid;
	int abort;
	PlayerWindow rect;
}PlayerPlayInfo;

typedef enum {
	PLAYER_MEDIA_AUDIO  = (1 << 0),
	PLAYER_MEDIA_VIDEO  = (1 << 1),
	PLAYER_MEDIA_SUB    = (1 << 2),
	PLAYER_MEDIA_RECORD = (1 << 2),
	PLAYER_MEDIA_ALL    = 0xFFFFFFFF,
}PlayerMediaContent;

typedef void (*PLAYER_EVENT_REPORT)(PlayerEventID event,void* args);

typedef int  (*PLAYER_FREEZE_FRAME)(void);

typedef int  (*PLAYER_UNFREEZE_FRAME)(void);

typedef int  (*PLAYER_SEEK_CBK)(int timems);

typedef int  (*PLAYER_INTERRUPT_CBK)(void);


typedef struct {
	unsigned char* data;
	unsigned int   size;
}GxPlayerDataPacket;

typedef handle_t (*PLAYER_STREAM_PORT_INIT_CBK)(size_t blksize, unsigned int delayms);
typedef void     (*PLAYER_STREAM_PORT_UNINIT_CBK)(handle_t handle);
typedef void     (*PLAYER_STREAM_PORT_EXIT_CBK)(handle_t handle);
typedef int      (*PLAYER_STREAM_PORT_NEWPKT_CBK)(handle_t handle, GxPlayerDataPacket* pkt, ssize_t size);
typedef void     (*PLAYER_STREAM_PORT_DELPKT_CBK)(handle_t handle, GxPlayerDataPacket* pkt);
typedef int      (*PLAYER_STREAM_PORT_GETPKT_CBK)(handle_t handle, GxPlayerDataPacket* pkt);
typedef int      (*PLAYER_STREAM_PORT_PUTPKT_CBK)(handle_t handle, GxPlayerDataPacket* pkt);

typedef struct {
	PLAYER_STREAM_PORT_INIT_CBK    Init;
	PLAYER_STREAM_PORT_UNINIT_CBK  Uninit;
	PLAYER_STREAM_PORT_EXIT_CBK    Exit;
	PLAYER_STREAM_PORT_NEWPKT_CBK  NewPacket;
	PLAYER_STREAM_PORT_DELPKT_CBK  DelPacket;
	PLAYER_STREAM_PORT_GETPKT_CBK  GetPacket;
	PLAYER_STREAM_PORT_PUTPKT_CBK  PutPacket;
}PlayerStreamPortCallback;

extern void GxPlayer_SetStreamCallback(PlayerStreamPortCallback *cbk);

extern void GxPlayer_SetSeekCallback(PLAYER_SEEK_CBK cbk);

extern void GxPlayer_SetEventCallback(PLAYER_EVENT_REPORT report);

extern void GxPlayer_ModuleInit(int modFlag);

extern void GxPlayer_ModuleDestroy(void);


extern status_t GxPlayer_MediaPlay(const char* name, const char* url, int64_t start, int volume, PlayerWindow* window);

extern status_t GxPlayer_MediaExitPlay(const char* name);

extern status_t GxPlayer_MediaWaitPlay(const char* name);

extern status_t GxPlayer_MediaPlay2(const char* name, const char* srcurl, PlayerPlayInfo *info);

extern status_t GxPlayer_MediaRecord(const char* name, const char* url, const char* file);

extern status_t GxPlayer_MediaStop(const char* name);

extern status_t GxPlayer_MediaPause(const char* name);

extern status_t GxPlayer_MediaResume(const char* name);

extern status_t GxPlayer_MediaSeek(const char* name, int64_t time, SeekFlag flag);

extern status_t GxPlayer_MediaSpeed(const char* name, float speed);

extern status_t GxPlayer_MediaWindow(const char* name, PlayerWindow* window);

extern status_t GxPlayer_MediaClip(const char* name, PlayerWindow* Clip);

extern status_t GxPlayer_MediaAudioSync(const char* name, int timems);

extern status_t GxPlayer_MediaAudioSwitch(const char* name,int pid,AudioCodecType type,char* url);

extern status_t GxPlayer_MediaVideoHide(const char* name);

extern status_t GxPlayer_MediaVideoShow(const char* name);

extern status_t GxPlayer_MediaRecordConfig(const char* name, PlayerRecordConfig* config);

extern status_t GxPlayer_MediaPlayConfig(const char* name, PlayerPlayConfig* config);

extern status_t GxPlayer_MediaDelayConfig(const char* name, PlayerDelayConfig* config);

extern status_t GxPlayer_MediaDelayConfig(const char* name, PlayerDelayConfig* config);

extern PlayerSubtitle*  GxPlayer_MediaSubLoad(const char* name, PlayerSubPara* subpara);

extern status_t GxPlayer_MediaSubUnLoad(const char* name, PlayerSubtitle* subdata);

extern status_t GxPlayer_MediaSubHide(const char* name, PlayerSubtitle* subdata);

extern status_t GxPlayer_MediaSubShow(const char* name, PlayerSubtitle* subdata);

extern status_t GxPlayer_MediaSubSync(const char* name, PlayerSubtitle* subdata,int timems);

extern status_t GxPlayer_MediaSubSwitch(const char* name, PlayerSubtitle* subdata,PlayerSubPID pid);

extern status_t GxPlayer_MediaSubResolution(const char* name, PlayerSubtitle* subdata,VideoOutputMode res);


extern status_t GxPlayer_MediaGetDataLength(const char* name, uint32_t* aDataLen, uint32_t* vDataLen);

extern status_t GxPlayer_MediaGetTime(const char* name, PlayTimeInfo *info);

extern status_t GxPlayer_MediaGetPercent(const char* name, uint8_t* current);

extern status_t GxPlayer_MediaGetProgInfoByUrl(const char* url, PlayerProgInfo* info);

extern status_t GxPlayer_MediaGetProgInfoByName(const char* player, PlayerProgInfo* info);

extern status_t GxPlayer_MediaGetNetInfo(const char* name, PlayerNetInfo* info);

extern status_t GxPlayer_MediaGetStatus(const char* name, PlayerStatusInfo* info);

extern status_t GxPlayer_MediaFreeID3Info(PlayerID3Info* pID3);

extern PlayerID3Info* GxPlayer_MediaGetID3Info(const char* file);

extern status_t GxPlayer_SetVideoSyncMode(int flag);
// 0: free run;
// 1: play when synced;
// 2: play when decode over; before synced;

extern status_t GxPlayer_SetVideoColors(VideoColor color);

extern status_t GxPlayer_GetVideoColors(VideoColor *color);

extern status_t GxPlayer_GetVideoUsableIface(int *iface);

extern status_t GxPlayer_SetVideoAspect(VideoAspect aspect );

extern status_t GxPlayer_SetVideoOutputSelect(int select);

extern status_t GxPlayer_SetVideoOutputConfig(VideoOutputConfig config);

extern status_t GxPlayer_SetVideoOutputDef(VideoOutDefault outdef);

extern status_t GxPlayer_SetVideoOutputPower(int enable);

extern status_t GxPlayer_SetVideoOutputPower2(VideoOutPower power);

extern status_t GxPlayer_SetDisplayScreen(DisplayScreen scr);

extern status_t GxPlayer_SetVideoMosaicDrop(int enable);

extern status_t GxPlayer_SetVideoUserdataConfig(VideoUserdataConfig *config);

extern status_t GxPlayer_SetAudioPureRecoveryMode(int enable);

extern status_t GxPlayer_SetAudioOutputSelect(int interface);

extern status_t GxPlayer_SetAudioOutputConfig(AudioOutputConfig config);

extern status_t GxPlayer_SetAudioVolume(unsigned int vol);

extern status_t GxPlayer_SetAudioTrack(AudioTrack track);

extern status_t GxPlayer_SetAudioDescriptorTrack(AudioDecriptorTrack tarck);

extern status_t GxPlayer_SetAudioMute(int enable);

extern status_t GxPlayer_SetAudioDmxFullGate(int full_gate);

extern status_t GxPlayer_SetAudioAC3Mode(AudioAc3Mode mode);

extern status_t GxPlayer_SetAudioSyncEnable(int enable);

extern status_t GxPlayer_SetAudioDownMix(int enable);

extern status_t GxPlayer_SetFreezeFrameSwitch(int enable);

extern status_t GxPlayer_SetTimeShiftConfig(PlayerShiftConfig* config);

extern status_t GxPlayer_SetVideoAutoAdapt(PlayerVideoAutoAdapt* config);

extern status_t GxPlayer_MediaTrackAdd(const char* name, GxStreamTrackAdd* track);

extern status_t GxPlayer_MediaTrackDel(const char* name, GxStreamTrackDel* track);

extern status_t GxPlayer_MediaBandwidthSwitch(const char* name, unsigned int index);

extern status_t GxPlayer_SetPVRConfig(PlayerPVRConfig* config);

extern status_t GxPlayer_MediaAdAudioEnable(const char* name, int pid, AudioCodecType type);

extern status_t GxPlayer_MediaAdAudioDisable(const char* name);

extern status_t GxPlayer_MediaSave(const char* name, PlayerMediaContent content);

extern status_t GxPlayer_MediaRestore(const char* name, PlayerMediaContent content);

extern status_t GxPlayer_MediaStopPlay(const char* name);

extern status_t GxPlayer_MediaStopRecord(const char* name);

extern void GxPlayer_SetVideoPPZoom(int enable);

extern void GxPlayer_AudioCodecMask(AudioCodecType mask);

extern void GxPlayer_VideoCodecMask(VideoCodecType mask);

extern void GxPlayer_SetTP(const char *url);

__END_DECLS

#endif

