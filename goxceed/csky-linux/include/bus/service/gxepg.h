#ifndef __GX_EPG_H__
#define __GX_EPG_H__

#include <stdint.h>
#include <time.h>
#include "module/epg/gxepg_manage.h"

#define EPG_TXT_UTF8 (0x5a5a)
#define EPG_TXT_ORIGINAL (0)
#define EPG_TXT_PRIVATE (1)

///<是否保持全速过滤，默认为default
//
//范例：
//
//GxBus_ConfigSetInt(EPG_SERVICE_FILTER_MODE,EPG_MANAGER_FILTER_MODE_MAX);


#define EPG_SERVICE_FILTER_MODE	"epg_service>filter_mode"
#define EPG_SERVICE_FILTER_MODE_DEFAULT (0)//会根据eit表接收情况，以默认规则做过滤条件转换
#define EPG_SERVICE_FILTER_MODE_MAX (1)//任何时候都不转换匹配条件,过滤速度最快。但是如果流里epg很多，会有一定系统负担


/*当txt_format为EPG_TXT_PRIVATE ， ttx_privat起作用，返回的指针是用了malloc的，当epg服务
 * 用完后会释放。*/
typedef uint8_t * (*gx_epg_ttx_private)(uint8_t *src, uint32_t len);
/**
 * 建立epg时，需要配置的信息
 */
typedef struct {
	uint16_t  ts_src;               ///< epg数据来自的TS通路 TS1-0 TS2-1 TS3-2
	uint16_t  dmx_id;

	uint16_t  service_count;        ///< 需要同时存储epg的service总数
	uint16_t  event_count;          ///< 总共需存储的event总数

	uint16_t  event_size;           ///< 存储一个service下的event的总空间(bytes)，包括名字和详细描述
	uint16_t  epg_day;              ///< 需要存储几天的epg

	uint8_t   language[3];          ///< 需要过滤epg的语言格式
	uint8_t   cur_tp_only;          ///< 1 - 仅过滤当前频点的EPG信息   0 - 过滤所有epg数据
	uint16_t  txt_format;
	gx_epg_ttx_private  ttx_private;
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
} GxEpgInfo;

/**
 * epg服务所提供的，获取某个service id下epg的数据结构
 */
typedef struct {
	uint16_t ts_id;            ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;       ///< 当前epg所处的service id
	uint16_t get_event_pos;    ///< 从第几条event开始获取event信息，前两个为
	//当前后续信息，后续的为schedule信息
	uint16_t get_event_count;  ///< 从get_event_pos开始，epg_info空间所能容纳的event总数,这个参数是由epg服务返回时填充的
	                           ///< 用以告诉用户真实获取了几天 event，在用户发
	//消息的时候是不必要填这个参数的
	uint16_t want_event_count; ///< 想要一次获取的event总数
	uint32_t epg_info_size;    ///< 用来存储epg的总空间大小
	GxEpgInfo *epg_info;       ///< 这是一个由上层分配的空间
} GxMsgProperty_EpgGet;

/**
 * 获取某个service下的epg数量
 */
typedef struct {
	uint16_t ts_id;                          ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;                     ///< 当前epg所处的service id
	uint16_t real_event_count;               ///< 实际存在的event总数
	float time_zone;                         ///< 时区-12 ~ 0 ~ 12, 支持半时区。Exp.+8.5
	uint16_t event_per_day[8];               ///< 从今天开始的7天内，每天所含event的数目，
	//0-PF信息 1 - 今天的event 数目 2-明天的event数目...
} GxMsgProperty_EpgNumGet;

/* parental rating */
typedef struct {
	uint16_t ts_id;                          ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;                     ///< 当前epg所处的service id
	uint16_t parental_rating_num;
	GxBusEpgParentalRating *parental_rating;
} GxMsgProperty_EpgParentalInfo;

typedef GxEpgInfo GxNvodInfo;

/**
 * epg服务所提供的，获取某个service id下nvod的数据结构
 */
typedef struct {
	uint16_t ts_id;           ///< transport stream id
	uint16_t service_id;      ///< 当前epg所处的service id

	uint16_t orig_network_id;
	uint16_t get_nvod_count;

	uint32_t nvod_info_size;  ///< 用来存储nvod的总空间大小

	GxNvodInfo *nvod_info;    ///< 这是一个由上层分配的空间
} GxMsgProperty_EpgNvodGet;

typedef enum {
	STOP_FILTER = 0,
	START_FILTER ,
	MATCH_SERV_ID_FILTER,
	MATCH_FULL_FILTER,
	UNMATCH_FILTER
} filterStatus;

typedef struct {
	uint32_t tid;
	filterStatus status;
} GxEpgFilterInfo;

/**
 * epg服务所提供的，获取epg当前filter的状态
 */
typedef struct {
	uint32_t num;                   ///< 想要获取的filter数量
	uint16_t real_num;              ///< 实际获取的filter数量

	GxEpgFilterInfo *filter_status; ///< 这是一个由上层分配的空间
} GxMsgProperty_EpgFilterInfo;

typedef struct {
	uint32_t tid;
	uint32_t service_id;
	uint32_t version;

	filterStatus status;
} GxEpgFilterModify;

/**
 * epg服务所提供的，修改epg当前filter的状态
 */
typedef struct {
	uint32_t num;              ///< 想要修改的filter数量
	GxEpgFilterModify *status; ///< 这是一个由上层分配的空间
} GxMsgProperty_EpgFilterModify;

#endif

