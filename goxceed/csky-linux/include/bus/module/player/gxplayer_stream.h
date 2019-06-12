#ifndef __GXPLAYER_STREAM_H__
#define __GXPLAYER_STREAM_H__

#include "gxplayer_common.h"

typedef struct {
	int pid;
	int type;
}GxStreamStreamSwitch;

typedef struct {
	int num;
	int pid[GXPLAYER_MAX_EXT_TRACK];
}GxStreamTrackAdd;

typedef struct {
	int num;
	int pid[GXPLAYER_MAX_EXT_TRACK];
}GxStreamTrackDel;

#endif
