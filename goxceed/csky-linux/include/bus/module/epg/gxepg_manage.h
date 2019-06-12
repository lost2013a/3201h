/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __GXEPG_MANAGE_H__
#define __GXEPG_MANAGE_H__

#include <time.h>
#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

/*错误值*/
#define GX_BUS_EPG_OK GXCORE_SUCCESS
#define GX_BUS_EPG_ERR GXCORE_ERROR
#define GX_BUS_EPG_EVENT_EXIST       (0x7ffffff9)
#define GX_BUS_EPG_SERVICE_FULL      (0x7ffffffa)
#define GX_BUS_EPG_MEM_POOL_FULL     (0x7ffffffb)
#define GX_BUS_EPG_EVENT_FULL        (0x7ffffffc)
#define GX_BUS_EPG_PARAMETER_ERR     (0x7ffffffd)
#define GX_BUS_EPG_NOT_LOCK          (0x7ffffffe)
#define GX_BUS_EPG_MEM_ERR           (0x7fffffff)


#define GX_BUS_MEM_POOL_CELL_SIZE (52)///<内存池每个单元的大小
#define GX_BUS_EPG_INVALID_POS (0x7ffffff8)///<代表数组的无效下标

#define EPG_MALLOC

///<版本号发生变化时如何做？默认为不采取任何行为
//
//范例：
//int32_t act = EPG_MANAGER_VER_ACT_DEL_EVENT;
//GxBus_ConfigSetInt(EPG_MANAGER_VER_ACT,&act);


#define EPG_MANAGER_VER_ACT	"epg_manager>ver_act"

#define EPG_MANAGER_VER_ACT_DEFAULT (0)
#define EPG_MANAGER_VER_ACT_DEL_EVENT (1)


/* Exported Types --------------------------------------------------------- */

/*内存池单元空间的结构体*/
#ifdef EPG_MALLOC
typedef struct {
	int8_t* content;
	uint32_t  size;
} GxBusEpgMemPoolCell;
#else
typedef struct {
	uint8_t content[GX_BUS_MEM_POOL_CELL_SIZE-4]; ///< 前48字节存内容
	void* next_Cell;                              ///< 后四个字节是下一个单元的指针
} GxBusEpgMemPoolCell;
#endif

/*时间信息*/
typedef struct {
	time_t  start_time; ///< 使用秒来表示
	time_t  duration;   ///< 持续时间,也用秒来表示
} GxBusEpgEventTime;

/* 当前后续信息 */
typedef struct {
	GxBusEpgMemPoolCell* name;                ///< event名字的起始指针
	GxBusEpgMemPoolCell* detaile_description; ///< event详细描述的起始指针
	GxBusEpgEventTime time;                   ///< 该event的开始时间和持续时间
} GxBusEpgEventPFHead;

/* first event结构，从古乐pos外还得加上语言的iso639码 */
typedef struct {
	int8_t language[4];
	uint32_t pos;        ///< 该语言下的第一个event的下标
	void* next;
} GxBusEpgFirstEvent;

/* 父母锁信息得结构 */
typedef struct {
	int8_t country[4];
	uint32_t rating;
} GxBusEpgParentalRating;

/* channel ett结构 */
typedef struct {
	int8_t language[4];
	int8_t* info;
} GxBusEpgChannelEtt;

/*epg 的service的头结构,相当于每个service epg信息的起始位置*/
typedef struct {
	uint32_t use_flag;                       ///< 该头部是否被使用 1--被使用 0--空闲
	uint32_t ts_id;                          ///< 和service_id一起用以确定一个service
	uint32_t service_id;                     ///< 和ts_id一起用以确定一个service
	uint32_t reference_service_id;           ///< 和ts_id一起用以确定一个service
	uint32_t original_id;                    ///< 用来确定一个service
	GxBusEpgFirstEvent* first_event;         ///< 该service的第一个event的下标
	//uint32_t last_event;                   ///< 该service的最后一个event下标,用于按时间插入event时的搜索,暂时没有用
	GxBusEpgEventPFHead present;             ///< 当前信息
	GxBusEpgEventPFHead follow;              ///< 后续信息
	GxBusEpgParentalRating* parental_rating; ///< 存储父母锁信息
	uint32_t parental_rating_num;            ///< 父母锁信息的数量
	GxBusEpgChannelEtt* channel_ett;         ///< 存储channel ett信息
	uint32_t channel_ett_num;                ///< channel ett的数量
	uint16_t detaile_description_ver;        ///< 详细描述的版本号
} GxBusEpgServiceHead;

typedef struct {
	uint32_t event_id;                        ///< service id ts id和event id唯一的确定一个event
	uint32_t reference_event_id;              ///< service id ts id和event id唯一的确定一个event
	GxBusEpgMemPoolCell* name;                ///< event名字的起始指针
	GxBusEpgMemPoolCell* detaile_description; ///< event详细描述的起始指针
	GxBusEpgEventTime time;                   ///< 该event的开始时间和持续时间
	uint32_t next_event;                      ///< 下一个event的下标
} GxBusEpgEventHead;



