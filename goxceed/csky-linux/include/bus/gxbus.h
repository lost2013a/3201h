/**
 * @file gxbus.h
 * @author lixb
 * @brief 服务总线架构实现文件
 * @example gxbus_demo.c 本例子解决如何通过BUS定义一个服务
 * @defgroup bus Goxceed Bus
 */
/*@{*/
#ifndef __GXBUS_H__
#define __GXBUS_H__

#include <gxtype.h>
#include <gxcore.h>
#include "gxbus_version.h"

__BEGIN_DECLS


/**名称最大长度，包括'\\0'*/
#define NAME_SIZE                   (32)
/**消息处理*/
#define GXMSG_OK                    (0)
/**永远等待*/
#define GX_INFINITE                 (0)


/**宏函数，msg消息指针，type消息所带数据类型，当type的大小与注册消息时的大小
 * 不同时，返回NULL
 */
#define GxBus_GetMsgPropertyPtr(msg, type)  \
	((msg)->size==sizeof(type)?(type*)((char*)(msg)+sizeof(GxMessage)) : NULL)

/**消息处理状态*/
typedef int32_t             GxMsgStatus;
/**消息ID类型*/
typedef uint32_t            GxMsgID;

/**调度器类型*/
typedef enum {
	GXBUS_SCHED_MSG,                    /**<消息调度器*/
	GXBUS_SCHED_CONSOLE,                /**<控制台调度器*/
	GXBUS_SCHED_TOTAL_NUM               /**<调度器类型总数量*/
} GxSchedType;

enum msg_prior {
	GXMSG_PRIOR_NORMAL = 0,
	GXMSG_PRIOR_FAST   = 1
};

/**消息结构体*/
typedef struct {
	GxMsgID     msg_id;                 /**<消息ID*/
	uint32_t    size;                   /**<消息所带数据大小*/
} GxMessage;

/**服务操作*/
typedef struct{
	char        name[NAME_SIZE];                                        /**<服务名称*/
	status_t    (*init)            (handle_t self,int priority_offset); /**<服务初始化函数入口*/
	void        (*destroy)         (handle_t self);                     /**<服务关闭函数入口*/
	GxMsgStatus (*msg_process)     (handle_t self, GxMessage* msg);     /**<服务消息处理函数入口*/
	void        (*console_process) (handle_t self);                     /**<服务控制台函数入口*/
	handle_t self;                                                      /**<服务的句柄*/
	int         priority_offset;                                        /**<该服务相对默认优先级的偏移，
	                                                                        例如-1代表在原有优先级基础上减一（也就是跑得更快），+1反之*/
}GxServiceClass;

typedef struct{
	uint32_t player_reserved_mem;//player 服务的内存配置 默认为1024*1024*10,最小为1024*1024*2
}GxServiceMemConf;

/**
 * @brief Service Bus初始化函数
 * @param [in] service_list   服务操作结体列表指针
 * @param [in] service_num         服务列表中服务数量
 * @return status_t                         初始化成功，返回GXCORE_SUCCESS
 * @remark 调用本函数将会初始化服务总线.
 *         本函数是服务注册到服务总线的方法之一,用户可以将已定义的服务定义成
 *         GxServiceClass* service_list
 * @see GxBus_Destroy
 */
status_t GxBus_Init(GxServiceClass* service_list, uint32_t service_num);

/**
 * @brief Service Bus关闭函数
 * @param 无
 * @return status_t
 * @remark 调用本函数会关闭服务总线,并将已经注册到服务总线上的服务关闭
 * @see GxBus_Init
 */
status_t GxBus_Destroy(void);

/**
 * @brief 通过调度器名查找调度器句柄
 * @param [in] name                         调度器名
 * @return handle_t                         调度器句柄，查找成功，返回调度器句柄，
 *                                          不成功，返回GXCORE_INVALID_POINTER
 * @see GxBus_SchedulerCreate
 */
handle_t GxBus_SchedulerFindByName(const char* name);

/**
 * @brief 创建调度器
 * @param [in] name         调度器名
 * @param [in] type         调度器类型
 * @param [in] stack_size   调度器所在线程栈大小
 * @param [in] prior        调度器所在线程优先级
 * @return handle_t                 调度器句柄，如果创建成功返回调度器句柄
 *                                  如果创建失败返回GXCORE_INVALID_POINTER
 * @remark 本函数创建一个调度器
 *         调度器是服务的容器,服务的执行在调度器中执行.
 *         调度器具有两种类型,消息调度器,控制台调度器
 * @see
 */
handle_t GxBus_SchedulerCreate(const char* name, GxSchedType type, size_t stack_size, uint8_t prior);

/**
 * @brief 关闭调度器
 * @param [in] h_scheduler 调度器句柄
 * @return status_t                 关闭成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 关闭调度器，GxBus_SchedulerCreate的反操作
 *         当这个调度器已经和服务关联时，用户不需要显式调用本函数，关闭服务时,
 *         会隐式调用本函数释放调度器资源.
 *         如果一个调度器只是调用GxBus_SchedulerCreate创建,并没有与服务关联时,
 *         用户需要显示调用本函数关闭调度器
 * @see
 */
