#ifndef __GX_ATSC_EPG_H__
#define __GX_ATSC_EPG_H__

#include <stdint.h>
#include <time.h>
#include "module/epg/gxepg_manage.h"

/**
 * 建立epg时，需要配置的信息,对应GXMSG_ATSC_EPG_CREATE消息
 */
typedef struct {
	uint16_t   ts_src;               ///< epg数据来自的TS通路 TS1-0 TS2-1 TS3-2
	uint16_t   dmx_id;               ///< 数据从哪个demux过来的,0,1

	uint16_t   service_count;        ///< 需要同时存储epg的service总数
	uint16_t   event_count;          ///< 总共需存储的event总数

	uint16_t   event_size;           ///< event_size是一个event的空间，全部event耗费的空间为event_size*event_count

	uint16_t   epg_day;              ///< 需要存储几天的epg

	uint8_t    language[3];          ///< 需要过滤epg的语言格式
#define EPG_TXT_UTF8 (0x5a5a)
#define EPG_TXT_ORIGINAL (0)
	uint16_t   txt_format;           ///< 过滤txt的格式是否需要转码为utf8

#define SERVICE_FULL_DEFAULT_OPS    (1<<0)
#define EVENT_FULL_DEFAULT_OPS      (1<<1)
#define POOLMEM_FULL_DEFAULT_OPS    (1<<2)
	int32_t    (*func)(status_t st); ///< 注册回调函数，在数据存储满等一些情况的回调动作，如果NULL，
	                                 ///< 就调用默认，st的类型有如下几种
	                                 ///< GX_BUS_EPG_SERVICE_FULL:service头数组满了
	                                 ///< GX_BUS_EPG_EVENT_FULL:event头数组已经满了
	                                 ///< GX_BUS_EPG_MEM_POOL_FULL:内存池满了
	                                 ///< epg内部根据返回值来确定是否用默认处理方式
	                                 ///< 返回值用OPS宏，0表示调用注册的函数
	                                 ///< 几个宏可以或上，也可以单独需要那个调用默认处理
} GxMsgProperty_AtscEpgCreate;


/**
 * 存储某一个epg事件相关内容的结构
 */
typedef struct {
	time_t start_time;         ///< event的开始时间
	time_t duration;           ///< event的持续时间

	uint16_t event_id;         ///< event id
	uint16_t reserved;         ///< 保留

	uint16_t event_name_len;   ///< 事件name的长度
	uint16_t event_detail_len; ///< 事件内容的长度

	uint8_t *event_name;       ///< 指向event name存储空间的指针
	uint8_t *event_detail;     ///< 指向详细描述存储空间的指针,长描述和短描述之间的拼接间隔符号为"@"
}GxEpgEventInfo;

/**
 * epg服务所提供的，获取某个source id下epg的数据结构和释放这个source id的内存
 * 对应GXMSG_ATSC_EPG_GET和GXMSG_ATSC_EPG_FREE消息
 */
typedef struct {
	uint16_t source_id;         ///< 当前epg所处的source id

	time_t begin_time;          ///< 当begin_time,end_time,want_count都为0的时候,取当前所有的event。
	time_t end_time;            ///< 当begin_time,end_time为0,want_count不为0获取所有event前面want_count个的event。
	uint16_t want_count;        ///< 当time,end_time,want_count都不为0的时候，获取时间区间want_count个的event。

	uint16_t real_count;        ///< 表示传入时间区间内有多少个epg_event_info
	GxEpgEventInfo *event_info; ///< epg_event_info存储空间
}GxMsgProperty_AtscEpgInfo;

#endif /* __GX_ATSC_EPG_H__*/