/* event 类型*/
typedef enum {
	GX_EVENT_PRESENT = 0, ///< present信息
	GX_EVENT_FOLLOW ,     ///< follow信息
	GX_EVENT_DETAILE,     ///< detaile信息
} GxBusEpgEventType;


/*已经添加到service头数组中的service*/
typedef struct {
	uint32_t ts_id;       ///< 和service_id一起用以确定一个service
	uint32_t service_id;  ///< 和ts_id一起用以确定一个service
	uint32_t original_id; ///< 用来确定一个service
	uint32_t pos;         ///< service头数组的下标
} GxBusEpgEventCurUseService;


/*添加epg信息时的结构体*/
typedef struct {
	uint32_t ts_id;                          ///< 和service_id一起确定一个节目
	uint32_t service_id;                     ///< 和ts_id一起确定一个节目
	uint32_t reference_service_id;           ///< 和ts_id一起用以确定一个service
	uint32_t original_id;                    ///< 用来确定一个service
	uint32_t event_id;                       ///< 和service id ts id original_id一起确定一个event
	uint32_t reference_event_id;             ///< service id ts id和event id唯一的确定一个event
	GxBusEpgEventTime* event_time;           ///< 该event的时间
	uint8_t* name;                           ///< 该event的名称
	uint32_t name_length;                    ///< name的长度
	uint8_t* detaile_description;            ///< 该event的描述
	uint32_t detaile_length;                 ///< detaile_description的长度
	GxBusEpgEventType type;                  ///< 该event的类型是当前 还是后续 或者是详细信息
	int8_t language[4];                      ///< 该event的语言
	GxBusEpgParentalRating* parental_rating; ///< 存储父母锁信息，如果没有父母锁信息请置为NULL
	uint32_t parental_rating_num;            ///< 父母锁信息的数量，如果没有父母锁信息请置为0
	GxBusEpgChannelEtt* channel_ett;         ///< 存储channel ett信息，如果没有channel ett请置为NULL
	uint32_t channel_ett_num;                ///< channel ett的数量，如果没有channel ett请置为0
	uint32_t ver;
}GxBusEpgEventAddInfo;

/* 用于比较两个event是否是同一个event，返回GX_BUS_EPG_OK:表示两个event相同，GX_BUS_EPG_ERR:表示
 * 两个event不相同。如果没有注册比较函数，则使用默认的比较方式，仅仅比较service id
 */
typedef struct {
	uint32_t ts_id;       ///< 和service_id一起确定一个节目
	uint32_t service_id;  ///< 和ts_id一起确定一个节目
	uint32_t original_id; ///< 用来确定一个service
}GxBusEpgEventComp;

typedef status_t (*GxBusEpgCheckEvent)(GxBusEpgEventComp* src,GxBusEpgEventComp* cur);
typedef status_t (*GxBusEpgModifyEvent)(GxBusEpgEventAddInfo* event);

/* Exported Functions ----------------------------------------------------- */

/**
 * @brief 初始化epg,使用epg前面必须得初始化
 *
 * @param uint32_t service_count:需要保存的service头的个数
 *        uint32_t event_count:需要保存的总的event数量
 *        uint32_t event_size:每个event的大小 包括 event name和event describe
 *        uint32_t epg_day:需要保存地epg的天数 一般是7天
 *
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_ERR:执行失败
 *          GX_BUS_EPG_MEM_ERR:epg申请内存失败
 */
status_t GxBus_EpgInit(uint32_t service_count, uint32_t event_count, uint32_t event_size, uint32_t epg_day);

/**
 * @brief 释放epg所占资源,包括硬件资源
 *
 * @param void
 *
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_ERR:执行失败
 */
status_t GxBus_EpgRelease(void);

/**
 * @brief 释放epg存储空间,使所有存储空间可用,开始全速解析
 *
 * @param void
 *
 * @return GX_BUS_EPG_OK:执行正常
 *         GX_BUS_EPG_ERR:执行失败
 */
status_t GxBus_EpgClean(void);

/**
 * @brief 获取当前已经添加到service头数组中的service
 *
 * @param GxBusEpgEventCurUseService** service:返回的指针
 *        uint32_t* num:数量,如果为0代表service头数组是空的
 *
 * @return   GX_BUS_EPG_OK:执行正常
 *           GX_BUS_EPG_NOT_LOCK:epg没有上锁
 *           GX_BUS_EPG_PARAMETER_ERR:传入的参数错误
 */
status_t GxBus_EpgCurUseServiceGet(GxBusEpgEventCurUseService** service,uint32_t* num);

