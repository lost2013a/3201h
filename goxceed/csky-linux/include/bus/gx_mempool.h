#ifndef __GX_MEMPOOL_H__
#define __GX_MEMPOOL_H__

#include <stdint.h>
#include <gxcore.h>

typedef struct _mempool {
	size_t            block_size;
	size_t            block_number;
	char *            buffer;
	char *            buffer_end;
	int               max_need_count;
	int               alloc_count;
	int               free_count;
	struct node       *chunk;
	handle_t          mutex;
} gx_mempool;

gx_mempool *gx_mempool_create(size_t block_size, size_t block_number, char* buffer);
void *gx_mempool_alloc(gx_mempool* pool, size_t size);
void gx_mempool_free(gx_mempool* pool, void *buffer, size_t size);
void gx_mempool_destory(gx_mempool* pool);

#endif

