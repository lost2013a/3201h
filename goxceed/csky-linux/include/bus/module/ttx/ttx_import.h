#ifndef __COM_TTX_IMPORT_H__
#define __COM_TTX_IMPORT_H__

#include <gxtype.h>
#include "av/gxav_vpu_propertytypes.h"
#include "gdi_core.h"
#include "gxcore.h"

__BEGIN_DECLS

#define TTX_MAX_BLIT_COUNT		(500)
#define TTX_FREE(p) if(NULL != p) {GxCore_Free(p); p = NULL; }

typedef struct _TtxDrawNode
{
	void *surface;
	struct _TtxDrawNode *next;
}TtxDrawNode;

typedef struct _TtxCommitJob
{
	int total_num;
	TtxDrawNode *list_head;
	TtxDrawNode *list_tail;
}TtxCommitJob;

typedef struct _TtxPalette
{
	GxVpuProperty_CreatePalette *palette;
	struct _TtxPalette *next;
}TtxPalette;

typedef struct _TtxCreatePalette
{
	int num_palette;
	TtxPalette *head;
	TtxPalette *tail;
}TtxCreatePalette;

typedef struct {
	uint16_t                x;
	uint16_t                y;
	uint16_t                width;
	uint16_t                heigth;
} TtxCCRect;

typedef struct{
	int32_t                 dev;
	handle_t                spp;
	void*                   surface;
	TtxCCRect               rect;
	void*                   old_surface;
	bool                    old_top;
	bool                    old_enable;
	bool                    ntsc_flag;
	TtxCCRect               RecoverRect;
	uint16_t               *buf;
	GuiSurface             *gui_surface;
}TtxCCSpp;

void ttx_api_thread_delay(uint32_t millisecond );



void ttx_sib_osd_draw_text(
		uint32_t nDstPositionX,
		uint32_t nDstPositionY,
		uint32_t nWidth,
		uint32_t nHeight,
		const uint8_t* pData,
		uint32_t nFrontColor,
		uint32_t nBackColor);



void ttx_api_osd_draw_text(
		uint32_t nDstPositionX,
		uint32_t nDstPositionY,
		uint32_t nWidth,
		uint32_t nHeight,
		const uint8_t* pData,
		uint32_t nFrontColor,
		uint32_t nBackColor);


void ttx_spp_draw_text( uint32_t DstPositionX,
		uint32_t DstPositionY,
		uint32_t Width,
		uint32_t Height,
		const uint8_t  *pData,
		uint32_t FrontColor,
		uint32_t BackColor);
void ttx_spp_open(TtxCCRect* rect);
void ttx_spp_close(void);

void ttx_spp_fill_rect(uint32_t y,uint32_t color);
void ttx_spp_clear(uint32_t color);
int ttx_hd_fillrect(int16_t x, int16_t y,uint16_t w,uint16_t h,unsigned int color);

void ttx_record_stb_palette(void);
int ttx_set_stb_palette(void);
int ttx_set_ttx_palette(void);
int ttx_hd_init(void);
int ttx_hd_exit(void);

void ttx_spp_enable(void);
void ttx_spp_disable(void);
void ttx_osd_enable(void);
void ttx_osd_disable(void);
int ttx_hd_new_blit_list(void);
int ttx_hd_end_blit_list(void);

__END_DECLS

#endif /* __COM_TTX_IMPORT_H__ */

