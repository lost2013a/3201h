/**
 * @file gxupdate.h
 * @author lixb
 * @brief Goxceed Update������������ʵ��
 * @defgroup update_service Update Servce
 */
/*@{*/
#ifndef __GXUPDATE_SERVICE_H__
#define __GXUPDATE_SERVICE_H__

#include "gxtype.h"
#include "gxbus.h"
#include "module/update/gxupdate_def.h"
#include "gxcore.h"

__BEGIN_DECLS

/**GxUpdate����״̬���Ͷ���*/
typedef enum {
	GXUPDATE_STATUS_PRERCENT,                /**<�������Ȱٷֱ�*/
	GXUPDATE_STATUS_ERROR                    /**<��������*/
} GxUpdae_StatusType;

/**����״̬��Ϣ����ϢGXMSG_UPDATE_STATUSЯ������*/
typedef struct {
	GxUpdae_StatusType              type;           /**<����״̬����*/
	union {
		uint32_t                    percent;        /**<�������Ȱٷֱ�*/
		int32_t                     error;          /**<���������*/
	};
} GxMsgProperty_UpdateStatus;

/**������������ϢGXMSG_UPDATE_OPEN��Я����������*/
typedef GxUpdate_StreamName             GxMsgProperty_UpdateOpen;
/**����Э��������ϢGXMSG_UPDATE_PROTOCOL_SELECT��Я����������*/
typedef GxUpdate_ProtocolName           GxMsgProperty_UpdateProtocolSelect;
/**��������������ϢGXMSG_UPDATE_PARTITION_SELECT��Я����������*/
typedef GxUpdate_PartitionName          GxMsgProperty_UpdatePartitionSelect;
/**����Э�����ò�������ϢGXMSG_UPDATE_PROTOCOL_CTRL��Я����������*/
typedef GxUpdate_IoCtrl                 GxMsgProperty_UpdateProtocolCtrl;
/**����Э�����ò�������ϢGXMSG_UPDATE_PROTOCOL_CTRL��Я����������*/
typedef GxUpdate_IoCtrl                 GxMsgProperty_UpdatePartitionCtrl;

/**
 * ����Э���б�
 * ���APP�İ�������Ҫʹ��GxUpdate��������APP�ж������ȫ��ָ�����飬����NULL��Ϊ
 * ���һ��������ʶ
 */
extern  GxUpdate_ProtocolOps**         gxupdate_protocol_list;
/**
 * �����б�
 * ���APP�İ�������Ҫʹ��GxUpdate��������APP�ж������ȫ��ָ�����飬����NULL��Ϊ
 * ���һ��������ʶ
 */
extern  GxUpdate_PartitionOps**        gxupdate_partition_list;

__END_DECLS

#endif
/*@}*/
