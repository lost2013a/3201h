#ifndef __GXCORE_H__
#define __GXCORE_H__

#include "common/gxcore_common.h"
#include "gxos/gxcore_os.h"
#include "av/avapi.h"

#if 1
#define CHECK_STACK_ADDRESS {                   \
	int x;      \
                    \
	x=GxCore_ThreadGetId();  \
	GxCore_ThreadRecord* thread_rec1 = THREAD_GET(gxcore_id_to_handle(x)); \
	printf("thread stack use %5.2f%%\n", (unsigned int)(&x)/(thread_rec1->stack_info->memory + thread_rec1->stack_info->size)); \
}
#endif

#define ENABLE_TIME 1

#if ENABLE_TIME
#define RUNTIME(prompt, code) do {                \
	static GxTime start, stop;    \
	uint32_t ms1, ms2;                        \
                                                  \
	GxCore_GetTickTime(&start);               \
	code;                                     \
	GxCore_GetTickTime(&stop);                \
	ms1 = stop.seconds * 1000 + stop.microsecs / 1000 - (start.seconds * 1000 + start.microsecs / 1000); \
	ms2 = stop.seconds * 1000 + stop.microsecs / 1000; \
	printf("\033[031m%s:\033[036m %u \033[0mms, total\033[036m %u \033[0mms\n", prompt, ms1, ms2); \
} while(0)

#define SHOWTIME(prompt) do { \
	uint32_t ms;                                                \
	GxTime now_tick;                                            \
	GxCore_GetTickTime(&now_tick);                              \
	ms = now_tick.seconds * 1000 + now_tick.microsecs / 1000;   \
	printf("\033[031m%s:\033[036m %u \033[0mms\n", prompt, ms); \
}while(0)

#else

#define RUNTIME(prompt, code) do {   \
	code;                        \
} while(0)

#define SHOWTIME(prompt) do { \
}while(0)

#endif

#define GET_VERSON GOXCEED_VERSON

#endif
