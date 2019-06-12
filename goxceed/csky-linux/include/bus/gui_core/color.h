#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdbool.h>
#include "gui_private.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef unsigned char         u8;
typedef unsigned short        u16;
typedef unsigned short        U16;
typedef unsigned int          u32;
typedef bool            BOOL;

/*Define some inline function for conversion from on color format to anoter.*/

#define PIXEL_GREY(r,g,b) (u8)(((u16)r*77 + (u16)g*150 + (u16)b*29) >> 8)

int hexToInt(const char *string);

int getColorFromString(const char *input, int *color);

GuiClut* gui_set_color_from_pal(const char *filename);
int gui_set_clut(void *surface, Color *colors, int firstcolor, int ncolors);
int gui_set_osdalpha_color(Color color, int alpha);
int gui_get_color(const char *color_name, int default_color);
int gui_set_alpha(unsigned int value);

u8 R565( u16 clr );
u8 G565( u16 clr );
u8 B565( u16 clr );
u32 RGB32( u8 r, u8 g, u8 b );
u32 ARGB32( u8 a, u8 r, u8 g, u8 b );
u16  _8_to_565(  const  Color  * pal, u16 index );
void _8_to_24 (  const  Color  *pal, u16 index, u8 *r, u8 *g, u8 *b );
u32  _8_to_32 (  const  Color  * pal, u16 index );

u8 _565_to_8( u16 clr );
void  _565_to_24( u16 clr, u8 *r, u8* g, u8* b );
u32 _565_to_32( u16 clr );

u8 _24_to_8( u8 r, u8 g, u8 b );
u16 _24_to_565( u8 r, u8 g, u8 b );
u32 _24_to_32( u8 r, u8 g, u8 b );

u8 _32_to_8( u32 clr );
u16 _32_to_565( u32 clr );
void _32_to_24( u32 clr, u8  *r, u8  *g, u8  *b );

__END_DECLS

#endif

