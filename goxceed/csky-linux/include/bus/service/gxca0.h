/**
 * @file gxca.h
 * @author lixb
 * @brief CA������
 * @example gxca_demo.c �����ӽ�����ͨ��CA������ֲһ��CAS
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
/**CA������ϢGXMSG_CA_UNREGISTER_CAS��Я�������ṹ��*/
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