status_t GxBus_SchedulerDestroy(handle_t h_scheduler);

/**
 * @brief 创建服务
 * @param [in] ops    服务结构体
 * @return handle_t                 操作句柄，如果成功，返回服务句柄，失败返回
 *                                  GXCORE_INVALID_POINTER
 * @remark 创建一个服务,在服务总线中,已经预定义了几个服务CA,Console,EPG,GUI_View
 *         Player,Search,SI几个服务,当用户需要使用这个几个服务时,只需要将文件
 *         gxservices.h定义的服务在GxBus_Init()将其注册进服务总线即可.
 *         本函数用于用户自定义服务实现,用户在GxBus_Init()调用之后,调用GxBus_ServiceCreate
 *         创建自己的服务
 * @see ::GxBus_ServiceDestroy ::GxBus_Init
 */
handle_t GxBus_ServiceCreate(GxServiceClass* ops);

/**
 * @brief 关闭服务
 * @param [in] h_service   服务句柄
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 关闭服务.本函数将会释放服务相关资源
 *         在服务总线中,用户不需要显示调用此函数
 * @see ::GxBus_ServiceCreate
 */
status_t GxBus_ServiceDestroy(handle_t h_service);

/**
 * @brief 通过服务名查找服务句柄
 * @param [in] name     服务名
 * @return handle_t                 操作句柄，如果成功，返回服务句柄，失败返回
 *                                  GXCORE_INVALID_POINTER
 * @see ::GxBus_ServiceCreate
 */
handle_t GxBus_ServiceFindByName(const char* name);

/**
 * @brief 关联服务与调度器
 * @param [in] h_service   服务句柄
 * @param [in] h_scheduler 调度器句柄
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark  本函数将会关联服务与调度器
 *          服务将会在关联的调度器上运行
 *          本函数必须服务的GxServiceClass::init()函数中调用
 * @see ::GxBus_ServiceUnlink
 */
status_t GxBus_ServiceLink(handle_t h_service, handle_t h_scheduler);

/**
 * @brief 去关联服务
 * @param [in]  h_service  服务句柄
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark  本函数是GxBus_ServiceLink函数的反操作
 *          调用本函数将会释放与服务关联的资源，包括调度器.
 *          本函数必须服务的GxServiceClass::destroy()函数中调用
 * @see ::GxBus_ServiceLink
 */
status_t GxBus_ServiceUnlink(handle_t h_service);

/**
 * @brief 注册消息，即将一个消息注册到服务总线
 * @param [in] msg_id       消息标识符
 * @param [in] size         消息携带参数大小
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 本函数是消息的注册函数，注册这个消息必须带msg_id和这个消息所携带参数
 *         的大小
 *         这个函数必须在服务的GxServiceClass::init()函数中调用
 * @see ::GxBus_MessageUnregister
 */
status_t GxBus_MessageRegister(GxMsgID msg_id, int32_t size);

/**
 * @brief 去注册消息
 * @param [in] msg_id       消息标识符
 * @return void                     无
 * @remark 本函数是GxBus_MessageRegister的反操作，关闭一个服务时，必须把本服务
 *         注册的消息调用GxBus_MessageUnregister()去注册之后，才可以正确关闭服务
 *         这个函数必须在服务的GxServiceClass::destroy()函数中调用
 * @see ::GxBus_MessageRegister
 */
void GxBus_MessageUnregister(GxMsgID msg_id);

/**
 * @brief 监听消息
 * @param [in] h_service   服务句柄
 * @param [in] msg_id       消息标识符
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 调用本函数表示，这个服务对消息msg_id感兴趣，会对这个消息进行处理
 *         这个函数必须在GxServiceClass::init中调用。
 *         服务总线只会把已经listen的消息发给服务。
 *         如果msg_id没有被GxBus_MessageRegister注册，则函数返回GXCORE_ERROR
 * @see ::GxBus_MessageRegister ::GxBus_MessageUnListen
 */
status_t GxBus_MessageListen(handle_t h_service, GxMsgID msg_id);

/**
 * @brief 去监听消息
 * @param [in]  h_service  服务句柄
 * @param [in]  msg_id      消息标识符
 * @return      status_t            函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark  这个函数是GxBus_MessageListen的反操作，当关闭一个服务时，必须先调用本
 *          函数去这个服务监听的消息，然后才可以调用GxBus_MessageUnregister
 *          这个函数必须在服务的GxServiceClass::destroy()函数中调用
 * @see ::GxBus_MessageListen ::GxBus_MessageUnregister ::GxServiceClass
 */
status_t GxBus_MessageUnListen(handle_t h_service, GxMsgID msg_id);

