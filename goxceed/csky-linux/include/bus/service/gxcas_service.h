/**
 * @file gxca.h
 * @author lixb
 * @brief CA服务定义
 * @example gxca_demo.c 本例子解决如何通过CA服务移植一个CAS
 * @defgroup ca_service CA Service
 */
 /*@{*/
#ifndef __GXCA_SERVICE_TYPE_H__
#define __GXCA_SERVICE_TYPE_H__

#include <gxbus.h>
#include <gxtype.h>
#include "gxcore.h"

__BEGIN_DECLS

/* link/unlink event 参数 */
typedef struct link_event{
	handle_t hca;
}GxMsgProperty_CaEventLink;


typedef struct event_string{
	const char* json_string;
}GxMsgProperty_CaEvent;

typedef struct descrambler_pids {
	uint32_t num;
	uint16_t pids[8];
}GxMsgProperty_CaDescramblerPids;


__END_DECLS

#endif
/*@}*/
