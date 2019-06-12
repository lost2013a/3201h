#ifndef __GX_ADVANCE_EPG_H__
#define __GX_ADVANCE_EPG_H__

#include <stdint.h>
#include <time.h>
#include "module/epg/gxepg_manage.h"

/**
 * 建立epg时，需要配置的信息
 */
typedef struct {
	uint16_t   ts_src;                         ///< epg数据来自的TS通路 TS1-0 TS2-1 TS3-2
	uint16_t   dmx_id;

	uint16_t   service_count;                  ///< 需要同时存储epg的service总数
	uint16_t   event_count;                    ///< 总共需存储的event总数

	uint16_t   event_size;                     ///< 存储一个service下的event的总空间(bytes)，包括名字和详细描述
	uint16_t   epg_day;                        ///< 需要存储几天的epg

	uint8_t    language[3];                    ///< 需要过滤epg的语言格式
	uint8_t    cur_tp_only;                    ///< 1 - 仅过滤当前频点的EPG信息   0 - 过滤所有epg数据
#define EPG_TXT_UTF8 (0x5a5a)
#define EPG_TXT_ORIGINAL (0)
	uint16_t  txt_format;
#define SERVICE_FULL_DEFAULT_OPS    (1<<0)
#define EVENT_FULL_DEFAULT_OPS      (1<<1)
#define POOLMEM_FULL_DEFAULT_OPS    (1<<2)
	int32_t    (*func)(status_t st);           ///< 注册回调函数，在数据存储满等一些情况的回调动作，如果NULL，
#define ATSC 0
#define DVB 1
	int32_t type;
} GxMsgProperty_EpgCreate;

// service count that can exsit in one time
// total event count
// event size include name & content description (bytes)
// need epg days  (exp. 7-get epg in the follow 7days)

/**
 * 存储某一个epg事件相关内容的结构
 */
typedef struct {
	time_t start_time;             ///< event的开始时间
	time_t duration;               ///< event的持续时间

	uint16_t event_id;             ///< event id值
	uint16_t reserved;             ///< 保留

	uint16_t event_name_len;
	uint16_t event_detail_len;

	uint16_t reference_event_id;
	uint16_t reference_service_id;
	uint8_t *event_name;           ///< 指向event name存储空间的指针
	uint8_t *event_detail;         ///< 指向详细描述存储空间的指针
} GxEpgEventInfo;

/**
 * epg服务所提供的，获取某个service id下epg的数据结构
 */
typedef struct {
	uint16_t ts_id;             ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;        ///< 当前epg所处的source id
	time_t begin_time;          ///< 当begin_time,end_time,want_count都为0的时候,取当前所有的event。
	                            ///< 当前后续信息，后续的为schedule信息
	                            ///< 用以告诉用户真实获取了几天 event，在用户发
	                            ///< 消息的时候是不必要填这个参数的
	time_t end_time;            ///< 当begin_time,end_time为0,want_count不为0获取所有event前面want_count个的event。
	uint16_t want_count;        ///< 当time,end_time,want_count都不为0的时候，获取时间区间want_count个的event。
	uint16_t real_count;        ///< 表示传入时间区间内有多少个epg_event_info
	GxEpgEventInfo *event_info; ///< epg_event_info存储空间
} GxMsgProperty_EpgInfo;

typedef struct {
	uint16_t ts_id;             ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;        ///< 当前epg所处的source id
	GxEpgEventInfo present;     ///< epg_event_info存储空间
	GxEpgEventInfo follow;      ///< epg_event_info存储空间
} GxMsgProperty_EpgPFInfo;

/* parental rating */
typedef struct {
	uint16_t ts_id;             ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;        ///< 当前epg所处的service id
	uint16_t parental_rating_num;
	GxBusEpgParentalRating *parental_rating;
} GxMsgProperty_EpgParentalInfo;

/**
 * epg服务所提供的，获取某个service id下nvod的数据结构
 */
typedef struct {
	uint16_t ts_id;            ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;       ///< 当前epg所处的service id
	uint16_t get_nvod_count;
	GxEpgEventInfo *nvod_info;
} GxMsgProperty_EpgNvodGet;


#endif /* __GX_EPG_H__ */