/**
 * @brief 生成一个消息实例
 * @param [in] msg_id       消息标识符
 * @return GxMessage*               生成的消息实例指针，如果失败返回NULL
 * @remark  此函数生成一个消息实例。
 *          函数输入的msg_id必须已经调用GxBus_MessageRegister对这个消息标识符先
 *          行注册，才能生成成功，否则失败
 * @see ::GxBus_MessageFree ::GxBus_MessageRegister
 */
GxMessage *GxBus_MessageNew(GxMsgID msg_id);

/**
 * @brief 释放一个消息实例
 * @param [in] message   消息结构体指针
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 此函数只会在消息采用同步发送处理方式（GxBus_MessageSendWait）时才需要
 *         调用，因为对于服务总线来说采用同步方式发送，服务总线无法预知这个消息
 *         实例需要在何时释放。
 *         当采用异步发送处理方式（GxBus_MessageSend）时，不需要用户调用本接口，
 *         服务总线自动完成释放功能
 * @see ::GxBus_MessageNew ::GxBus_MessageSendWait
 */
status_t GxBus_MessageFree(GxMessage* message);

/**
 * @brief 发送一个消息实例，带优先级
 * @param [in] message   消息结构体指针
 * @param [in] priority  优先级
 *                       GXMSG_PRIOR_NORMAL: 普通消息，消息添加到消息队列的尾部，顺序执行
 *                       GXMSG_PRIOR_FAST: 优先消息，消息添加到消息队列的前面，优先执行
 * @return status_t
 *         函数执行状态，成功，返回GXCORE_SUCCESS
 *         失败返回，GXCORE_ERROR
 * @remark 消息调用 GxBus_MessageSendPriority 发送，表示这个消息的发送处理方式是采用异步方式，
 *         当采用这种方式时，函数立即返回，这时这个消息可能还未被处理。
 *         因此当发送方向处理方发送一个状态，但并不关心处理结果时，通常采用这种方式。
 *         如果发送的消息没有注册，或者没有服务在listen这个消息，函数返回
 *         GXCORE_ERROR
 * @see ::GxBus_MessageSendWait ::GxBus_MessageNew
 */
status_t GxBus_MessageSendPriority(GxMessage *message, int priority);

/**
 * @brief 发送一个消息实例，普通优先级
 * @param [in] message   消息结构体指针
 * @return status_t
 *         函数执行状态，成功，返回GXCORE_SUCCESS
 *         失败返回，GXCORE_ERROR
 * @remark 消息调用GxBus_MessageSend发送，表示这个消息的发送处理方式是采用异步方式，
 *         当采用这种方式时，函数立即返回，这时这个消息可能还未被处理。
 *         因此当发送方向处理方发送一个状态，但并不关心处理结果时，通常采用这种方式。
 *         如果发送的消息没有注册，或者没有服务在listen这个消息，函数返回
 *         GXCORE_ERROR
 * @see ::GxBus_MessageSendWait ::GxBus_MessageNew
 */
status_t GxBus_MessageSend(GxMessage* message);

/**
 * @brief 发送一个消息，并直到消息已经被处理才返回
 * @param [in] message      消息结构体指针
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 消息调用GxBus_MessageSendWait发送，表示这个消息的发送处理方式是采用同步方式，
 *         当采用这种方式时，函数将会等待直到这个消息被服务处理后才返回，这时用户
 *         需要调用GxBus_MessageFree释放消息实例。
 *         当发送方需要从处理方获取处理结果时，通常采用这种方式。
 *         如果发送的消息没有注册，或者没有服务在listen这个消息，函数返回
 *         GXCORE_ERROR
 * @see ::GxBus_MessageFree ::GxBus_MessageNew
 */
status_t GxBus_MessageSendWait(GxMessage* message);

/**
 * @brief 清空消息
 * @param [in] h_service      服务句柄
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 调用本函数，将清空h_service服务消息队列中的所有消息
 * @see ::GxBus_MessageFree ::GxBus_MessageNew
 */
status_t GxBus_MessageEmpty(handle_t h_service);

/**
 * @brief 通过ops里的信息 清空消息
 * @param [GxServiceClass] ops      服务的ops
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 * @remark 调用本函数，将清空服务消息队列中的所有消息
 * @see ::GxBus_MessageFree ::GxBus_MessageNew
 */
status_t GxBus_MessageEmptyByOps(GxServiceClass* ops);

/**
 * @brief 配置各个服务的内存,如果参数为null，则为默认运行环境256MB的配置.
 * @param [GxServiceMemConf] mem    服务的
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 */
status_t GxBus_ServiceMemConfSet(GxServiceMemConf* mem);

/**
 * @brief 获取当前各个服务的内存配置情况，
 * @param [GxServiceMemConf] mem    服务的
 * @return status_t                 函数执行状态，成功，返回GXCORE_SUCCESS
 *                                  失败返回，GXCORE_ERROR
 */
status_t GxBus_ServiceMemConfGet(GxServiceMemConf* mem);

__END_DECLS

#endif
/*@}*/
