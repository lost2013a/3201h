#ifndef __GXPLAYER_CONFIG_H__
#define __GXPLAYER_CONFIG_H__

#include "gxplayer_module.h"
#include "gxcore.h"

__BEGIN_DECLS

/******************************* Video Start **********************************/

#define VIDEO_ESV_SD              ( 1024 * 1024 )
#define VIDEO_ESV_HD              ( 4096 * 1024 )
#define VIDEO_FB_SIZE             ( 1920 * 1088 * 1.75 * 12)

#define VIDEO_DISPLAY_SCREEN      ( DISPLAY_SCREEN_16X9 )
#define VIDEO_ASPECT              ( ASPECT_NORMAL )
#define VIDEO_SCREEN_XRES         ( 1920 )
#define VIDEO_SCREEN_YRES         ( 1080 )

#define VIDEO_BRIGHTNESS          ( 50 )
#define VIDEO_SATURATION          ( 50 )
#define VIDEO_CONTRAST            ( 50 )

#define VIDEO_AUTO_ADAPT          ( 1 )
#define VIDEO_AUTO_PAL            ( VIDEO_OUTPUT_PAL )
#define VIDEO_AUTO_NTSC           ( VIDEO_OUTPUT_NTSC_M )

#define VIDEO_USERDATA_ENABLE     ( 0 )
#define VIDEO_USERDATA_LENGTH     ( 1024 )
#define VIDEO_MOSAIC_DROP_GATE    ( 0x7FFFFFFF )
#define VIDEO_MOSAIC_ERROR_GATE   ( 0 )
#define VIDEO_SYNC_FLAG           ( 1 )

#define VIDEO_SUPPORT_PPZOOM      ( 1 )
#define VIDEO_SUPPORT_DEINTERLACE ( 1 )
#define VIDEO_DEINTERLACE_WIDTH   ( 1280 )
#define VIDEO_DEINTERLACE_HEIGHT  ( 720 )

/******************************* Video End ************************************/


/******************************* Audio Start **********************************/

#define AUDIO_ESA_SD   ( 64  * 1024 )
#define AUDIO_ESA_HD   ( 128 * 1024 )

#define AUDIO_PCM_SD   ( 256 * 1024 )
#define AUDIO_PCM_HD   ( 512 * 1024 )


#define AUDIO_AC3_SD   ( AUDIO_ESA_SD )
#define AUDIO_DDP_SD   ( AUDIO_ESA_SD )
#define AUDIO_DTS_SD   ( AUDIO_ESA_SD )
#define AUDIO_AC3_HD   ( AUDIO_ESA_HD )
#define AUDIO_DDP_HD   ( AUDIO_ESA_HD )
#define AUDIO_DTS_HD   ( AUDIO_ESA_HD )

#define AUDIO_DMX_FULL_GATE     ( 1024 )
#define AUDIO_ANTI_ERROR_CODE   ( 1 )
#define AUDIO_SPDIF_SOURCE      ( SAFE_OUTPUT )
#define AUDIO_HDMI_SOURCE       ( SAFE_OUTPUT )
#define AUDIO_TRACK             ( AUDIO_TRACK_STEREO )
#define AUDIO_VOLUME_VALUE      ( 50 )
#define AUDIO_VOLUME_PRIVATE    ( 0 )
#define AUDIO_DOWNMIX           ( 1 )

#define AUDIO_AC3_DEFAULT_MODE  ( AUDIO_AC3_BYPASS_MODE )
#define AUDIO_ENABLE_AC3_SD     ( 1 )
#define AUDIO_ENABLE_AC3_HD     ( 1 )
#define AUDIO_SYNC_FLAG         ( 1 )
#define AUDIO_SPEED_MUTE        ( 0 )

/******************************* Audio End ************************************/


/******************************* Subtitle Start *******************************/

#define SUBTITLE_ESS_SD   ( 64  * 1024 )
#define SUBTITLE_ESS_HD   ( 128 * 1024 )

/***************************** Subtitle End ***********************************/


/******************************* PVR   Start **********************************/

//#define PVR_REC_BUFFER_SD       ( 188 * 1024 * 1  )
//#define PVR_REC_BUFFER_HD       ( 188 * 1024 * 1  )
#define PVR_REC_BUFFER_NDS      ( 188 * 1024 * 20 )

#define PVR_REC_CACHE_SD        ( 188 * 1024 * 5  )
#define PVR_REC_CACHE_HD        ( 188 * 1024 * 20 )

#define PVR_TIME_SHIFT_ENABLE   ( 1 )
#define PVR_TIME_SHIFT_DMXID    ( 0 )
#define PVR_TIME_SHIFT_FILE     ( "/mnt/usb0_1/shift.ts" )

#define PVR_RESERVE_SIZEMB      ( 20 )
#define PVR_VOLUME_SIZEMB       ( 200 )
#define PVR_VOLUME_MAX_NB       ( 0 )
#define PVR_VOLUME_FULLSTOP     ( 0 )

#define ETS_ENCRYPT_ENABLE      ( 1 )
#define ETS_ENCRYPT_KEY_LEN     ( 8 )
#define ETS_ENCRYPT_KEY         ( "gxspd123" )
/******************************* PVR  End **************************************/


/******************************* Player Start **********************************/

#define PLAY_SUPPORT_NDS        ( 0 )
#define PLAY_AUTO_PALY          ( 0 )
#define PLAY_ERROR_STOP         ( 0 )
#define PLAY_FREEZE_SWITCH      ( 1 )
#define PLAY_FREEZE_TIMEOUT     ( 3000000 )

#define PLAY_FREEZE_FB_SD       ( 720  * 576  * 1.75 + 1024 * 2)
#define PLAY_FREEZE_FB_HD       ( 1920 * 1088 * 1.75 + 1024 * 2)
#define PLAY_CACHE_SIZE_SD      ( 1024 * 1024 * 2 )
#define PLAY_CACHE_SIZE_HD      ( 1024 * 1024 * 10 )
#ifdef LINUX_OS
#define PLAY_CACHE_SIZE_NET     ( 1024 * 1024 * 4 )
#else
#define PLAY_CACHE_SIZE_NET     ( 512 * 1024 )
#endif

#define PLAY_DELAY_CACHE_SIZE      ( 0x1000000 )
#define PLAY_DELAY_CACHE_HW_SIZE   ( 0x200000 )
#define PLAY_DELAY_CACHE_TO_MEMORY ( 0x1)
/******************************* Player End ************************************/


__END_DECLS

#endif
