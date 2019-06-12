#ifndef __GUI_POOL_H__
#define __GUI_POOL_H__

#include "gx_mempool.h"

#define GUIPOOL_SIZE 1 * 1024 * 1024
#define MEMPOOL_NUM  6
typedef struct _GuiPool {
	int         init;
	int         size[MEMPOOL_NUM];
	int         count[MEMPOOL_NUM];
	gx_mempool* data_pool[MEMPOOL_NUM];
} GuiPool;

void GuiPool_Info(GuiPool*pool);
void GuiPool_Init(size_t size);
void GuiPool_Destroy(GuiPool* pool);
void *GuiPool_Alloc(GuiPool *pool, size_t size);
void *GuiPool_Allocz(GuiPool *pool, size_t size);
void *GuiPool_Realloc(GuiPool *pool, void *ptr, size_t size);
char *GuiPool_Strdup(GuiPool *pool, const char *s);
void GuiPool_Free(GuiPool *pool, void *ptr);

#endif

