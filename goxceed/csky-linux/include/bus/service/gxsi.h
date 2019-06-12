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

///<si����eit section�����ޣ������˵���section������������ʱ���ᵱ��subtable ok
//Ĭ��ֵΪ1000
#define SI_CONFIG_EIT_GATE          "si>eit_gate"
#define SI_CONFIG_PER_READ_SIZE     "si>per_read_size"
#define SI_CONFIG_EVENT_DETAIL_SPLICE "si>event_detail_splice"

typedef struct {
	uint16_t    ts_src;                ///< ��ǰ�⸴�õ����ݴ���һ·TS����
	uint16_t    demux_id;              ///< ��ǰ�⸴�ò�����һ��demux

	int16_t     si_subtable_id;        ///< ��ǰsubtable�Ŀ��ƿ�id����"GXBUS_SI_MSG_CREATE"ʱ���ֵ��������Ϣ����Ϊ����ֵ
	uint16_t    reserved;              ///< ����

	uint32_t    request_id;            ///< ��"GXBUS_SI_MSG_CREATE"ʱÿ�μ�1, ����Ӧ�����ʶΨһ

	GxSiFilter  si_filter;             ///< si filter �����ݣ���"GXBUS_SI_MSG_GET_INFO"Ϊ�����������Ϣ����Ϊ����ֵ
	uint32_t    time_out;              ///< subtable ��ʱʱ��( ms)����λ����
	private_table_cfg table_parse_cfg; ///< ˽�б����������
}GxSubTableDetail;

typedef GxSubTableDetail* GxMsgProperty_SiCreate;             ///< ��GXMSG_SI_SUBTABLE_CREATE��Ӧ�Ľṹָ��
typedef GxSubTableDetail* GxMsgProperty_SiGet;                ///< ��GXMSG_SI_SUBTABLE_GET��Ӧ�Ľṹָ��
typedef GxSubTableDetail* GxMsgProperty_SiModify;             ///< ��GXMSG_SI_SUBTABLE_MODIFY��Ӧ�Ľṹָ��

// int16_t can't use as global varibale, so change to int32_t
typedef int32_t GxMsgProperty_SiStart;                        ///< ��GXMSG_SI_SUBTABLE_START��Ӧ�Ľṹ������Ϊsi_subtable_id
typedef int32_t GxMsgProperty_SiStop;                         ///< ��GXMSG_SI_SUBTABLE_STOP��Ӧ�Ľṹ������Ϊsi_subtable_id
typedef int32_t GxMsgProperty_SiRelease;                      ///< ��GXMSG_SI_SUBTABLE_RELEASE��Ӧ�Ľṹ������Ϊsi_subtable_id

/**
 * provid parsed result
 */
typedef struct {
	uint16_t      table_id;       ///< table id
	int16_t       si_subtable_id; ///< subtable id, ûһ�����˵����ݶ����Ӧһ·subtable
	uint32_t      request_id;     ///< ��"GXBUS_SI_MSG_CREATE"ʱÿ�μ�1, ����Ӧ�����ʶΨһ
	uint8_t*      parsed_data;    ///< ������һ��section�󣬽��������ݰ���һ����ʽ�洢�Ŀռ��ַ
}GxParseResult;

typedef GxParseResult GxMsgProperty_SiSectionOk;  ///< ��GXMSG_SI_SECTION_OK��Ӧ�Ľṹָ��
typedef GxParseResult GxMsgProperty_SiSubtableOk; ///< ��GXMSG_SI_SUBTABLE_OK��Ӧ�Ľṹָ��
typedef GxParseResult GxMsgProperty_SiTimeout;    ///< ��GXMSG_SI_SUBTABLE_TIME_OUT��Ӧ�Ľṹָ��
typedef GxParseResult GxMsgProperty_SiReleaseOk;  ///< ��GXMSG_SI_SUBTABLE_RELEASE_OK��Ӧ�Ľṹ������Ϊsi_subtable_id

__END_DECLS

#endif /* __GX_SI_H__ */
/*@}*/

