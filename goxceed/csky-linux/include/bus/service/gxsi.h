/**@defgroup si_service SI Service*/
 /*@{*/

/* Define to prevent recursive inclusion */
#ifndef __GX_SI_H__
#define __GX_SI_H__

#include "module/si/si_filter.h"
#include "module/si/si_parser.h"
#include "module/si/si_public.h"
#include "module/si/si_eit.h"
#include "module/si/si_pat.h"
#include "module/si/si_sdt.h"
#include "module/si/si_pmt.h"
#include "module/si/si_nit.h"
#include "module/si/si_bat.h"
#include "module/si/si_tdt.h"
#include "module/si/si_tot.h"
#include "gxbus.h"
#include "gxcore.h"

__BEGIN_DECLS

///<si过滤eit section的门限，当过滤到的section数量超过门限时将会当作subtable ok
//默认值为1000
#define SI_CONFIG_EIT_GATE          "si>eit_gate"
#define SI_CONFIG_PER_READ_SIZE     "si>per_read_size"
#define SI_CONFIG_EVENT_DETAIL_SPLICE "si>event_detail_splice"

typedef struct {
	uint16_t    ts_src;                ///< 当前解复用的数据从哪一路TS流入
	uint16_t    demux_id;              ///< 当前解复用采用哪一个demux

	int16_t     si_subtable_id;        ///< 当前subtable的控制块id，在"GXBUS_SI_MSG_CREATE"时获得值，其他消息都作为输入值
	uint16_t    reserved;              ///< 保留

	uint32_t    request_id;            ///< 在"GXBUS_SI_MSG_CREATE"时每次加1, 供对应服务标识唯一

	GxSiFilter  si_filter;             ///< si filter 的内容，在"GXBUS_SI_MSG_GET_INFO"为输出，其他消息都作为传入值
	uint32_t    time_out;              ///< subtable 超时时间( ms)，单位毫秒
	private_table_cfg table_parse_cfg; ///< 私有表解析的配置
}GxSubTableDetail;

typedef GxSubTableDetail* GxMsgProperty_SiCreate;             ///< 与GXMSG_SI_SUBTABLE_CREATE对应的结构指针
typedef GxSubTableDetail* GxMsgProperty_SiGet;                ///< 与GXMSG_SI_SUBTABLE_GET对应的结构指针
typedef GxSubTableDetail* GxMsgProperty_SiModify;             ///< 与GXMSG_SI_SUBTABLE_MODIFY对应的结构指针

// int16_t can't use as global varibale, so change to int32_t
typedef int32_t GxMsgProperty_SiStart;                        ///< 与GXMSG_SI_SUBTABLE_START对应的结构，内容为si_subtable_id
typedef int32_t GxMsgProperty_SiStop;                         ///< 与GXMSG_SI_SUBTABLE_STOP对应的结构，内容为si_subtable_id
typedef int32_t GxMsgProperty_SiRelease;                      ///< 与GXMSG_SI_SUBTABLE_RELEASE对应的结构，内容为si_subtable_id

/**
 * provid parsed result
 */
typedef struct {
	uint16_t      table_id;       ///< table id
	int16_t       si_subtable_id; ///< subtable id, 没一个过滤的数据都会对应一路subtable
	uint32_t      request_id;     ///< 在"GXBUS_SI_MSG_CREATE"时每次加1, 供对应服务标识唯一
	uint8_t*      parsed_data;    ///< 解析完一个section后，解析后数据按照一定格式存储的空间地址
}GxParseResult;

typedef GxParseResult GxMsgProperty_SiSectionOk;  ///< 与GXMSG_SI_SECTION_OK对应的结构指针
typedef GxParseResult GxMsgProperty_SiSubtableOk; ///< 与GXMSG_SI_SUBTABLE_OK对应的结构指针
typedef GxParseResult GxMsgProperty_SiTimeout;    ///< 与GXMSG_SI_SUBTABLE_TIME_OUT对应的结构指针
typedef GxParseResult GxMsgProperty_SiReleaseOk;  ///< 与GXMSG_SI_SUBTABLE_RELEASE_OK对应的结构，内容为si_subtable_id

__END_DECLS

#endif /* __GX_SI_H__ */
/*@}*/

