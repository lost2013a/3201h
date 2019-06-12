#ifndef __GX_MEDIA_API_H__
#define __GX_MEDIA_API_H__

#include "gxcore.h"
#include "gxplayer_decoder.h"

typedef enum {
	GXMEDIA_SOURCE_TS,
	GXMEDIA_SOURCE_ES,
	GXMEDIA_SOURCE_PES,
	GXMEDIA_SOURCE_MEM //for Es and Pes
} GxMediaSourceType;

typedef enum {
	GXMEDIA_STREAM_VIDEO,
	GXMEDIA_STREAM_AUDIO,
	GXMEDIA_STREAM_SUBTITLE
} GxMediaStreamType;

typedef enum {
	GXMEDIA_VIDEO_DECODE_ALL,
	GXMEDIA_VIDEO_DECODE_I_ONLY,
	GXMEDIA_VIDEO_DECODE_IP,
} GxMediaVideoDecodeMode;

typedef struct {
	AudioCodecType   codectype;
	int              sample_rate;
	int              sample_bits;
	int              channel_num;
	int              big_endian;
} GxMediaAudioPara;

typedef struct {
	VideoCodecType codectype;
	int width;
	int height;
	int mosaic_gate;
	int frame_rate;
	GxMediaVideoDecodeMode decode_mode;
} GxMediaVideoPara;

typedef struct {
	GxMediaAudioPara aparam;
	GxMediaVideoPara vparam;
	int audPid;
	int vidPid;
	int pcrPid;
	int freq_HZ;
	int sync_mode;
} GxMediaModulePara;

typedef struct {
	GxMediaSourceType source_type;
	GxMediaStreamType stream_type;
	uint8_t* buf;
	int len;
	int pts;
} GxMediaModuleInject;

typedef struct {
	int64_t apts;
	int64_t vpts;
	int64_t stc;
	int     esa_free_size;
	int     esa_used_size;
	int     esv_free_size;
	int     esv_used_size;
	int     ts_free_size;
	int     ts_used_size;
} GxMediaModuleInfo;

handle_t GxMediaApi_ModuleOpen(GxMediaSourceType type);
status_t GxMediaApi_ModuleClose(handle_t handle);
status_t GxMediaApi_ModuleConfig(handle_t handle, GxMediaModulePara params);
status_t GxMediaApi_ModuleStart (handle_t handle);
status_t GxMediaApi_ModuleStop  (handle_t handle, int freeze);
status_t GxMediaApi_ModulePause (handle_t handle);
status_t GxMediaApi_ModuleResume(handle_t handle);
status_t GxMediaApi_ModuleFinished(handle_t handle);
status_t GxMediaApi_ModuleInfo(handle_t handle, GxMediaModuleInfo *info);
int GxMediaApi_ModuleInjectData(handle_t handle, GxMediaModuleInject inject);

handle_t GxMediaApi_AudioOpen  (handle_t demux_handle);
status_t GxMediaApi_AudioClose (handle_t handle);
status_t GxMediaApi_AudioConfig(handle_t handle, GxMediaAudioPara param);
status_t GxMediaApi_AudioStart (handle_t handle);
status_t GxMediaApi_AudioStop  (handle_t handle);
status_t GxMediaApi_AudioPause (handle_t handle);
status_t GxMediaApi_AudioResume(handle_t handle);
status_t GxMediaApi_AudioFinished   (handle_t handle);
status_t GxMediaApi_AudioGetFifoInfo(handle_t handle, int* free_size, int* used_size, int* total_size);
status_t GxMediaApi_AudioFinished   (handle_t handle);
status_t GxMediaApi_AudioGetPts(handle_t handle, int64_t* apts);
int GxMediaApi_AudioInjectData(handle_t handle, GxMediaSourceType type, uint8_t* buffer, int len, int pts);

handle_t GxMediaApi_VideoOpen(handle_t demux_handle);
status_t GxMediaApi_VideoClose (handle_t handle);
status_t GxMediaApi_VideoConfig(handle_t handle, GxMediaVideoPara param);
status_t GxMediaApi_VideoStart (handle_t handle);
status_t GxMediaApi_VideoStop  (handle_t handle, int freeze);
status_t GxMediaApi_VideoPause (handle_t handle);
status_t GxMediaApi_VideoResume(handle_t handle);
status_t GxMediaApi_VideoGetFifoInfo(handle_t handle, int* free_size, int* used_size, int* total_size);
status_t GxMediaApi_VideoGetPts  (handle_t handle, int64_t* vpts);
status_t GxMediaApi_VideoFinished(handle_t handle);
int GxMediaApi_VideoInjectData(handle_t handle, GxMediaSourceType type, uint8_t* buffer, int len, int pts);

handle_t GxMediaApi_DemuxOpen(void);
status_t GxMediaApi_DemuxConfig(handle_t handle, int AudPid, int VidPid, int PcrPid);
status_t GxMediaApi_DemuxStart (handle_t handle);
status_t GxMediaApi_DemuxStop  (handle_t handle);
status_t GxMediaApi_DemuxClose (handle_t handle);
status_t GxMediaApi_DemuxGetAfifo(handle_t handle);
status_t GxMediaApi_DemuxGetVfifo(handle_t handle);
status_t GxMediaApi_DemuxGetFifoInfo(handle_t handle, int* free_size, int* used_size, int* total_size);
int GxMediaApi_DemuxInjectData(handle_t handle, uint8_t* buffer, int len);

handle_t GxMediaApi_StcOpen(void);
status_t GxMediaApi_StcConfig(handle_t handle, int freq_HZ, int sync_mode);
status_t GxMediaApi_StcStart (handle_t handle);
status_t GxMediaApi_StcStop  (handle_t handle);
status_t GxMediaApi_StcPause (handle_t handle);
status_t GxMediaApi_StcResume(handle_t handle);
status_t GxMediaApi_StcClose (handle_t handle);
status_t GxMediaApi_StcGetTime(handle_t handle, int64_t* stc);

#endif
