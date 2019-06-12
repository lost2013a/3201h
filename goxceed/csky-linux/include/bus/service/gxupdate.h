/**
 * @file gxupdate.h
 * @author lixb
 * @brief Goxceed Update在线升级服务实现
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

/**GxUpdate服务状态类型定义*/
typedef enum {
	GXUPDATE_STATUS_PRERCENT,                /**<升级进度百分比*/
	GXUPDATE_STATUS_ERROR                    /**<升级错误*/
} GxUpdae_StatusType;

/**升级状态信息，消息GXMSG_UPDATE_STATUS携带参数*/
typedef struct {
	GxUpdae_StatusType              type;           /**<升级状态类型*/
	union {
		uint32_t                    percent;        /**<升级进度百分比*/
		int32_t                     error;          /**<升级错误号*/
	};
} GxMsgProperty_UpdateStatus;

/**升级流名，消息GXMSG_UPDATE_OPEN所携带参数类型*/
typedef GxUpdate_StreamName             GxMsgProperty_UpdateOpen;
/**升级协议名，消息GXMSG_UPDATE_PROTOCOL_SELECT所携带参数类型*/
typedef GxUpdate_ProtocolName           GxMsgProperty_UpdateProtocolSelect;
/**升级分区名，消息GXMSG_UPDATE_PARTITION_SELECT所携带参数类型*/
typedef GxUpdate_PartitionName          GxMsgProperty_UpdatePartitionSelect;
/**升级协议设置参数，消息GXMSG_UPDATE_PROTOCOL_CTRL所携带参数类型*/
typedef GxUpdate_IoCtrl                 GxMsgProperty_UpdateProtocolCtrl;
/**升级协议设置参数，消息GXMSG_UPDATE_PROTOCOL_CTRL所携带参数类型*/
typedef GxUpdate_IoCtrl                 GxMsgProperty_UpdatePartitionCtrl;

/**
 * 升级协议列表
 * 如果APP文案开发者要使用GxUpdate，必须在APP中定义这个全局指针数组，并以NULL作为
 * 最后一个结束标识
 */
extern  GxUpdate_ProtocolOps**         gxupdate_protocol_list;
/**
 * 分区列表
 * 如果APP文案开发者要使用GxUpdate，必须在APP中定义这个全局指针数组，并以NULL作为
 * 最后一个结束标识
 */
extern  GxUpdate_PartitionOps**        gxupdate_partition_list;

__END_DECLS

#endif
/*@}*/
