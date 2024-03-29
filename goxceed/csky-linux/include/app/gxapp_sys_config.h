#ifndef _GXAPP_SYS_CONFIG_H_
#define _GXAPP_SYS_CONFIG_H_
  
  
#include "remote_enum.h"
#include "panel_enum.h"
#include "demod_enum.h"
#include "ota_enum.h"
#include "goxceed_csky.h"
#include "chip_enum.h"
#include "theme_enum.h"
#include "tuner_enum.h"
#include "search_prog_enum.h"
#include "gxtype.h"
#include "service/gxplayer.h"
#include "gxprogram_manage_berkeley.h"
#include "app_common_flash.h"
  
#define LANGUAGE_CHINESE ("Chinese")
#define LANGUAGE_ENGLISH ("English")
#define LANGUAGE_PORTUGUESE ("Portuguese")
#define LANGUAGE_SPAINISH ("Spainish")
  
#define WORK_PATH "/dvb/"
#define LOGO_PATH "/dvb/theme/logo.bin"
#define I_FRAME_PATH "/dvb/theme/logo.bin"
#define DVB_JPG_LOGO 1
  
  
#define DVB_CA_MTC 0
  
  
#define USB_FLAG 
#define MBIS_CLIENT_FLAG 0
#define DVB_BAD_SIGNAL_SHOW_LOGO 1
#define DVB_CASCAM_FLAG 0
#define DVB_MEDIA_FLAG 1
#define DVB_PVR_FLAG 1
#define PVR_DURATION_VALUE 0
#define PVR_TIMESHIFT_DEFAULT 0
#define DVB_ZOOM_RESTART_PLAY 0
  
#define DVB_NETWORK_FLAG 1
#define MEDIA_SUBTITLE_SUPPORT 0
#define DVB_CHIP_TYPE GX_CHIP_3113H
#define DVB_DEFINITION_TYPE HD_DEFINITION
#define MENCENT_FREEE_SPACE
#define DVB_THEME_TYPE DVB_THEME_DTMB_MINI_HD
  
  
#define DVB_CUSTOM "newstar"
#define DVB_MARKET "dtmb"
#define DVB_DEMOD_TYPE DVB_DEMOD_ATBM888X
#define DVB_DEMOD_MODE DVB_DEMOD_DTMB
#define DVB_TS_SRC 1
#define DVB_PROGRAM_TYPE PROGRAM_TYPE_FTA
  
#define TUNER_TYPE TUNER_MXL608
#define REMOTE_TYPE KEY_XINSIDA
  
#define PANEL_TYPE PANEL_TYPE_fd650_RUNDE
#define PANEL_CLK_GPIO 33
#define PANEL_DATA_GPIO 33
#define PANEL_STANDBY_GPIO 199
#define PANEL_LOCK_GPIO 33
  
#define DVB_OTA_TYPE DVB_NATIONALCHIP_OTA
#define OTA_PID 0x1e61
#define OTA_TABLEID 0x88
  
  
#define SYSC_MODE 0
#define VIDEO_WINDOW_X 0
#define VIDEO_WINDOW_Y 0
#define VIDEO_WINDOW_W 1024
#define VIDEO_WINDOW_H 576
#define SAT_MAX_NUM 1
#define TP_MAX_NUM 100
#define SERVICE_MAX_NUM 200
#define DVB_DDRAM_SIZE 128
#define PAT_FILTER_TIMEOUT 3000
#define SDT_FILTER_TIMEOUT 5000
#define NIT_FILTER_TIMEOUT 10000
#define PMT_FILTER_TIMEOUT 8000
#define TRICK_PLAY_SUPPORT 0
#define PROG_MAX_LCN 500
#define DVB_CENTER_FRE 714
#define DVB_CENTER_SYMRATE 6875
#define DVB_CENTER_QAM 2
#define DVB_CENTER_BANDWIDTH 8
#define MANUSAL_SEARCH_FREQ_DV 506000
#define MANUSAL_SEARCH_SYMBOL_DV 6875
#define MANUSAL_SEARCH_QAM_DV 2
#define MANUSAL_SEARCH_BANDWIDTH_DV 8
#define MAX_SEARIAL_LEN 20
  
#define DVB_DUAL_MODE 0 
#define DTMB_DVBC_SWITCH_DV 0
  
  
#define LCN_DV 0 
#define DVB_TAXIS_MODE 0
#define SORT_PROG_BY_PAT_DV 1 
#define USER_LIST_DV 0 
#define DVB_HD_LIST 0
  
#define MUTE_GPIO_VALUE 31
#define MUTE_GPIO_LEVEL 1
#define AUDIO_VOLUME_LEVEV 32
#define AUDIO_VOLUME_STEP 3
#define AUDIO_VOLUME_DV 48
#define AUDIO_TRACK_DV AUDIO_TRACK_LEFT
#define AUDIO_AUDIO_TRACK_DV AUDIO_TRACK_LEFT
#define AUDIO_AC3_BYPASS_DV AUDIO_AC3_DECODE_MODE
#define TRACK_GLOBLE_FLAG_DV 1 
#define VOLUMN_GLOBLE_FLAG_DV 1 
#define MUTE_FLAG_DV 0 
#define AUDIO_DOLBY 0
  
#define LANGUAGE_TYPE LANGUAGE_GB2312
#define OSD_LANG_DV LANGUAGE_CHINESE
#define TELTEXT_LANG_DV LANGUAGE_ENGLISH
#define SUBTITLE_LANG_DV LANGUAGE_ENGLISH
#define SUBTITLE_LANG_VALUE 0
#define SUBTITLE_MODE_VALUE 0
#define OSD_TRANS_DV 10
#define VIDEOCOLOR_BRIGHTNESS_DV 50
#define VIDEOCOLOR_SATURATION_DV 50
#define VIDEOCOLOR_CONTRAST_DV 50
#define BAR_TIME_DV 2
#define TIMEZONE_DV 8
#define FACTORY_FLAG_VALUE 0
  
#define VIDEO_DISPLAY_SCREEN_DV DISPLAY_SCREEN_4X3
#define VIDEO_HDMI_MODE_DV VIDEO_OUTPUT_HDMI_1080P_60HZ
#define TV_STANARD_SUPPORT 1
#define VIDEO_ASPECT_DV ASPECT_NORMAL
#define VIDEO_QUIET_SWITCH_DV 1
#define VIDEO_AUTO_ADAPT_DV 0
#define PLAY_TIMER_DURATION 300
#define FRONT_MONITER_DURATION 1000
  
#define PASSWORD_DV "0000"
#define PASSWORD_FLAG_DV 1
#define MAX_PASSWD_LEN 4
#endif
