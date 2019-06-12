#ifndef __GXAV_VPU_PROPERTYTYPES_H__
#define __GXAV_VPU_PROPERTYTYPES_H__

#include "gxav_common.h"

typedef enum {
	GX_LAYER_OSD,
	GX_LAYER_VPP,
	GX_LAYER_SPP,
	GX_LAYER_SOSD,
	GX_LAYER_BKG,
	/*just for capture*/
	GX_LAYER_MIX_VPP_BKG,
	GX_LAYER_MIX_SPP_BKG,
	GX_LAYER_MIX_ALL,
}GxLayerID;

typedef enum {
	GX_LAYER_VIDEO_MODE_MPEG2,
	GX_LAYER_VIDEO_MODE_H264
} GxLayerVideoMode;

typedef enum {
	GX_SURFACE_MODE_IMAGE,
	GX_SURFACE_MODE_VIDEO
} GxSurfaceMode;

typedef enum {
	GX_ALPHA_GLOBAL,
	GX_ALPHA_PIXEL,
}GxAlphaType;

typedef struct {
	GxAlphaType        type;
	unsigned int       value;
	unsigned char      entry[256];//像素透明低索引表，目前只对3200 5551起作用
}GxAlpha;

typedef enum   {
	GX_COLOR_FMT_CLUT1 = 0, //0
	GX_COLOR_FMT_CLUT2,     //1
	GX_COLOR_FMT_CLUT4,     //2
	GX_COLOR_FMT_CLUT8,     //3
	GX_COLOR_FMT_RGBA4444,  //4
	GX_COLOR_FMT_RGBA5551,  //5
	GX_COLOR_FMT_RGB565,    //6
	GX_COLOR_FMT_RGBA8888,  //7
	GX_COLOR_FMT_ABGR8888,  //7
	GX_COLOR_FMT_RGB888,    //8
	GX_COLOR_FMT_BGR888,    //9

	GX_COLOR_FMT_ARGB4444, //10
	GX_COLOR_FMT_ARGB1555,  //11
	GX_COLOR_FMT_ARGB8888,  //12

	GX_COLOR_FMT_YCBCR422,  //13
	GX_COLOR_FMT_YCBCRA6442,//14
	GX_COLOR_FMT_YCBCR420,  //15

	GX_COLOR_FMT_YCBCR420_Y_UV, //16
	GX_COLOR_FMT_YCBCR420_Y_U_V,//17
	GX_COLOR_FMT_YCBCR420_Y,    //18
	GX_COLOR_FMT_YCBCR420_U,    //19
	GX_COLOR_FMT_YCBCR420_V,    //20
	GX_COLOR_FMT_YCBCR420_UV,   //21

	GX_COLOR_FMT_YCBCR422_Y_UV, //22
	GX_COLOR_FMT_YCBCR422_Y_U_V,//23
	GX_COLOR_FMT_YCBCR422_Y,    //24
	GX_COLOR_FMT_YCBCR422_U,    //25
	GX_COLOR_FMT_YCBCR422_V,    //26
	GX_COLOR_FMT_YCBCR422_UV,   //27

	GX_COLOR_FMT_YCBCR444,      //28
	GX_COLOR_FMT_YCBCR444_Y_UV, //29
	GX_COLOR_FMT_YCBCR444_Y_U_V,//30
	GX_COLOR_FMT_YCBCR444_Y,    //31
	GX_COLOR_FMT_YCBCR444_U,    //32
	GX_COLOR_FMT_YCBCR444_V,    //33
	GX_COLOR_FMT_YCBCR444_UV,   //34

	GX_COLOR_FMT_YCBCR400,      //35
	GX_COLOR_FMT_A8,            //36
	GX_COLOR_FMT_ABGR4444,      //37
	GX_COLOR_FMT_ABGR1555,      //39
	GX_COLOR_FMT_Y8,            //40
	GX_COLOR_FMT_UV16,          //41
	GX_COLOR_FMT_YCBCR422v,     //42
	GX_COLOR_FMT_YCBCR422h,     //43
	GX_COLOR_FMT_YUVA8888,      //44
} GxColorFormat;

typedef union  {
	struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
	struct {
		unsigned char y;
		unsigned char cb;
		unsigned char cr;
		unsigned char alpha;
	};
	unsigned char entry;
} GxColor;

typedef enum {
	GX_GAMODE_BATCH,
	GX_GAMODE_FLOW
}GxGAMode;

typedef struct {
	unsigned int num_entries;
	GxColor      *entries;
}GxPalette;

typedef struct {
	unsigned int 	width;
	unsigned int 	height;
	void*             buffer;
	GxColorFormat   color_format;
}GxSurface;

