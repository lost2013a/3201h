#ifndef __IMG_H__
#define __IMG_H__

#include "types.h"
#include "gdi_play.h"
#include "gdi_core.h"
#include "common/list.h"

__BEGIN_DECLS

typedef enum {
	BMP_TYPE,
	JPEG_TYPE,
	GIF_TYPE,
	PNG_TYPE,
	TIFF_TYPE,
	MPEG_TYPE,
	FILE_TYPE,
	UNKOWN_TYPE
}image_type;

typedef enum {
	EFFECT_SRC_TO_DST = 0,
	EFFECT_COPY,
	EFFECT_SRC_AND_DST
}image_effect;


enum load_mode {
	NO_LOAD  = 0,     // 不自动加载片
	DELAY_LOAD = 1,  // 延迟加载图片
};

typedef struct image_file_node image_file_node;
typedef struct _image_desc {
	unsigned int hot;
	int ref;
	char *filename;
	int  hw_accel;

	void *data;
	GxHwMallocObj *vq;
	int xoff;
        int yoff;
	int width;
	int height;
	int bpp;
	GxColorFormat fmt;

	void *pal;
	image_type type;
	int pal_index;
	int bkgd;
	int color;
	int size;
	int alpha;
	image_effect effect;
	enum load_mode load_mode;
	image_file_node *ops;
	struct gxlist_head head;
}image_desc;

#define MAX_FILE_TYPE      (4)

#define IMAGE_1_BPP         (1)
#define IMAGE_8_BPP         (8)
#define IMAGE_16_BPP        (16)
#define IMAGE_24_BPP        (24)
#define IMAGE_32_BPP        (32)

typedef int (*image_covert)(const image_desc *image, int i, int j);

typedef int         (*gal_image_cb)(void *dst, const char *filename, int x, int y, int screen_width, int screen_height);
typedef int         (*gal_image_stop_cb)(void);
typedef image_desc *(*gal_image_load_cb)(image_desc *desc, const char *filename);
typedef int         (*gal_image_free)(void *data);
typedef int         (*gal_image_getinfo)(const char *filename, Image_Exif *img_info);

struct image_file_node {
	char *file_type[MAX_FILE_TYPE];
	image_type type;

	gal_image_cb            img_cb;
	gal_image_load_cb       img_load_cb;
	gal_image_getinfo       img_get_info_cb;
	gal_image_free          img_free;
	gal_image_stop_cb       img_stop;
	struct image_file_node *reserve;
};

image_desc *gal_img_new(void);
void *gal_img_alloc_memory(image_desc *desc);
void  gal_img_free_memory(image_desc *desc);
image_desc *gal_img_load(image_desc *desc, const char *filename);
int gal_img_release(image_desc *img);
int gal_img_cleanup(image_desc *img);

int gal_img_get_width(const char *filename);
int gal_img_get_height(const char *filename);

void gal_set_default_desc(const image_desc * pDesc);
int gal_img_file       (void *screen, const char *filename, int x, int y, int screen_width, int screen_height);
int gal_img_desc(void *screen, const image_desc *pDesc, int x, int y, int w, int h);
int gal_img_stretch(GuiSurface *surface, const image_desc *pDesc, GAL_Rect *src_rect, GAL_Rect *dst_rect);
int gal_set_clut       (void *screen, const image_desc * pDesc);
int gal_set_logic_clut (void *screen, const image_desc * pDesc);
int gal_background_desc(void *screen, const image_desc * pDesc);

int gal_get_clut_index(void);
int gal_set_clut_index(int pal_index);
image_desc *gal_get_background(void);

int gal_get_img_flag(void);
int gal_enable_img(int flag);
int gal_rgb2yuv(int color);

//void imgs_add_img(GuiImgs* img, const char* id, const char *value, int flag);
int image_convert2current(image_desc *image);
int GDI_ColorSpaceConvert(image_desc *image);

/*Special*/
image_desc *IMG_JPEG_Load_and_Zoom(const char *filename, int zw, int zh);
image_desc *IMG_JPEG_Load_and_Cut (const char *filename, int zw, int zh);
image_desc *Own_IMG_PNG_Load      (const char *filename, int color);


static inline unsigned short YUV2YUV422(int yuv, int index)
{
	if(index % 2)
		return ((yuv >> 8) & 0x0000FF00) | (yuv & 0x000000FF);
	else
		return yuv >> 8;
}

int check_cpu(void);

extern unsigned short FILE_Read16(const FILE* filename);
extern unsigned int FILE_Read32(const FILE* filename);
extern unsigned int FILE_Seek(const FILE* filename, int pos);

void convert_rgb_2_yuv422(void* pin, void* pout, unsigned int width, unsigned int height, unsigned int bpp, void *pclut);
int gal_add_palette(const char *pal_name);

/* BMP */
image_desc *IMG_BMP_Load(image_desc *desc, const char *filename);

int IMG_BMP_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_BMP_GetInfo(const char *filename, Image_Exif *img_info);
int IMG_BMP_STOP(void);

/* JPEG */
image_desc *IMG_JPEG_Load(image_desc *desc, const char *filename);
int IMG_JPEG_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_JPEG_GetInfo(const char *filename, Image_Exif *img_info);
int IMG_JPEG_STOP(void);

image_desc *IMG_JPEG_SOFT_Load(image_desc *desc, const char *filename);
int IMG_JPEG_SOFT_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_JPEG_SOFT_STOP(void);

/* PNG */
image_desc *IMG_PNG_Load(image_desc *dec, const char *filename);
int IMG_PNG_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_PNG_GetInfo(const char *filename, Image_Exif *img_info);

/* GIF */
typedef struct _GIF_Image {
	int img_top;
	int img_left;
	int img_width;
	int img_height;
	int disposal;
	int delaytime;
	int num_color;
	int enable_trans;
	int color_key_index;
	Color img_trans;
	Color *img_pal;
	unsigned char *img_data;
	struct _GIF_Image *next;
} GIF_Image;

typedef struct _GIF_Para {
	int screen_width;
	int screen_height;
	int bpp;
	int num_color;
	Color *pal;
	Color backcolor;
	GIF_Image *each_image;
	GIF_Image *cur_image;
} GIF_Para;

image_desc *IMG_GIF_Load(image_desc *desc, const char *filename);
int IMG_GIF_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_GIF_Stop(void);
int IMG_GIF_Free(void *data);
int IMG_GIF_GetInfo(const char *filename, Image_Exif *img_info);

/* TIFF */
image_desc *IMG_TIFF_Load(image_desc *desc, const char *filename);
int IMG_TIFF_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_TIFF_GetInfo(const char *filename, Image_Exif *img_info);

/* MPEG */
image_desc *IMG_MPEG_Load(image_desc *desc, const char *filename);
int IMG_MPEG_Draw(void *screen, const char *filename, int x0, int y0, int screen_width, int screen_height);
int IMG_MPEG_GetInfo(const char *filename, Image_Exif *img_info);

__END_DECLS

#endif  /*end __IMG_H__*/


