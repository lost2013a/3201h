#ifndef __GDI_H__
#define __GDI_H__

#include <stdlib.h>
#include "gxcore.h"

__BEGIN_DECLS

int gdi_enable(int flag);

int gdi_fillrect(void *rect, unsigned int color);

int gdi_draw_matrix(void *data, void *rect, int byteperline, int color);

int gdi_image_data(void *data, int x, int y, int w, int h, int bpp);

int gdi_setpixel(int x, int y, int color);

int gdi_set_clut(void *data, int number);

void *gdi_get_clut(void);

int gdi_image_enable(int flag);

int gdi_image_rect(void *rect, int color);

int gdi_image_pixel(int x, int y, int color);

int gdi_draw_image(void *data, void *rect);

int gdi_begin(void);

int gdi_end(void);

int gdi_commit(void);

int gdi_lock(void);

int gdi_unlock(void);

__END_DECLS

#endif /*__GDI_H__*/