/*==============================================================
  |     _________      |                    |                    |
  |    |         |     |                    |                    |
  |    |         |     |   _________        |        _________   |
  |    |         |     |  |         |       |       |         |  |
  |    |_________|     |  |         |       |       |         |  |
  |                    |  |    ***********  |  ***********    |  |
  |    ***********     |  |____*____|    *  |  *    |____*____|  |
  |    *         *     |       *         *  |  *         *       |
  |    *         *     |       *         *  |  *         *       |
  |    *         *     |       ***********  |  ***********       |
  |    ***********     |                    |                    |
  |                    |                    |                    |
  |       Basic        |      TopLeft       |       TopRight     |
  |                    |                    |                    |
  |====================|====================|=====================
  |                    |                    |                    |
  |                    |                    |                    |
  |                    |       ***********  |  ***********       |
  |                    |       *         *  |  *         *       |
  |  src_rect: ******  |   ____*____     *  |  *     ____*____   |
  |                    |  |    *    |    *  |  *    |    *    |  |
  |                    |  |    *****|*****  |  *****|*****    |  |
  |  dst_rect: ------  |  |         |       |       |         |  |
  |                    |  |_________|       |       |_________|  |
  |                    |                    |                    |
  |                    |     BottomLeft     |    BottomRight     |
  |                    |                    |                    |
  ==============================================================*/
typedef enum {
	GX_BLIT_TOPLEFT_MODE    = 0,
	GX_BLIT_TOPRIGHT_MODE   = 1,
	GX_BLIT_BOTTOMLEFT_MODE = 2,
	GX_BLIT_BOTTOMRIGHT_MODE= 3,
} GxBlitCopyMOde;

typedef enum {
	MODULAT_CHANNEL_RGB_WITH_REGCOLOR_ALPHA,
	MODULAT_CHANNEL_RGB_WITH_REGCOLOR_RGB,
	MODULAT_CHANNEL_ALPHA_WITH_REGCOLOR_ALPHA,
	MODULAT_CHANNEL_RGB_WITH_CHANNEL_ALPHA,
} PreMultiplyMode;

typedef struct {
	unsigned int	premultiply_en;
	unsigned int	reg_color;/*RGBA8888*/
	unsigned int	step1_en;
	PreMultiplyMode	step1_mode;
	unsigned int	step2_en;
	PreMultiplyMode	step2_mode;
	unsigned int	step3_en;
	PreMultiplyMode	step3_mode;
} GxBlitModulator;

typedef struct {
	/*surface info*/
	void*			surface;
	unsigned int	is_ksurface;
	/*color convert table info*/
	void*			cct;
	unsigned int	is_kcct;
	GxColorFormat	dst_format;
	/*rect and global alpha info*/
	GxAvRect		rect;
	unsigned int	alpha;
	unsigned int	alpha_en;
	/*modulator info*/
	GxBlitModulator modulator;
} GxBlitObject;

typedef enum {
	GX_BLIT_COLORKEY_BASIC_MODE     = 0,
	GX_BLIT_COLORKEY_REPLACE_MODE   = 2,
	GX_BLIT_COLORKEY_MASK_MODE      = 3,
}GxBlitColorKeyMode;

typedef struct {
	unsigned int        src_colorkey_en;
	unsigned int        src_colorkey;
	unsigned int        src_colorkey_has_alpha;
	unsigned int        dst_colorkey_en;
	unsigned int        dst_colorkey;
	unsigned int        dst_colorkey_has_alpha;
	unsigned int        reg_color;/*RGBA8888*/
	GxBlitColorKeyMode  mode;
} GxBlitColorKeyInfo;

typedef enum  {
	/* ROP operations */
	GX_ALU_ROP_CLEAR     = 0,
	GX_ALU_ROP_COPY         ,
	GX_ALU_ROP_AND          ,
	GX_ALU_ROP_AND_INVERT   ,
	GX_ALU_ROP_AND_REVERSE  ,
	GX_ALU_ROP_OR           ,
	GX_ALU_ROP_OR_INVERT    ,
	GX_ALU_ROP_OR_REVERSE   ,
	GX_ALU_ROP_NOOP         ,
	GX_ALU_ROP_INVERT       ,
	GX_ALU_ROP_COPY_INVERT  ,
	GX_ALU_ROP_NAND         ,
	GX_ALU_ROP_NOR          ,
	GX_ALU_ROP_XOR          ,
	GX_ALU_ROP_EQUIV        ,
	GX_ALU_ROP_SET          ,
	GX_ALU_ROP_EXTEND       ,

	/* PorterDuff operations(Alpha mix) */
	GX_ALU_MIX_CLEAR        ,
	GX_ALU_MIX_A            ,
	GX_ALU_MIX_B            ,
	GX_ALU_MIX_A_OVER_B     ,
	GX_ALU_MIX_B_OVER_A     ,
	GX_ALU_MIX_A_IN_B       ,
	GX_ALU_MIX_B_IN_A       ,
	GX_ALU_MIX_A_OUT_B      ,
	GX_ALU_MIX_B_OUT_A      ,
	GX_ALU_MIX_A_TOP_B      ,
	GX_ALU_MIX_B_TOP_A      ,
	GX_ALU_MIX_A_XOR_B  = 28,
	GX_ALU_MIX_NONE     = 31,
	GX_ALU_MIX_ADD      = 32,
	GX_ALU_MIX_TRUE,

	/* NC private */
	GX_ALU_VECTOR_FONT_COPY ,
}GxAluMode;

