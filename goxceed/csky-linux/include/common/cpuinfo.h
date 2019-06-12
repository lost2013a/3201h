#ifndef _GX_CORE_CPUINFO_H_
#define _GX_CORE_CPUINFO_H_

typedef struct ag_cpuinfo {
	const char *arch;                  /* Architecture name */
	char       vendorID[13];           /* CPU Vendor ID string */
	uint32_t   ext;			   /* Architecture extensions
					      (relevant to user-mode) */
#define GX_EXT_CPUID		0x00000001 /* CPUID Instruction */
#define GX_EXT_MMX		0x00000002 /* MMX Technology */
#define GX_EXT_MMX_EXT		0x00000004 /* MMX with AMD Extensions */
#define GX_EXT_3DNOW		0x00000008 /* 3dNow! */
#define GX_EXT_3DNOW_EXT	0x00000010 /* 3dNow! + Extensions */
#define GX_EXT_ALTIVEC		0x00000020 /* AltiVec Extensions */
#define GX_EXT_SSE		0x00000040 /* Streaming SIMD Extensions */
#define GX_EXT_SSE2		0x00000080 /* SSE2 Extensions */
#define GX_EXT_SSE3		0x00000100 /* SSE3 Extensions (PNI) */
#define GX_EXT_LONG_MODE	0x00000200 /* Long Mode */
#define GX_EXT_RDTSCP		0x00000400 /* RDTSCP instruction */
#define GX_EXT_FXSR		0x00000800 /* Fast FXSAVE/FXSTOR */
#define GX_EXT_PAGE_NX		0x00001000 /* W^X Page Protection */
#define GX_EXT_SSE5A		0x00002000 /* SSE5A Extensions */
#define GX_EXT_3DNOW_PREFETCH	0x00004000 /* PREFETCH/PREFETCHW for 3DNow! */
#define GX_EXT_SSE_MISALIGNED	0x00008000 /* Misaligned SSE mode */
#define GX_EXT_SSE4A		0x00010000 /* SSE4A Extensions */
#define GX_EXT_ONCHIP_FPU	0x00020000 /* On-chip FPU */
#define GX_EXT_TSC		0x00040000 /* Time Stamp Counter */
#define GX_EXT_CMOV		0x00080000 /* Conditional Move instruction */
#define GX_EXT_CLFLUSH		0x00100000 /* Cache-Line Flush instruction */
#define GX_EXT_HTT		0x00200000 /* Hyper-Threading technology */
#define GX_EXT_MON		0x00400000 /* MONITOR/MWAIT instructions */
#define GX_EXT_VMX		0x00800000 /* Virtual Machine extensions */
#define GX_EXT_SSSE3		0x01000000 /* SSSE3 Extensions */
#define GX_EXT_SSE41		0x02000000 /* SSE4.1 extensions */
#define GX_EXT_SSE42		0x04000000 /* SSE4.1 extensions */
} GxCPUInfo;

__BEGIN_DECLS
extern GxCPUInfo GxCPU;

void GxGetCPUInfo(GxCPUInfo *);
__END_DECLS

#if defined(_USE_GXCORE_CPUINFO)
#define HasMMX()	(GxCPU.ext & GX_EXT_MMX)
#define HasMMXEXT()	(GxCPU.ext & GX_EXT_MMX_EXT)
#define Has3DNOW()	(GxCPU.ext & GX_EXT_3DNOW)
#define Has3DNOWEXT()	(GxCPU.ext & GX_EXT_3DNOW_EXT)
#define HasAltiVec()	(GxCPU.ext & GX_EXT_ALTIVEC)
#define HasSSE()	(GxCPU.ext & GX_EXT_SSE)
#define HasSSE2()	(GxCPU.ext & GX_EXT_SSE2)
#define HasSSE3()	(GxCPU.ext & GX_EXT_SSE3)
#define HasSSSE3()	(GxCPU.ext & GX_EXT_SSSE3)
#endif

#endif	/* _USE_GXCORE_CPUINFO */
