#ifndef __GXBASIC_GRAPH__
#define __GXBASIC_GRAPH__

#include "gxcore.h"

__BEGIN_DECLS

typedef struct _BG_Rect {
	int x, y;
	int w, h;
}BG_Rect;

/*---------------OSD---------------*/

int BG_OSD_On(void);
int BG_OSD_Off(void);
int BG_OSD_Rect(BG_Rect *rect, int color);
int BG_OSD_Matrix(void *data, BG_Rect *rect, int byteperline, int color);
int BG_OSD_Image(void *data, BG_Rect *rect, int bpp);
int BG_OSD_Pixel(int x, int y, int color);
int BG_OSD_SetCLUT(void *data, int number);
void *BG_OSD_GetCLUT(void);

/*---------------SPP---------------*/

int BG_SPP_On(void);
int BG_SPP_Off(void);
int BG_SPP_Rect(BG_Rect *rect, int color);
int BG_SPP_Pixel(int x, int y, int color);
int BG_SPP_Image(void *data, BG_Rect *rect);

/*---------------BLIT---------------*/

int BG_Blit(void);
int BG_Begin(void);

__END_DECLS

#endif /*__GXBASIC_GRAPH__*/