typedef enum {
	VP_UDEF,
	VP_1X,
	VP_2X,
	VP_HALF,
	VP_FS,
	VP_PAN_SCAN,
	VP_LETTER_BOX,
	VP_RAW_SIZE,
	VP_RAW_RATIO,
	VP_4X3_PULL,
	VP_4X3_CUT,
	VP_16X9_PULL,
	VP_16X9_CUT,
	VP_4X3,
	VP_16X9,
	VP_AUTO,
}GxVpSpec;

typedef enum {
	ZOOM_0TIMES,
	ZOOM_1TIMES,
	ZOOM_2TIMES,
}GxZoomMode;

typedef enum {
	SCREW_0  ,
	SCREW_90 ,
	SCREW_270,
	SCREW_180,
}GxScrewMode;

typedef enum {
	REVERSE_NO        ,
	REVERSE_HORIZONTAL,
	REVERSE_VERTICAL  ,
}GxReverseMode;

typedef enum {
	SCREEN_4X3 ,
	SCREEN_16X9,
}GxTvScreen;

/********************property types ******************************************/

typedef struct {
	GxLayerID           layer;
	GxAvRect            rect;
}GxVpuProperty_LayerViewport;

typedef struct {
	GxLayerID           layer;
	GxAvRect            rect;
}GxVpuProperty_LayerClipport;

typedef struct {
	GxLayerID           layer;
	void *              surface;
}GxVpuProperty_LayerMainSurface;

typedef GxVpuProperty_LayerMainSurface GxVpuProperty_UnsetLayerMainSurface;

typedef struct {
	GxLayerID           layer;
	int                 enable;
}GxVpuProperty_LayerEnable;

typedef struct {
	GxLayerID           layer;
	int                 enable;
}GxVpuProperty_LayerAntiFlicker;

typedef struct {
	GxLayerID           layer;
	int                 enable;
}GxVpuProperty_LayerOnTop;

typedef struct {
	GxLayerID           layer;
	GxLayerVideoMode    mode;
}GxVpuProperty_LayerVideoMode;

typedef struct {
	GxLayerID           layer;
	GxAvRect            rect;
	void*               surface;
}GxVpuProperty_LayerCapture;

typedef struct {
	void*               surface;
	unsigned int        width;
	unsigned int        height;
	GxColorFormat       format;
	GxSurfaceMode       mode;
	void*               buffer;
}GxVpuProperty_CreateSurface;

typedef struct {
	void*               surface;
	unsigned int        width;
	unsigned int        height;
	GxColorFormat       format;
	GxSurfaceMode       mode;
	void*               buffer;
}GxVpuProperty_ReadSurface;

typedef struct {
	GxPalette  *         palette;
	unsigned int         palette_num;
	unsigned int        num_entries;
}GxVpuProperty_CreatePalette;

typedef struct {
	GxPalette  *         palette;
}GxVpuProperty_DestroyPalette;

typedef struct {
	GxPalette  *         k_palette;
	int                  palette_id;
	GxPalette  *         u_palette;
}GxVpuProperty_RWPalette;

typedef struct {
	GxPalette  *         k_palette;
	GxColor             *entries;
}GxVpuProperty_GetEntries;

typedef struct {
	void *              surface;
}GxVpuProperty_DestroySurface;

typedef struct {
	void*               src_surface;
	unsigned int        src_is_ksurface;
	GxAvRect            src_rect;
	void*               dst_surface;
	unsigned int        dst_is_ksurface;
	GxAvRect            dst_rect;
	GxScrewMode         screw;
	GxReverseMode       reverse;
}GxVpuProperty_TurnSurface;