/**
 * @brief 获得某个service,
 *
 * @param uint32_t ts_id,
 *        uint32_t service_id
 *        uint32_t original_id
 *        GxBusEpgServiceHead* service_head:保存头信息的空间
 *
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_PARAMETER_ERR:传入的参数不正确,无法匹配到正确值
 *          GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_EpgServiceGet(uint32_t ts_id,
		uint32_t service_id,
		uint32_t original_id,
		GxBusEpgServiceHead* service_head);

/**
 * @brief 获得某个event,
 *
 * @param uint32_t event_pos:event的pos
 *        GxBusEpgEventHead* event_head:保存头信息的空间
 *
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_PARAMETER_ERR:传入的参数不正确,无法匹配到正确值
 *          GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_EpgEventGet(uint32_t event_pos,GxBusEpgEventHead* event_head);

/**
 * @brief   添加一条event,
 *
 * @param   GxBusEpgEventAddInfo* info:添加的信息
 *
 * @return  GX_BUS_EPG_OK            : 执行正常
 *          GX_BUS_EPG_SERVICE_FULL  : service头数组满了
 *          GX_BUS_EPG_EVENT_FULL    : event头数组已经满了
 *          GX_BUS_EPG_MEM_POOL_FULL : 内存池满了
 *          GX_BUS_EPG_NOT_LOCK      : epg没有上锁
 *          GX_BUS_EPG_PARAMETER_ERR : 传入的参数错误
 *          GX_BUS_EPG_EVENT_EXIST   : 传入的event已经存在
 */
status_t GxBus_EpgInfoAdd(GxBusEpgEventAddInfo* info);

/**
 * @brief 清理指定的service的无效event信息,如果ts_id,service_id,original_id
 *        都为 0xffffffff 的话将会清除所有service的无效event
 *
 * @param    uint32_t ts_id:确定一条service
 *           uint32_t service_id:确定一条service
 *           uint32_t original_id:确定一条service
 *
 * @return   GX_BUS_EPG_OK:执行正常
 *           GX_BUS_EPG_NOT_LOCK:epg没有上锁
 *           GX_BUS_EPG_PARAMETER_ERR:传入的参数错误
 **/
status_t GxBus_EpgInvalidInfoClean(uint32_t ts_id,uint32_t service_id, uint32_t original_id);

/**
 * @brief 清理指定的service的全部event信息,并且释放service
 *
 * @param  uint32_t ts_id:确定一条service
 *         uint32_t service_id:确定一条service
 *         uint32_t original_id:确定一条service
 *
 * @return GX_BUS_EPG_OK:执行正常
 *         GX_BUS_EPG_NOT_LOCK:epg没有上锁
 *         GX_BUS_EPG_PARAMETER_ERR:传入的参数错误
 **/
status_t GxBus_EpgServiceClean(uint32_t ts_id,uint32_t service_id, uint32_t original_id);

/**
 * @brief 清理离当前播放的service最远的service的epg信息,该函数是当add返回full
 *        时,如果不想自己处理就调用此函数,
 * @param void
 *
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_ERR:执行失败
 *          GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_EpgFarServiceClean(void);

/**
 * @brief 获得某个nvod 的event, 用于获取nvod的名字
 * @param uint32_t reference_service_id:用于对比的 reference_service_id
 *        uint32_t reference_event_id:用于对比的 reference_event_id
 *	  GxBusEpgEventHead* event_head:保存头信息的空间
 *
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_PARAMETER_ERR:传入的参数不正确,无法匹配到正确值
 *          GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_NvodInfoGet(uint32_t ts_id,uint32_t reference_service_id,
		uint32_t reference_event_id,
		GxBusEpgEventHead* event);
/**
 * @brief  注册event是否相同的比较函数，没有注册则使用默认的比较方式，仅仅比较service id
 * @param
 * @return GX_BUS_EPG_OK:执行正常
 *         GX_BUS_EPG_PARAMETER_ERR:传入的参数错误
 *         GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_RegisterCompFunc(GxBusEpgCheckEvent fun);
/**
 * @brief   注销event是否相同的比较函数，从此以后使用默认的比较方式，仅仅比较service id
 * @param
 * @return  GX_BUS_EPG_OK:执行正常
 *          GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_UnregisterCompFunc(void);

/**
 * @brief     修改一条event的内容，包括name和descriptor
 * @param     uint32_t event_pos:用于定位修改哪条event
 *            GxBusEpgEventAddInfo* info:新的event信息
 * @return    GX_BUS_EPG_OK:执行正常
 *            GX_BUS_EPG_PARAMETER_ERR:传入的参数不正确,无法匹配到正确值
 *            GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_EpgEventModify(uint32_t event_pos,GxBusEpgEventAddInfo* info);

/**
 * @brief    注册修改event的回调函数，在保存event前被调佣
 * @param
 * @return   GX_BUS_EPG_OK:执行正常
 *           GX_BUS_EPG_PARAMETER_ERR:传入的参数不正确,无法匹配到正确值
 *           GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_RegisterModifyEventCb(GxBusEpgModifyEvent fun);
/**
 * @brief    注销修改event的回调函数
 * @param
 * @return   GX_BUS_EPG_OK:执行正常
 *           GX_BUS_EPG_PARAMETER_ERR:传入的参数不正确,无法匹配到正确值
 *           GX_BUS_EPG_NOT_LOCK:epg没有上锁
 */
status_t GxBus_UnregisterModifyEventCb(void);

__END_DECLS

#endif

/*@}*/

