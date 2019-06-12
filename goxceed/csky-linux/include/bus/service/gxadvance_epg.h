#ifndef __GX_ADVANCE_EPG_H__
#define __GX_ADVANCE_EPG_H__

#include <stdint.h>
#include <time.h>
#include "module/epg/gxepg_manage.h"

/**
 * ����epgʱ����Ҫ���õ���Ϣ
 */
typedef struct {
	uint16_t   ts_src;                         ///< epg�������Ե�TSͨ· TS1-0 TS2-1 TS3-2
	uint16_t   dmx_id;

	uint16_t   service_count;                  ///< ��Ҫͬʱ�洢epg��service����
	uint16_t   event_count;                    ///< �ܹ���洢��event����

	uint16_t   event_size;                     ///< �洢һ��service�µ�event���ܿռ�(bytes)���������ֺ���ϸ����
	uint16_t   epg_day;                        ///< ��Ҫ�洢�����epg

	uint8_t    language[3];                    ///< ��Ҫ����epg�����Ը�ʽ
	uint8_t    cur_tp_only;                    ///< 1 - �����˵�ǰƵ���EPG��Ϣ   0 - ��������epg����
#define EPG_TXT_UTF8 (0x5a5a)
#define EPG_TXT_ORIGINAL (0)
	uint16_t  txt_format;
#define SERVICE_FULL_DEFAULT_OPS    (1<<0)
#define EVENT_FULL_DEFAULT_OPS      (1<<1)
#define POOLMEM_FULL_DEFAULT_OPS    (1<<2)
	int32_t    (*func)(status_t st);           ///< ע��ص������������ݴ洢����һЩ����Ļص����������NULL��
#define ATSC 0
#define DVB 1
	int32_t type;
} GxMsgProperty_EpgCreate;

// service count that can exsit in one time
// total event count
// event size include name & content description (bytes)
// need epg days  (exp. 7-get epg in the follow 7days)

/**
 * �洢ĳһ��epg�¼�������ݵĽṹ
 */
typedef struct {
	time_t start_time;             ///< event�Ŀ�ʼʱ��
	time_t duration;               ///< event�ĳ���ʱ��

	uint16_t event_id;             ///< event idֵ
	uint16_t reserved;             ///< ����

	uint16_t event_name_len;
	uint16_t event_detail_len;

	uint16_t reference_event_id;
	uint16_t reference_service_id;
	uint8_t *event_name;           ///< ָ��event name�洢�ռ��ָ��
	uint8_t *event_detail;         ///< ָ����ϸ�����洢�ռ��ָ��
} GxEpgEventInfo;

/**
 * epg�������ṩ�ģ���ȡĳ��service id��epg�����ݽṹ
 */
typedef struct {
	uint16_t ts_id;             ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;        ///< ��ǰepg������source id
	time_t begin_time;          ///< ��begin_time,end_time,want_count��Ϊ0��ʱ��,ȡ��ǰ���е�event��
	                            ///< ��ǰ������Ϣ��������Ϊschedule��Ϣ
	                            ///< ���Ը����û���ʵ��ȡ�˼��� event�����û���
	                            ///< ��Ϣ��ʱ���ǲ���Ҫ�����������
	time_t end_time;            ///< ��begin_time,end_timeΪ0,want_count��Ϊ0��ȡ����eventǰ��want_count����event��
	uint16_t want_count;        ///< ��time,end_time,want_count����Ϊ0��ʱ�򣬻�ȡʱ������want_count����event��
	uint16_t real_count;        ///< ��ʾ����ʱ���������ж��ٸ�epg_event_info
	GxEpgEventInfo *event_info; ///< epg_event_info�洢�ռ�
} GxMsgProperty_EpgInfo;

typedef struct {
	uint16_t ts_id;             ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;        ///< ��ǰepg������source id
	GxEpgEventInfo present;     ///< epg_event_info�洢�ռ�
	GxEpgEventInfo follow;      ///< epg_event_info�洢�ռ�
} GxMsgProperty_EpgPFInfo;

/* parental rating */
typedef struct {
	uint16_t ts_id;             ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;        ///< ��ǰepg������service id
	uint16_t parental_rating_num;
	GxBusEpgParentalRating *parental_rating;
} GxMsgProperty_EpgParentalInfo;

/**
 * epg�������ṩ�ģ���ȡĳ��service id��nvod�����ݽṹ
 */
typedef struct {
	uint16_t ts_id;            ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;       ///< ��ǰepg������service id
	uint16_t get_nvod_count;
	GxEpgEventInfo *nvod_info;
} GxMsgProperty_EpgNvodGet;


#endif /* __GX_EPG_H__ */

