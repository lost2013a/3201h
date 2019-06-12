/**
 * @file gxbus.h
 * @author lixb
 * @brief �������߼ܹ�ʵ���ļ�
 * @example gxbus_demo.c �����ӽ�����ͨ��BUS����һ������
 * @defgroup bus Goxceed Bus
 */
/*@{*/
#ifndef __GXBUS_H__
#define __GXBUS_H__

#include <gxtype.h>
#include <gxcore.h>
#include "gxbus_version.h"

__BEGIN_DECLS


/**������󳤶ȣ�����'\\0'*/
#define NAME_SIZE                   (32)
/**��Ϣ����*/
#define GXMSG_OK                    (0)
/**��Զ�ȴ�*/
#define GX_INFINITE                 (0)


/**�꺯����msg��Ϣָ�룬type��Ϣ�����������ͣ���type�Ĵ�С��ע����Ϣʱ�Ĵ�С
 * ��ͬʱ������NULL
 */
#define GxBus_GetMsgPropertyPtr(msg, type)  \
	((msg)->size==sizeof(type)?(type*)((char*)(msg)+sizeof(GxMessage)) : NULL)

/**��Ϣ����״̬*/
typedef int32_t             GxMsgStatus;
/**��ϢID����*/
typedef uint32_t            GxMsgID;

/**����������*/
typedef enum {
	GXBUS_SCHED_MSG,                    /**<��Ϣ������*/
	GXBUS_SCHED_CONSOLE,                /**<����̨������*/
	GXBUS_SCHED_TOTAL_NUM               /**<����������������*/
} GxSchedType;

enum msg_prior {
	GXMSG_PRIOR_NORMAL = 0,
	GXMSG_PRIOR_FAST   = 1
};

/**��Ϣ�ṹ��*/
typedef struct {
	GxMsgID     msg_id;                 /**<��ϢID*/
	uint32_t    size;                   /**<��Ϣ�������ݴ�С*/
} GxMessage;

/**�������*/
typedef struct{
	char        name[NAME_SIZE];                                        /**<��������*/
	status_t    (*init)            (handle_t self,int priority_offset); /**<�����ʼ���������*/
	void        (*destroy)         (handle_t self);                     /**<����رպ������*/
	GxMsgStatus (*msg_process)     (handle_t self, GxMessage* msg);     /**<������Ϣ���������*/
	void        (*console_process) (handle_t self);                     /**<�������̨�������*/
	handle_t self;                                                      /**<����ľ��*/
	int         priority_offset;                                        /**<�÷������Ĭ�����ȼ���ƫ�ƣ�
	                                                                        ����-1������ԭ�����ȼ������ϼ�һ��Ҳ�����ܵø��죩��+1��֮*/
}GxServiceClass;

typedef struct{
	uint32_t player_reserved_mem;//player ������ڴ����� Ĭ��Ϊ1024*1024*10,��СΪ1024*1024*2
}GxServiceMemConf;

/**
 * @brief Service Bus��ʼ������
 * @param [in] service_list   ������������б�ָ��
 * @param [in] service_num         �����б��з�������
 * @return status_t                         ��ʼ���ɹ�������GXCORE_SUCCESS
 * @remark ���ñ����������ʼ����������.
 *         �������Ƿ���ע�ᵽ�������ߵķ���֮һ,�û����Խ��Ѷ���ķ������
 *         GxServiceClass* service_list
 * @see GxBus_Destroy
 */
status_t GxBus_Init(GxServiceClass* service_list, uint32_t service_num);

/**
 * @brief Service Bus�رպ���
 * @param ��
 * @return status_t
 * @remark ���ñ�������رշ�������,�����Ѿ�ע�ᵽ���������ϵķ���ر�
 * @see GxBus_Init
 */
status_t GxBus_Destroy(void);

/**
 * @brief ͨ�������������ҵ��������
 * @param [in] name                         ��������
 * @return handle_t                         ��������������ҳɹ������ص����������
 *                                          ���ɹ�������GXCORE_INVALID_POINTER
 * @see GxBus_SchedulerCreate
 */
