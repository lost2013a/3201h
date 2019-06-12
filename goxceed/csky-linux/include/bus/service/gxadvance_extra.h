#ifndef __GXADVANCE_EXTRA_H__
#define __GXADVANCE_EXTRA_H__

#include <time.h>
#include "gxbus.h"
#include "sub_system/si_sub_engine/si_sub_engine.h"

#if 1
typedef enum {
	TDT_TIME,
	TOT_TIME,
	STT_TIME,
}FOUNTAIN;
#endif

typedef struct
{
	int         time_zone;//当没有获取到时区信息时，置为0xfffffff（7个F）,用户需要手动设置时区
	time_t      utc_second;
	FOUNTAIN    time_fountain;
}GxMsgProperty_ExtraTimeOk;

typedef struct
{
	uint32_t ts_src;    // 通过哪一路TS去过滤tdt或者tot，TS1-0  TS2-1  TS3-2 ...
	GxSubsystemSiProtocol dmx_protocol;//在兼容dvb和atsc时，需要用户指定那个dmx硬件赖过率，指定协议来区分过滤什么表
}GxMsgProperty_ExtraSyncTime;

#endif /*  __GX_EXTRA_H__ */
