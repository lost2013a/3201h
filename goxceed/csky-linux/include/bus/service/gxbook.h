/**@defgroup book_service BOOK Service*/
 /*@{*/
/* Define to prevent recursive inclusion */
#ifndef __GX_BOOK_H__
#define __GX_BOOK_H__

#include "gxbus.h"
#include "gxcore.h"
#include <time.h>

__BEGIN_DECLS

/**最大能存储的book结点数量*/
#define MAX_BOOK_NUM	(32)

#define MAX_BOOK_STRUCT_LEN	(56)


/**
 * @brief	触发book时，所执行的回调函数，可直接执行功能代码或者发消息
 * @param   struct_buf 存储与book结构体中的自定义数据结构指针
 * @Return  void
 */
typedef void (*GxBookExec)(uint8_t *struct_buf);

/**
 * book类型，此book用作何种功能
 */
typedef enum
{
	BOOK_PROGRAM_PLAY = 1, ///< 预约播放
	BOOK_POWER_ON = 1<<1,  ///< 预约开机
	BOOK_POWER_OFF = 1<<2, ///< 预约关机
	BOOK_TYPE_1 = 1<<3,    ///< 预留功能1
	BOOK_TYPE_2 = 1<<4,    ///< 预留功能2
	BOOK_TYPE_3 = 1<<5,    ///< 预留功能3
}GxBookType;

/**
 * book的触发模式
 */
typedef enum
{
	BOOK_TRIG_OFF = 0,    ///< 关闭此book
	BOOK_TRIG_ING,        ///< 段触发中间状态
	BOOK_TRIG_BY_POINT,   ///< 只在某一个时间点触发book
	BOOK_TRIG_BY_SEGMENT, ///< 在某一时间段内都可触发book, 段跨度暂时为20小时
} GxBookTriggerMode;

/**
 * book重复模式，将需要的日子或在一起赋值给mode即可
 */
typedef struct
{
	uint32_t mode;
#define BOOK_REPEAT_MON       (1<<1)
#define BOOK_REPEAT_TUES      (1<<2)
#define BOOK_REPEAT_WED       (1<<3)
#define BOOK_REPEAT_THURS     (1<<4)
#define BOOK_REPEAT_FRI       (1<<5)
#define BOOK_REPEAT_SAT       (1<<6)
#define BOOK_REPEAT_SUN       (1)
#define BOOK_REPEAT_EVERY_DAY (0x7f)
#define BOOK_REPEAT_ONCE      (1<<8)
}GxBookRepeatMode;

/**
 * book的结构体，在建立、销毁、修改、开始、停止时会用到
 */
typedef struct
{
	int32_t   id;                            ///< 唯一标识某个book的id号，在建立时获得
	uint32_t  pos;                           ///< 从0开始一直往上增加，可标识book的建立顺序
	GxBookType book_type;                    ///< 描述此book为何功能而建立
	GxBookTriggerMode  trigger_mode;         ///< book的触发模式
	GxBookRepeatMode  repeat_mode;           ///< book事件的重复模式
	time_t time_stamp;                       ///< 建立book时，不要配置此值，作用:预防段触发模式下的多次触发
	time_t trigger_time_start;               ///< 时间点触发配置该值，时间段触发的起始值
	time_t trigger_time_end;                 ///< 时间点触发无需配置，时间段触发的结束值，段间隔最大为20小时
	uint32_t struct_size;                    ///< 存储结构的大小
	uint8_t struct_buf[MAX_BOOK_STRUCT_LEN]; ///< 将结构体数据拷贝到此
}GxBook;

/**
 * 在获取book时所用到的数据结构
 */
typedef struct
{
	GxBookType book_type;  ///< 描述此book为何功能而建立
	uint32_t  book_number; ///< 该功能的book下有几个book
	GxBook  *book;         ///< 存储某类book type的信息
}GxBookGet;

typedef GxBook GxMsgProperty_BookTrigger;
typedef GxBook GxMsgProperty_BookFinish;  // 段触发有此消息
typedef GxBook* GxMsgProperty_BookCreate;
typedef GxBook* GxMsgProperty_BookDestroy;
typedef GxBook* GxMsgProperty_BookModify;
typedef GxBookGet* GxMsgProperty_BookGet;

__END_DECLS

#endif /* __GX_BOOK_H__ */
/*@}*/