handle_t GxBus_SchedulerFindByName(const char* name);

/**
 * @brief ����������
 * @param [in] name         ��������
 * @param [in] type         ����������
 * @param [in] stack_size   �����������߳�ջ��С
 * @param [in] prior        �����������߳����ȼ�
 * @return handle_t                 �������������������ɹ����ص��������
 *                                  �������ʧ�ܷ���GXCORE_INVALID_POINTER
 * @remark ����������һ��������
 *         �������Ƿ��������,�����ִ���ڵ�������ִ��.
 *         ������������������,��Ϣ������,����̨������
 * @see
 */
handle_t GxBus_SchedulerCreate(const char* name, GxSchedType type, size_t stack_size, uint8_t prior);

/**
 * @brief �رյ�����
 * @param [in] h_scheduler ���������
 * @return status_t                 �رճɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark �رյ�������GxBus_SchedulerCreate�ķ�����
 *         ������������Ѿ��ͷ������ʱ���û�����Ҫ��ʽ���ñ��������رշ���ʱ,
 *         ����ʽ���ñ������ͷŵ�������Դ.
 *         ���һ��������ֻ�ǵ���GxBus_SchedulerCreate����,��û����������ʱ,
 *         �û���Ҫ��ʾ���ñ������رյ�����
 * @see
 */
status_t GxBus_SchedulerDestroy(handle_t h_scheduler);

/**
 * @brief ��������
 * @param [in] ops    ����ṹ��
 * @return handle_t                 �������������ɹ������ط�������ʧ�ܷ���
 *                                  GXCORE_INVALID_POINTER
 * @remark ����һ������,�ڷ���������,�Ѿ�Ԥ�����˼�������CA,Console,EPG,GUI_View
 *         Player,Search,SI��������,���û���Ҫʹ�������������ʱ,ֻ��Ҫ���ļ�
 *         gxservices.h����ķ�����GxBus_Init()����ע����������߼���.
 *         �����������û��Զ������ʵ��,�û���GxBus_Init()����֮��,����GxBus_ServiceCreate
 *         �����Լ��ķ���
 * @see ::GxBus_ServiceDestroy ::GxBus_Init
 */
handle_t GxBus_ServiceCreate(GxServiceClass* ops);

/**
 * @brief �رշ���
 * @param [in] h_service   ������
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark �رշ���.�����������ͷŷ��������Դ
 *         �ڷ���������,�û�����Ҫ��ʾ���ô˺���
 * @see ::GxBus_ServiceCreate
 */
status_t GxBus_ServiceDestroy(handle_t h_service);

/**
 * @brief ͨ�����������ҷ�����
 * @param [in] name     ������
 * @return handle_t                 �������������ɹ������ط�������ʧ�ܷ���
 *                                  GXCORE_INVALID_POINTER
 * @see ::GxBus_ServiceCreate
 */
handle_t GxBus_ServiceFindByName(const char* name);

/**
 * @brief ���������������
 * @param [in] h_service   ������
 * @param [in] h_scheduler ���������
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark  ������������������������
 *          ���񽫻��ڹ����ĵ�����������
 *          ��������������GxServiceClass::init()�����е���
 * @see ::GxBus_ServiceUnlink
 */
status_t GxBus_ServiceLink(handle_t h_service, handle_t h_scheduler);

/**
 * @brief ȥ��������
 * @param [in]  h_service  ������
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark  ��������GxBus_ServiceLink�����ķ�����
 *          ���ñ����������ͷ�������������Դ������������.
 *          ��������������GxServiceClass::destroy()�����е���
 * @see ::GxBus_ServiceLink
 */
status_t GxBus_ServiceUnlink(handle_t h_service);

/**
 * @brief ע����Ϣ������һ����Ϣע�ᵽ��������
 * @param [in] msg_id       ��Ϣ��ʶ��
 * @param [in] size         ��ϢЯ��������С
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ����������Ϣ��ע�ắ����ע�������Ϣ�����msg_id�������Ϣ��Я������
 *         �Ĵ�С
 *         ������������ڷ����GxServiceClass::init()�����е���
 * @see ::GxBus_MessageUnregister
 */
