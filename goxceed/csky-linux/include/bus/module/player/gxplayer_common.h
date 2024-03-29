#ifndef __GXPLAYER_COMMON_H__
#define __GXPLAYER_COMMON_H__

#include "gxcore.h"

__BEGIN_DECLS

#define GXPLAYER_MAX_EXT_TRACK 16
#define GXPLAYER_MAX_BAND_WIDTH 16

typedef enum {
	PLAYER_STATUS_STOPPED              ,
	PLAYER_STATUS_PLAY_START           ,
	PLAYER_STATUS_PLAY_PAUSE           ,
	PLAYER_STATUS_PLAY_RUNNING         ,
	PLAYER_STATUS_PLAY_END             ,
	PLAYER_STATUS_RECORD_PAUSE         ,
	PLAYER_STATUS_RECORD_RUNNING       ,
	PLAYER_STATUS_RECORD_FULL          ,
	PLAYER_STATUS_RECORD_END           ,
	PLAYER_STATUS_SHIFT_START          ,
	PLAYER_STATUS_SHIFT_PAUSE          ,
	PLAYER_STATUS_SHIFT_RUNNING        ,
	PLAYER_STATUS_SHIFT_SWITCH         ,
	PLAYER_STATUS_SHIFT_HOLD_PAUSE     ,
	PLAYER_STATUS_SHIFT_HOLD_RUNNING   ,
	PLAYER_STATUS_SHIFT_END            ,
	PLAYER_STATUS_ERROR                ,
	PLAYER_STATUS_START_FILL_BUF       ,
	PLAYER_STATUS_END_FILL_BUF         ,
	PLAYER_STATUS_SERVER_ERROR         ,
} PlayerStatus;

typedef enum {
	PLAYER_ERROR_NO_ERROR              ,
	PLAYER_ERROR_NO_DATA_SOURCE        ,
	PLAYER_ERROR_NO_DEMUX_TOOLS        ,
	PLAYER_ERROR_NO_MUXER_TOOLS        ,
	PLAYER_ERROR_NO_DUMP_TOOLS         ,
	PLAYER_ERROR_NO_VIDEO_DECODER      ,
	PLAYER_ERROR_NO_AUDIO_DECODER      ,
	PLAYER_ERROR_NO_SUB_DECODER        ,
	PLAYER_ERROR_NO_VIDEO_RENDER       ,
	PLAYER_ERROR_NO_AUDIO_RENDER       ,
	PLAYER_ERROR_NO_SUB_RENDER         ,
	PLAYER_ERROR_DEMUX_ERROR           ,
	PLAYER_ERROR_VIDEO_DECODER_ERROR   ,
	PLAYER_ERROR_AUDIO_DECODER_ERROR   ,
	PLAYER_ERROR_SUB_DECODER_ERROR     ,
	PLAYER_ERROR_VIDEO_RENDER_ERROR    ,
	PLAYER_ERROR_AUDIO_RENDER_ERROR    ,
	PLAYER_ERROR_SUB_RENDER_ERROR      ,
	PLAYER_ERROR_ACCESS_ERROR          ,
	PLAYER_ERROR_MUXER_ERROR           ,
	PLAYER_ERROR_DUMPER_ERROR          ,
	PLAYER_ERROR_SOURCE_RESTART        ,
} PlayerError;

typedef struct {
	void*       priv;
	void        (*func)(void* priv, PlayerStatus status, PlayerError error);
} GxPlayerEvent;

typedef enum {
	SEEK_ORIGIN_SET     ,
	SEEK_ORIGIN_CUR     ,
	SEEK_ORIGIN_END     ,
	SEEK_ORIGIN_PERCENT ,
} SeekFlag;

typedef struct {
	unsigned int        x;
	unsigned int        y;
	unsigned int        width;
	unsigned int        height;
} PlayerWindow;

__END_DECLS

#endif