typedef struct {
	void*               src_surface;
	unsigned int        src_is_ksurface;
	GxAvRect            src_rect;
	void*               dst_surface;
	unsigned int        dst_is_ksurface;
	GxAvRect            dst_rect;
}GxVpuProperty_ZoomSurface;

typedef struct {
	void               *src_buf_Y;
	void               *src_buf_U;
	void               *src_buf_V;
	GxColorFormat       src_color;
	unsigned int        src_width;
	unsigned int        src_height;
	unsigned int        src_base_width;
	void               *dst_surface;
	GxAvRect            dst_rect;
}GxVpuProperty_Complet;

typedef struct {
	void*               surface;
	GxPalette           palette;
}GxVpuProperty_Palette;


typedef struct {
	void*               surface;
	GxPalette       *palette;
}GxVpuProperty_SurfaceBindPalette;

typedef struct {
	void *              surface;
	GxAlpha             alpha;
}GxVpuProperty_Alpha;

typedef struct {
	unsigned int		covermode_en;
	unsigned int		vpp_alpha_value;
	GxAlpha             spp_alpha;
}GxVpuProperty_LayerMixConfig;

typedef struct {
	void *              surface;
	GxColorFormat       format;
}GxVpuProperty_ColorFormat;

typedef struct {
	void *              surface;
	GxColor             color;
	int                 enable;
}GxVpuProperty_ColorKey;

typedef struct {
	void *              surface;
	GxColor             color;
}GxVpuProperty_BackColor;

typedef struct {
	void *              surface;
	GxAvPoint           point;
	GxColor             color;
}GxVpuProperty_Point;

typedef struct {
	void *              surface;
	GxAvPoint           start;
	GxAvPoint           end;
	GxColor             color;
	unsigned int        width;
}GxVpuProperty_DrawLine;

typedef struct {
	GxBlitObject        srca;
	GxBlitObject        srcb;
	GxBlitObject        dst;
	GxAluMode           mode;
	GxBlitCopyMOde      copy_mode;
	GxBlitColorKeyInfo  colorkey_info;
}GxVpuProperty_Blit;


/*
 * Flags controlling blitting commands.
 */
typedef enum {
	GXBLIT_NOFX                   = 0x00000000, /* uses none of the effects */
	GXBLIT_BLEND_ALPHACHANNEL     = 0x00000001, /* enables blending and uses
												   alphachannel from source */
	GXBLIT_BLEND_COLORALPHA       = 0x00000002, /* enables blending and uses
												   alpha value from color */
	GXBLIT_COLORIZE               = 0x00000004, /* modulates source color with
												   the color's r/g/b values */
	GXBLIT_SRC_COLORKEY           = 0x00000008, /* don't blit pixels matching the source color key */
	GXBLIT_DST_COLORKEY           = 0x00000010, /* write to destination only if the destination pixel
												   matches the destination color key */
	GXBLIT_SRC_PREMULTIPLY        = 0x00000020, /* modulates the source color with the (modulated)
												   source alpha */
	GXBLIT_DST_PREMULTIPLY        = 0x00000040, /* modulates the dest. color with the dest. alpha */
	GXBLIT_DEMULTIPLY             = 0x00000080, /* divides the color by the alpha before writing the
												   data to the destination */
	GXBLIT_DEINTERLACE            = 0x00000100, /* deinterlaces the source during blitting by reading
												   only one field (every second line of full
												   image) scaling it vertically by factor two */
	GXBLIT_SRC_PREMULTCOLOR       = 0x00000200, /* modulates the source color with the color alpha */
	GXBLIT_XOR                    = 0x00000400, /* bitwise xor the destination pixels with the
												   source pixels after premultiplication */
	GXBLIT_INDEX_TRANSLATION      = 0x00000800, /* do fast indexed to indexed translation,
												   this flag is mutual exclusive with all others */
	GXBLIT_ROTATE90               = 0x00002000, /* rotate the image by 90 degree */
	GXBLIT_ROTATE180              = 0x00001000, /* rotate the image by 180 degree */
	GXBLIT_ROTATE270              = 0x00004000, /* rotate the image by 270 degree */
	GXBLIT_COLORKEY_PROTECT       = 0x00010000, /* make sure written pixels don't match color key (internal only ATM) */
	GXBLIT_SRC_COLORKEY_EXTENDED  = 0x00020000, /* use extended source color key */
	GXBLIT_DST_COLORKEY_EXTENDED  = 0x00040000, /* use extended destination color key */
	GXBLIT_SRC_MASK_ALPHA         = 0x00100000, /* modulate source alpha channel with alpha channel from source mask,
												   see also IDirectFBSurface::SetSourceMask() */
	GXBLIT_SRC_MASK_COLOR         = 0x00200000, /* modulate source color channels with color channels from source mask,
												   see also IDirectFBSurface::SetSourceMask() */
	GXBLIT_SOURCE2                = 0x00400000, /* use secondary source instead of destination for reading */
	GXBLIT_FLIP_HORIZONTAL        = 0x01000000, /* flip the image horizontally */
	GXBLIT_FLIP_VERTICAL          = 0x02000000, /* flip the image vertically */
	GXBLIT_ROP                    = 0x04000000, /* use rop setting */
	GXBLIT_SRC_COLORMATRIX        = 0x08000000, /* use source color matrix setting */
	GXBLIT_SRC_CONVOLUTION        = 0x10000000  /* use source convolution filter */
} GXDFBSurfaceBlittingFlags;


