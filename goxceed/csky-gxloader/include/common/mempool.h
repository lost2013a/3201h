#ifndef MEMPOOL_H
#define MEMPOOL_H

#include "gxcore.h"
#include "gxtype.h"
#include "common/config.h"

__BEGIN_DECLS

handle_t GxCore_MemPoolCreateFromBuffer(void *buffer, size_t buf_size, size_t block_size,uint32_t time);
handle_t GxCore_MemPoolCreate   (size_t block_size, size_t block_number,uint32_t time);
void*    GxCore_MemPoolAlloc    (handle_t _pool);
void*    GxCore_MemPoolAllocZero(handle_t _pool);
status_t GxCore_MemPoolFree     (handle_t _pool, void *buffer);
void     GxCore_MemPoolDestory  (handle_t _pool);

__END_DECLS

#endif