status_t GxBus_MessageRegister(GxMsgID msg_id, int32_t size);

/**
 * @brief ȥע����Ϣ
 * @param [in] msg_id       ��Ϣ��ʶ��
 * @return void                     ��
 * @remark ��������GxBus_MessageRegister�ķ��������ر�һ������ʱ������ѱ�����
 *         ע�����Ϣ����GxBus_MessageUnregister()ȥע��֮�󣬲ſ�����ȷ�رշ���
 *         ������������ڷ����GxServiceClass::destroy()�����е���
 * @see ::GxBus_MessageRegister
 */
void GxBus_MessageUnregister(GxMsgID msg_id);

/**
 * @brief ������Ϣ
 * @param [in] h_service   ������
 * @param [in] msg_id       ��Ϣ��ʶ��
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ���ñ�������ʾ������������Ϣmsg_id����Ȥ����������Ϣ���д���
 *         �������������GxServiceClass::init�е��á�
 *         ��������ֻ����Ѿ�listen����Ϣ��������
 *         ���msg_idû�б�GxBus_MessageRegisterע�ᣬ��������GXCORE_ERROR
 * @see ::GxBus_MessageRegister ::GxBus_MessageUnListen
 */
status_t GxBus_MessageListen(handle_t h_service, GxMsgID msg_id);

/**
 * @brief ȥ������Ϣ
 * @param [in]  h_service  ������
 * @param [in]  msg_id      ��Ϣ��ʶ��
 * @return      status_t            ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark  ���������GxBus_MessageListen�ķ����������ر�һ������ʱ�������ȵ��ñ�
 *          ����ȥ��������������Ϣ��Ȼ��ſ��Ե���GxBus_MessageUnregister
 *          ������������ڷ����GxServiceClass::destroy()�����е���
 * @see ::GxBus_MessageListen ::GxBus_MessageUnregister ::GxServiceClass
 */
status_t GxBus_MessageUnListen(handle_t h_service, GxMsgID msg_id);

/**
 * @brief ����һ����Ϣʵ��
 * @param [in] msg_id       ��Ϣ��ʶ��
 * @return GxMessage*               ���ɵ���Ϣʵ��ָ�룬���ʧ�ܷ���NULL
 * @remark  �˺�������һ����Ϣʵ����
 *          ���������msg_id�����Ѿ�����GxBus_MessageRegister�������Ϣ��ʶ����
 *          ��ע�ᣬ�������ɳɹ�������ʧ��
 * @see ::GxBus_MessageFree ::GxBus_MessageRegister
 */
GxMessage *GxBus_MessageNew(GxMsgID msg_id);

/**
 * @brief �ͷ�һ����Ϣʵ��
 * @param [in] message   ��Ϣ�ṹ��ָ��
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark �˺���ֻ������Ϣ����ͬ�����ʹ���ʽ��GxBus_MessageSendWait��ʱ����Ҫ
 *         ���ã���Ϊ���ڷ���������˵����ͬ����ʽ���ͣ����������޷�Ԥ֪�����Ϣ
 *         ʵ����Ҫ�ں�ʱ�ͷš�
 *         �������첽���ʹ���ʽ��GxBus_MessageSend��ʱ������Ҫ�û����ñ��ӿڣ�
 *         ���������Զ�����ͷŹ���
 * @see ::GxBus_MessageNew ::GxBus_MessageSendWait
 */
status_t GxBus_MessageFree(GxMessage* message);