enum {
	DESTINATION    = 0x00000001,
	FILLCOLOR      = 0x00000002,
	BLEND_MODE     = 0x00000004,
	ROP_MODE       = 0x00000008,

	SOURCE         = 0x00000010,
	SOURCE2        = 0x00000020,

	SRC_COLORKEY   = 0x00000100,
	DST_COLORKEY   = 0x00000200,
	ALL            = 0x0000033F
};

typedef struct {
	GxVpuProperty_Blit  basic;

	GXDFBSurfaceBlittingFlags blittingflags;
	unsigned int valid;
	GxAluMode    rop_mode;
	GxColor      color;
	int          ifscale;
}GxVpuProperty_DfbBlit;

#define MAX_BATCHBLIT_NUMS 256
typedef struct {
	GxVpuProperty_Blit  basic;
	GxAvRect        srcs[MAX_BATCHBLIT_NUMS];
	GxAvRect        dsts[MAX_BATCHBLIT_NUMS];

	GXDFBSurfaceBlittingFlags   blittingflags;
	unsigned int    valid;
	GxAluMode       rop_mode;
	GxColor         color;
	int             ifscale;
	int             num;
}GxVpuProperty_BatchDfbBlit;

typedef struct {
	void *              surface;
	unsigned int        is_ksurface;
	GxAvRect            rect;
	GxColor             color;
	GxBlitColorKeyInfo  colorkey_info;
	/* just use _MIX_ mode */
	int                 blend_en;
	int                 draw_XOR_en;
	GxAluMode           blend_mode;
} GxVpuProperty_FillRect;

typedef struct {
	void *              surface;
	GxAvRect            rect;
	GxColor             fill_color;
	GxColor             verge_color;
} GxVpuProperty_FillPolygon;

typedef struct {
	GxGAMode            mode;
} GxVpuProperty_SetGAMode;

typedef struct {
	unsigned int        dummy;
} GxVpuProperty_WaitUpdate;

typedef struct {
	unsigned int        max_job_num;
} GxVpuProperty_BeginUpdate;

typedef struct {
	unsigned int        dummy;
} GxVpuProperty_EndUpdate;

typedef struct {
	void               *surface;
	void               *dst_surface;
	GxPalette           src_palette;
	GxColorFormat       dst_format;
} GxVpuProperty_ConvertColor;

typedef struct {
	unsigned int        xres;
	unsigned int        yres;
} GxVpuProperty_Resolution;

typedef struct {
	GxVpSpec	AspectRatio;
} GxVpuProperty_AspectRatio;

typedef struct {
	GxTvScreen Screen;
} GxVpuProperty_TvScreen;

typedef GxVpuProperty_Resolution GxVpuProperty_VirtualResolution ;

typedef struct {
	int                 enable;
} GxVpuProperty_VbiEnable;

typedef struct {
	void *              buffer;
	unsigned int        unit_data_len;
	unsigned int        unit_num;
} GxVpuProperty_VbiCreateBuffer;

typedef GxVpuProperty_VbiCreateBuffer GxVpuProperty_VbiDestroyBuffer ;

typedef struct {
	void*               read_address;
} GxVpuProperty_VbiReadAddress;

typedef struct {
	void *              buffer;
	unsigned int        size;
} GxVpuProperty_GetFrameBuffer;


//double buffer
#define GXVPU_MAX_SURFACE_NUM (2)
typedef struct {
	GxLayerID  layer;
	void      *surfaces[GXVPU_MAX_SURFACE_NUM];
} GxVpuProperty_RegistSurface;

typedef GxVpuProperty_RegistSurface GxVpuProperty_UnregistSurface;

typedef struct {
	GxLayerID  layer;
	void      *idle_surface;
} GxVpuProperty_GetIdleSurface;

typedef struct {
	GxLayerID  layer;
	void      *surface;
} GxVpuProperty_FlipSurface;

#endif

