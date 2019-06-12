#ifndef SDC_CACHE_H
#define SDC_CACHE_H

#include "kernelcalls.h"

#define CACHE_PTS_SIZE        (2048)
#define CACHE_PAGE_SIZE       (4096)
#define CAHCE_PAGE_MAX_USED   (600)
#define CAHCE_PAGE_MAX_CACHED (200)

struct gxav_page {
	gxlist_head     head;
	unsigned char   buffer[CACHE_PAGE_SIZE];
	unsigned int    size;
};

struct gxav_cache {
	gxlist_head        page_list;
	unsigned int       page_pos_w;
	struct gxav_page*  cur_page_w;

	unsigned int       page_pos_r;
	struct gxav_page*  cur_page_r;

	unsigned int       size;
};

struct gxav_pts {
	unsigned int   addr;
	unsigned int   pts;
	unsigned int   pos;
};

struct gxav_cache_pts {
	unsigned int       in;
	unsigned int       out;
	struct gxav_pts    pts[CACHE_PTS_SIZE];
};

int  cache_init     (struct gxav_cache *cache);
void cache_uninit   (struct gxav_cache *cache);
int  cache_put      (struct gxav_cache *cache, unsigned char *data, unsigned int len, void *(*copy)(void *dest, const void *src, int n));
int  cache_get      (struct gxav_cache *cache, unsigned char *data, unsigned int len, void *(*copy)(void *dest, const void *src, int n));
int  cache_peek     (struct gxav_cache *cache, unsigned char *data, unsigned int len, void *(*copy)(void *dest, const void *src, int n));
int  cache_size     (struct gxav_cache *cache);
void cache_release  (void);
int  cache_pts_get  (struct gxav_cache_pts *cache, unsigned int *addr, int *pts, unsigned int pos);
int  cache_pts_put  (struct gxav_cache_pts *cache, unsigned int addr, int pts, unsigned int pos);
int  cache_pts_reset(struct gxav_cache_pts *cache);

#endif