/**
 * @brief ����һ����Ϣʵ���������ȼ�
 * @param [in] message   ��Ϣ�ṹ��ָ��
 * @param [in] priority  ���ȼ�
 *                       GXMSG_PRIOR_NORMAL: ��ͨ��Ϣ����Ϣ��ӵ���Ϣ���е�β����˳��ִ��
 *                       GXMSG_PRIOR_FAST: ������Ϣ����Ϣ��ӵ���Ϣ���е�ǰ�棬����ִ��
 * @return status_t
 *         ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *         ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ��Ϣ���� GxBus_MessageSendPriority ���ͣ���ʾ�����Ϣ�ķ��ʹ���ʽ�ǲ����첽��ʽ��
 *         ���������ַ�ʽʱ�������������أ���ʱ�����Ϣ���ܻ�δ������
 *         ��˵����ͷ���������һ��״̬�����������Ĵ�����ʱ��ͨ���������ַ�ʽ��
 *         ������͵���Ϣû��ע�ᣬ����û�з�����listen�����Ϣ����������
 *         GXCORE_ERROR
 * @see ::GxBus_MessageSendWait ::GxBus_MessageNew
 */
status_t GxBus_MessageSendPriority(GxMessage *message, int priority);

/**
 * @brief ����һ����Ϣʵ������ͨ���ȼ�
 * @param [in] message   ��Ϣ�ṹ��ָ��
 * @return status_t
 *         ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *         ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ��Ϣ����GxBus_MessageSend���ͣ���ʾ�����Ϣ�ķ��ʹ���ʽ�ǲ����첽��ʽ��
 *         ���������ַ�ʽʱ�������������أ���ʱ�����Ϣ���ܻ�δ������
 *         ��˵����ͷ���������һ��״̬�����������Ĵ�����ʱ��ͨ���������ַ�ʽ��
 *         ������͵���Ϣû��ע�ᣬ����û�з�����listen�����Ϣ����������
 *         GXCORE_ERROR
 * @see ::GxBus_MessageSendWait ::GxBus_MessageNew
 */
status_t GxBus_MessageSend(GxMessage* message);

/**
 * @brief ����һ����Ϣ����ֱ����Ϣ�Ѿ�������ŷ���
 * @param [in] message      ��Ϣ�ṹ��ָ��
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ��Ϣ����GxBus_MessageSendWait���ͣ���ʾ�����Ϣ�ķ��ʹ���ʽ�ǲ���ͬ����ʽ��
 *         ���������ַ�ʽʱ����������ȴ�ֱ�������Ϣ���������ŷ��أ���ʱ�û�
 *         ��Ҫ����GxBus_MessageFree�ͷ���Ϣʵ����
 *         �����ͷ���Ҫ�Ӵ�����ȡ������ʱ��ͨ���������ַ�ʽ��
 *         ������͵���Ϣû��ע�ᣬ����û�з�����listen�����Ϣ����������
 *         GXCORE_ERROR
 * @see ::GxBus_MessageFree ::GxBus_MessageNew
 */
status_t GxBus_MessageSendWait(GxMessage* message);

/**
 * @brief �����Ϣ
 * @param [in] h_service      ������
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ���ñ������������h_service������Ϣ�����е�������Ϣ
 * @see ::GxBus_MessageFree ::GxBus_MessageNew
 */
status_t GxBus_MessageEmpty(handle_t h_service);

/**
 * @brief ͨ��ops�����Ϣ �����Ϣ
 * @param [GxServiceClass] ops      �����ops
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 * @remark ���ñ�����������շ�����Ϣ�����е�������Ϣ
 * @see ::GxBus_MessageFree ::GxBus_MessageNew
 */
status_t GxBus_MessageEmptyByOps(GxServiceClass* ops);

/**
 * @brief ���ø���������ڴ�,�������Ϊnull����ΪĬ�����л���256MB������.
 * @param [GxServiceMemConf] mem    �����
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 */
status_t GxBus_ServiceMemConfSet(GxServiceMemConf* mem);

/**
 * @brief ��ȡ��ǰ����������ڴ����������
 * @param [GxServiceMemConf] mem    �����
 * @return status_t                 ����ִ��״̬���ɹ�������GXCORE_SUCCESS
 *                                  ʧ�ܷ��أ�GXCORE_ERROR
 */
status_t GxBus_ServiceMemConfGet(GxServiceMemConf* mem);

__END_DECLS

#endif
/*@}*/
