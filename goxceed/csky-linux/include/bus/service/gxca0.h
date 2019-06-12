/**
 * @file gxca.h
 * @author lixb
 * @brief CA服务定义
 * @example gxca_demo.c 本例子解决如何通过CA服务移植一个CAS
 * @defgroup ca_service CA Service
 */
 /*@{*/
#ifndef __GXCA_TYPE_H__
#define __GXCA_TYPE_H__

#include <gxbus.h>
#include <gxtype.h>
#include <stdbool.h>
#include "module/ca0/gxca_def.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef GxCA_System             GxMsgProperty_RegisterCas;
/**CA服务消息GXMSG_CA_UNREGISTER_CAS所携带参数结构体*/
typedef char                    GxMsgProperty_UnregisterCas[GXCA_NAME_SIZE];

typedef struct {
	char    name[GXCA_NAME_SIZE];
	int     key;
	void*   buf;
	size_t  size;
} GxMsgProperty_OnIoctrl;

typedef struct {
	char*   name;
	int     key;
	void*   buf;
	size_t  size;
} GxMsgProperty_OnEvent;

__END_DECLS

#endif
/*@}*/
