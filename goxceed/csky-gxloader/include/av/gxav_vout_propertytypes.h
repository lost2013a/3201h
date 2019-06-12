#ifndef __GXAV_VOUT_PROPERTYTYPES_H__
#define __GXAV_VOUT_PROPERTYTYPES_H__

#include "gxav_common.h"

typedef enum {
	GXAV_VOUT_RCA         = (1 << 0),
	GXAV_VOUT_RCA1        = (1 << 1),
	GXAV_VOUT_YUV         = (1 << 2),
	GXAV_VOUT_SCART       = (1 << 3),
	GXAV_VOUT_SVIDEO      = (1 << 4),
	GXAV_VOUT_HDMI        = (1 << 5),
}GxVideoOutProperty_Interface;

typedef enum {
	IFACE_ID_RCA         ,
	IFACE_ID_RCA1        ,
	IFACE_ID_YUV         ,
	IFACE_ID_SCART       ,
	IFACE_ID_SVIDEO      ,
	IFACE_ID_HDMI        ,
	IFACE_ID_MAX         ,
}IfaceID;

typedef enum {
	GXAV_VOUT_PAL = 1                   ,
	GXAV_VOUT_PAL_M                     ,
	GXAV_VOUT_PAL_N                     ,
	GXAV_VOUT_PAL_NC                    ,
	GXAV_VOUT_NTSC_M                    ,
	GXAV_VOUT_NTSC_443                  ,

	GXAV_VOUT_YCBCR_480I                ,
	GXAV_VOUT_YCBCR_576I                ,

	GXAV_VOUT_YPBPR_1080I_50HZ          ,
	GXAV_VOUT_YPBPR_1080I_60HZ          ,

	GXAV_VOUT_YPBPR_480P                ,
	GXAV_VOUT_YPBPR_576P                ,

	GXAV_VOUT_YPBPR_720P_50HZ           ,
	GXAV_VOUT_YPBPR_720P_60HZ           ,
	GXAV_VOUT_YPBPR_1080P_50HZ          ,
	GXAV_VOUT_YPBPR_1080P_60HZ          ,

	GXAV_VOUT_HDMI_480I                 ,
	GXAV_VOUT_HDMI_576I                 ,
	GXAV_VOUT_HDMI_480P                 ,
	GXAV_VOUT_HDMI_576P                 ,
	GXAV_VOUT_HDMI_720P_50HZ            ,
	GXAV_VOUT_HDMI_720P_60HZ            ,
	GXAV_VOUT_HDMI_1080I_50HZ           ,
	GXAV_VOUT_HDMI_1080I_60HZ           ,
	GXAV_VOUT_HDMI_1080P_50HZ           ,
	GXAV_VOUT_HDMI_1080P_60HZ           ,

	GXAV_VOUT_NULL_MAX                  ,
}GxVideoOutProperty_Mode;

typedef enum {
	ASPECT_RATIO_NOMAL = 0,
	ASPECT_RATIO_PAN_SCAN,
	ASPECT_RATIO_LETTER_BOX,
	ASPECT_RATIO_RAW_SIZE,
	ASPECT_RATIO_RAW_RATIO,
	ASPECT_RATIO_4X3_PULL,
	ASPECT_RATIO_4X3_CUT,
	ASPECT_RATIO_16X9_PULL,
	ASPECT_RATIO_16X9_CUT,
	ASPECT_RATIO_4X3,
	ASPECT_RATIO_16X9,
	ASPECT_RATIO_AUTO,
}GxVideoOutProperty_Spec;

typedef enum {
	TV_SCREEN_4X3 = 0,
	TV_SCREEN_16X9
}GxVideoOutProperty_Screen;

typedef enum {
	SCART_CVBS = 0,
	SCART_RGB
}GxVideoOutProperty_Scart;

typedef struct {
#define VOUT_BUF_SIZE (720*576*3)
	unsigned int  enable;
	unsigned char *buf[3];//每个buf：720*576*3,8byte对齐
} GxVideoOutProperty_OutputConfig;

typedef struct {
	int selection;
} GxVideoOutProperty_OutputSelect;

typedef struct {
	GxVideoOutProperty_Interface iface;
	GxVideoOutProperty_Mode      mode;
} GxVideoOutProperty_Resolution;

typedef struct {
	unsigned int auto_en;
	GxVideoOutProperty_Mode auto_pal;
	GxVideoOutProperty_Mode auto_ntsc;
}GxVideoOutProperty_Auto;

typedef struct {
	GxVideoOutProperty_Interface iface;
	unsigned int value;
} GxVideoOutProperty_Brightness;

typedef struct {
	GxVideoOutProperty_Interface iface;
	unsigned int value;
} GxVideoOutProperty_Saturation;

typedef struct {
	GxVideoOutProperty_Interface iface;
	unsigned int value;
} GxVideoOutProperty_Contrast;

typedef struct {
	GxVideoOutProperty_Spec spec;
}GxVideoOutProperty_AspectRatio;

typedef struct {
	GxVideoOutProperty_Screen screen;
}GxVideoOutProperty_TvScreen;

typedef struct {
	GxVideoOutProperty_Interface iface;
	unsigned int enable;
} GxVideoOutProperty_OutDefault;

typedef GxVideoOutProperty_OutDefault GxVideoOutProperty_Power;

typedef struct {
	GxVideoOutProperty_Interface selection;
} GxVideoOutProperty_PowerOff;

typedef struct {
	GxVideoOutProperty_Interface selection;
} GxVideoOutProperty_PowerOn;

typedef struct {
	int status;
#define HDMI_PLUG_OUT	(0)
#define HDMI_PLUG_IN	(1)
} GxVideoOutProperty_OutHdmiStatus;

typedef struct {
	GxAvHdmiEdid audio_codes;
} GxVideoOutProperty_EdidInfo;

typedef struct {
	int hdcp_enable;
} GxVideoOutProperty_HdmiHdcpAuth;

#endif

