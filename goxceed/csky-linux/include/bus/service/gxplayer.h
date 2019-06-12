#ifndef __SERVICE_PLAYER_H__
#define __SERVICE_PLAYER_H__

#include "../gxbus.h"
#include "../module/player/gxplayer_module.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef struct {
	const char*                   player;
	char                          url[PLAYER_URL_LONG+1];
	int64_t                       start;
	int                           volume;
	PlayerWindow                  window;
}GxMsgProperty_PlayerPlay;

typedef struct{
	const char*                   player;
}GxMsgProperty_PlayerStop;

typedef struct{
	const char*                   player;
}GxMsgProperty_PlayerPause;

typedef struct{
	const char*                   player;
}GxMsgProperty_PlayerResume;

typedef struct {
	const char*                   player;
	int64_t                       time;
	SeekFlag                      flag;
}GxMsgProperty_PlayerSeek;

typedef struct {
	const char*                   player;
	float                         speed;
}GxMsgProperty_PlayerSpeed;

typedef struct {
	const char*                   player;
	unsigned char                 url[PLAYER_URL_LONG+1];
	unsigned char                 file[PLAYER_URL_LONG+1];
}GxMsgProperty_PlayerRecord;

typedef struct{
	const char*                   player;
}GxMsgProperty_PlayerVideoHide;

typedef struct{
	const char*                   player;
}GxMsgProperty_PlayerVideoShow;

typedef VideoColor                GxMsgProperty_PlayerVideoColor;

typedef struct {
	const char*                   player;
	PlayerWindow                  rect;
}GxMsgProperty_PlayerVideoWindow;

typedef struct {
	const char*                   player;
	PlayerWindow                  rect;
}GxMsgProperty_PlayerVideoClip;


typedef VideoAspect               GxMsgProperty_PlayerVideoAspect;

typedef int                       GxMsgProperty_PlayerVideoInterface;//SAMPLE:VIDEO_OUTPUT_RCA|VIDEO_OUTPUT_VGA

typedef VideoOutputConfig         GxMsgProperty_PlayerVideoModeConfig;

typedef VideoOutDefault           GxMsgProperty_PlayerVideoOutputDef;

typedef int                       GxMsgProperty_PlayerVideoOutputPower;

typedef VideoUserdataConfig		  GxMsgProperty_PlayerVideoUserdataConfig;

typedef struct {
	int                           enable;
}GxMsgProperty_PlayerVideoMosaicDrop;

typedef struct {
	int                           enable;
}GxMsgProperty_PlayerAudioDownMix;

typedef struct {
	const char*                   player;
	int                           timems;
}GxMsgProperty_PlayerAudioSync;

typedef int                       GxMsgProperty_PlayerAudioMute;

typedef unsigned int              GxMsgProperty_PlayerAudioVolume;

typedef AudioTrack                GxMsgProperty_PlayerAudioTrack;

typedef AudioDecriptorTrack       GxMsgProperty_PlayerAudioDescriptorTrack;

typedef struct {
	const char*                   player;
	char                          url[PLAYER_URL_LONG+1];
	int                           pid;
	AudioCodecType                type;
}GxMsgProperty_PlayerAudioSwitch;

typedef struct {
	AudioAc3Mode                           mode;
}GxMsgProperty_PlayerAudioAC3Mode;

typedef int                       GxMsgProperty_PlayerAudioInterface;

typedef AudioOutputConfig         GxMsgProperty_PlayerAudioModeConfig;

typedef struct {
	const char*                   player;
	PlayerSubtitle*               sub;
	int                           timems;
}GxMsgProperty_PlayerSubtitleSync;

typedef struct {
	const char*                   player;
	PlayerSubPara                 para;
	PlayerSubtitle*               sub;
}GxMsgProperty_PlayerSubtitleLoad;

typedef struct {
	const char*                   player;
	PlayerSubtitle*               sub;
}GxMsgProperty_PlayerSubtitleUnLoad;

typedef struct {
	const char*                   player;
	PlayerSubtitle*               sub;
	PlayerSubPID                  pid;
}GxMsgProperty_PlayerSubtitleSwitch;

typedef struct {
	const char*                   player;
	PlayerSubtitle*               sub;
}GxMsgProperty_PlayerSubtitleHide;

typedef struct {
	const char*                   player;
	PlayerSubtitle*               sub;
}GxMsgProperty_PlayerSubtitleShow;

typedef struct {
	const char*                   player;
	PlayerSubtitle*               sub;
	VideoOutputMode               res;
}GxMsgProperty_PlayerSubtitleResolution;

typedef struct {
	const char*                   player;
	PlayerPlayConfig              config;
}GxMsgProperty_PlayerPlayConfig;

typedef struct {
	const char*                   player;
	PlayerDelayConfig             config;
}GxMsgProperty_PlayerDelayConfig;

typedef struct {
	const char*                   player;
	PlayerRecordConfig	          config;
}GxMsgProperty_PlayerRecordConfig;

typedef PlayerPVRConfig			  GxMsgProperty_PlayerPVRConfig;

typedef PlayerShiftConfig	      GxMsgProperty_PlayerTimeShift;

typedef DisplayScreen             GxMsgProperty_PlayerDisplayScreen;

typedef int                       GxMsgProperty_PlayerFreezeFrameSwitch ;

typedef PlayerVideoAutoAdapt      GxMsgProperty_PlayerVideoAutoAdapt ;

typedef struct {
	const char*                   player;
	char                          url[PLAYER_URL_LONG+1];
	PlayerWindow                  rect;
	int                           lock;
	int                           volume;
}GxMsgProperty_PlayerMultiScreenPlay;

typedef PlayerEventStatus         GxMsgProperty_PlayerStatusReport;

typedef PlayerEventAVCodec        GxMsgProperty_PlayerAVCodecReport;

typedef PlayerEventResolution     GxMsgProperty_PlayerResolutionReport;

typedef PlayerEventSpeed          GxMsgProperty_PlayerSpeedReport;

typedef PlayerEventRecordOverflow GxMsgProperty_PlayerRecordOverflow;

typedef struct {
	char                          player[PLAYER_NAME_LONG+1];
	GxMsgID                       msg;
	GxMsgStatus                   ret;
}GxMsgProperty_PlayerProcessFinish;

typedef struct {
	const char*                   player;
	GxStreamTrackAdd              track;
}GxMsgProperty_PlayerTrackAdd;

typedef struct {
	const char*                   player;
	GxStreamTrackDel              track;
}GxMsgProperty_PlayerTrackDel;

typedef struct {
	const char*                   player;
	unsigned int                  index;
}GxMsgProperty_PlayerBandwidthSwitch;

typedef struct {
	const char*                   player;
	int                           pid;
	AudioCodecType                type;
}GxMsgProperty_PlayerAdAudio;

__END_DECLS

#endif

