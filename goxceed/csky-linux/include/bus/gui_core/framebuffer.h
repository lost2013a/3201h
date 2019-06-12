#ifndef __FRAMEBUFFER_H_
#define __FRAMEBUFFER_H_

#include "gxcore.h"
#include "gxtype.h"

__BEGIN_DECLS

struct framebuffer {
	uint32_t  phys_address;
	uint8_t  *mmap_address;
	uint32_t size;
	void *mem_mgr;
	uint32_t used_size;
	uint32_t max_used_size;
	uint32_t overflow_size;
	handle_t lock;
};

void fb_init(struct framebuffer *fb);
void *fb_malloc(struct framebuffer *fb, GxHwMallocObj *p);
void *fb_malloc_nocache(struct framebuffer *fb, GxHwMallocObj *p);
void *fb_malloc_main(struct framebuffer *fb, GxHwMallocObj *p, int flag);
void fb_free(struct framebuffer *fb, GxHwMallocObj *p);
int fb_check(struct framebuffer *fb, GxHwMallocObj *p);

static inline int is_fb_memory(struct framebuffer *fb, uint8_t *p) {
	return p >= fb->mmap_address && p < fb->mmap_address + fb->size ? 1 : 0;
}

static inline void *fb_getmmap(struct framebuffer *fb, uint32_t p)
{
	if (fb && p >= fb->phys_address && p < fb->phys_address + fb->size)
		return fb->mmap_address + (p - fb->phys_address);

	return NULL;
}

static inline uint32_t fb_getphys(struct framebuffer *fb, uint8_t *p)
{
	if (fb && p >= fb->mmap_address && p < fb->mmap_address + fb->size)
		return fb->phys_address + (p - fb->mmap_address);

	return 0;
}

__END_DECLS

#endif

