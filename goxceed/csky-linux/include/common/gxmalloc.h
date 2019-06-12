#ifndef GXMALLOC_H
#define GXMALLOC_H

#include <unistd.h>

__BEGIN_DECLS
/* Malloc API */

/*以下几个参数可以用|的方式使用 */
typedef enum
{
	MEMORY_SHOW_ERR_P = 1,
	MEMORY_SHOW_ALL_MALLOC = 2,
	MEMORY_SHOW_NO_FREE = 4,
}MemoryDebugShow;

#ifdef MEMORY_DEBUG

void *GxCore_MallocDebug(const char *file, int line, size_t size);
void *GxCore_MalloczDebug(const char *file, int line, size_t size);
void *GxCore_CallocDebug(const char *file, int line, size_t nmemb, size_t size);
void *GxCore_ReallocDebug(const char *file, int line, void *mem, size_t size);
void GxCore_FreeDebug(const char *file, int line, void *ptr);
char *GxCore_StrdupDebug(const char *file, int line, const char* sting);
void GxCore_MemoryShowDebug(MemoryDebugShow show);
int GxCore_MemoryTryDebug(const char *file, int line, void *p);

#define GxCore_Malloc(size)              GxCore_MallocDebug(__FILE__, __LINE__, size)
#define GxCore_Mallocz(size)             GxCore_MalloczDebug(__FILE__, __LINE__, size)
#define GxCore_Calloc(nmemb, size)       GxCore_CallocDebug(__FILE__, __LINE__, nmemb, size)
#define GxCore_Realloc(mem, size)        GxCore_ReallocDebug(__FILE__, __LINE__, mem, size)
#define GxCore_Free(ptr)                 GxCore_FreeDebug(__FILE__, __LINE__, ptr)
#define GxCore_MemoryTry(ptr)            GxCore_MemoryTryDebug(__FILE__, __LINE__, ptr)
#define GxCore_Strdup(ptr)               GxCore_StrdupDebug(__FILE__, __LINE__, ptr)
#define GxCore_MemoryShow(stat)          GxCore_MemoryShowDebug(stat)

#else

void *GxCore_MallocRelease(size_t size);
void *GxCore_MalloczRelease(size_t size);
void *GxCore_CallocRelease(size_t nmemb, size_t size);
void *GxCore_ReallocRelease(void *mem, size_t size);
void GxCore_FreeRelease(void *ptr);

#define GxCore_Malloc(size)              GxCore_MallocRelease(size)
#define GxCore_Mallocz(size)             GxCore_MalloczRelease(size)
#define GxCore_Calloc(nmemb, size)       GxCore_CallocRelease(nmemb, size)
#define GxCore_Realloc(mem, size)        GxCore_ReallocRelease(mem, size)
#define GxCore_Free(ptr)                 GxCore_FreeRelease(ptr)
#define GxCore_Strdup(ptr)               strdup(ptr)
#define GxCore_MemoryCheck()
#define GxCore_MemoryShow(stat)
#define GxCore_MemoryTry(ptr)

#endif


__END_DECLS
#endif

