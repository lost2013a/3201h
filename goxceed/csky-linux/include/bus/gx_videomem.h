#ifndef __GX_VIDEO_MEMORY_H__
#define __GX_VIDEO_MEMORY_H__

unsigned char *Gx_VideoMemoryMalloc(unsigned long size, unsigned int align_shift);
unsigned char* Gx_VideoMemoryMapToKernel(unsigned char *p);
unsigned char* Gx_VideoMemoryMapToUser(unsigned char *p);
void Gx_VideoMemoryFree(unsigned char *p);

#endif
