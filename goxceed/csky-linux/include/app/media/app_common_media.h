/**
 *
 * @file        app_common_play.h
 * @brief
 * @version     1.1.0
 * @date        10/19/2012 09:40:49 AM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_MEDIA__H__
#define __APP_COMMON_MEDIA__H__
#ifdef __cplusplus
extern "C" {
#endif

#include "app_media_popmsg.h"
#include "module/player/gxplayer_module.h"
#include "gxservices.h"
#include "msg_enum.h"



//media
#include "media_key.h"
#include "media_string.h"

#include "pmp_setting.h"
#include "pmp_tags.h"
#include "pmp_explorer.h"
#include "pmp_spectrum.h"
#include "pmp_subtitle.h"
#include "pmp_lyrics.h"
#include "pmp_id3.h"

#include "file_view.h"
#include "file_edit.h"
#include "play_manage.h"
#include "play_pic.h"
#include "play_movie.h"
#include "play_music.h"
#include "play_text.h"
#include "app_common_flash.h"
#include "gxapp_sys_config.h"


#ifndef PMP_ATTACH_DVB
#define PMP_ATTACH_DVB
#endif




#define APP_XRES  VIDEO_WINDOW_W
#define APP_YRES  VIDEO_WINDOW_H





#define APP_FREE(x)	if(x){GxCore_Free(x);x=NULL;}

#define APP_CHECK_P(p, r) if(NULL == p){\
							printf("\033[033m");\
							printf("\n[%s: %d] %s\n", __FILE__, __LINE__, __FUNCTION__);\
							printf("%s is NULL\n", #p);\
							printf("\033[0m");\
							return r;}



#define APP_TIMER_ADD(timer, fun, timeout, flag) \
							if(timer){\
								reset_timer(timer);\
							 }else{\
								timer = create_timer(fun, timeout, 0, flag);}

#define APP_TIMER_REMOVE(x)	if(x){remove_timer(x);x=NULL;}


/*string*/
/*#define STR_ID_NO_DEVICE    "No device or not support!"
#define STR_ID_FILE_NOT_SUPPORT    "The file type is not supported!"
#define STR_ID_CONTINUE_VIEW "Continue to watch?"

#define STR_ID_FILE    "File"
#define STR_ID_VIDEO    "Video"
#define STR_ID_MUSIC    "Music"
#define STR_ID_PICTURE    "Picture"
#define STR_ID_TEXT    "Text"
#define STR_ID_WAITING    "Waiting..."
#define STR_ID_COPY    "Copy"
#define STR_ID_CUT    "Cut"
#define STR_ID_PASTE    "Paste"
#define STR_ID_SWITCH_DURA    "Switch Duration"
#define STR_ID_SWITCH_MODE    "Switch Mode"
#define STR_ID_L2R    "Left to Right"
#define STR_ID_R2L    "Right to Left"
#define STR_ID_PLAY_SEQ   "Play Sequence"
#define STR_ID_SEQUENCE    "Sequence"
#define STR_ID_RANDOM    "Random"
#define STR_ID_RESOLUTION    "Resolution"
#define STR_ID_DATE_TIME    "Date Time"
#define STR_ID_CAMERA_MAKE    "Camera Make"
#define STR_ID_CAMERA_MODEL    "Camera Model"
#define STR_ID_FOCAL_LENGTH   "Focal Length"
#define STR_ID_EXPOSURE_TIME  "Exposure Time"
#define STR_ID_QUICK_SEEK    "Quick Seek"
#define STR_ID_AUDIO_CH    "Audio Channel"
#define STR_ID_AUDIO_DELAY    "Audio Delay"
#define STR_ID_LOAD    "Load"
#define STR_ID_VISIBLITY    "Visibility"
#define STR_ID_DELAY    "Delay"
#define STR_ID_FILE_NAME    "File Name"
#define STR_ID_FILE_SIZE    "File Size"
#define STR_ID_CODE_FORMAT    "Code Format"
#define STR_ID_FRAME_RATE    "Frame Rate"
#define STR_ID_TRACK    "TRACK"
#define STR_ID_ONLY_ONCE    "Only once"
#define STR_ID_REPEAT_ONE    "Repeat one"
#define STR_ID_REPEAT_ALL    "Repeat all"
#define STR_ID_VIEW_MODE    "View Mode"
#define STR_ID_LRC    "Lyric"
#define STR_ID_NO_LRC    "No lyric!"
#define STR_ID_SPECTRUM    "Spectrum"
#define STR_ID_ROLL_LINES    "Roll Lines"
#define STR_ID_AUTO_ROLL   "Auto Roll"*/


#define TKGS_SUPPORT 0
#define MINI_256_COLORS_OSD_SUPPORT  0
#define MINI_16_BITS_OSD_SUPPORT  0
#define MINI_16BIT_WIN8_OSD_SUPPORT 0
//#define MENCENT_FREEE_SPACE
#define DLNA_SUPPORT 0
#define EX_SHIFT_SUPPORT 0
#define CA_SUPPORT 0
#define ECM_SUPPORT 0
#define TWO_ECM_SUPPORT 0
#define LOOP_TMS_SUPPORE
#define TTX_PRE_PROCESS_ENABLE 0
#define	PVRBAR_TIMEOUT	8
#define MV_WIN_SUPPORT 1
//#define MEDIA_FILE_EDIT_UNVALID
//#define MEDIA_SUBTITLE_SUPPORT 

//Don't support this in Ecos
#define FILE_EDIT_VALID
#define MEDIA_FILE_EDIT_UNVALID
#define DISK_FORMAT_UNVALID
#define REDIO_RECODE_SUPPORT	1

#ifdef ECOS_OS
#define FILE_EDIT_VALID
#undef DISK_FORMAT_UNVALID
#endif




// pvr control
//#define PVR_TIMESHIFT_FLAG	    0	/*0.time shift off / 1.time shift on*/
//#define PVR_FILE_SIZE_VALUE     2048/*1024 == 1G ,2048 == 2G, 4096 == 4G*/
//#define PVR_DURATION_VALUE      0   /* 0-2Hour ...*/
 

typedef struct {
	PlayerWindow rect;
	int type;
	int handle;
	int num;
	void* data;
}GxMsgProperty_AppSubtitle;



#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_MEDIA__H__*/

