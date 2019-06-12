/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __GXEPG_MANAGE_H__
#define __GXEPG_MANAGE_H__

#include <time.h>
#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

/*����ֵ*/
#define GX_BUS_EPG_OK GXCORE_SUCCESS
#define GX_BUS_EPG_ERR GXCORE_ERROR
#define GX_BUS_EPG_EVENT_EXIST       (0x7ffffff9)
#define GX_BUS_EPG_SERVICE_FULL      (0x7ffffffa)
#define GX_BUS_EPG_MEM_POOL_FULL     (0x7ffffffb)
#define GX_BUS_EPG_EVENT_FULL        (0x7ffffffc)
#define GX_BUS_EPG_PARAMETER_ERR     (0x7ffffffd)
#define GX_BUS_EPG_NOT_LOCK          (0x7ffffffe)
#define GX_BUS_EPG_MEM_ERR           (0x7fffffff)


#define GX_BUS_MEM_POOL_CELL_SIZE (52)///<�ڴ��ÿ����Ԫ�Ĵ�С
#define GX_BUS_EPG_INVALID_POS (0x7ffffff8)///<�����������Ч�±�

#define EPG_MALLOC

///<�汾�ŷ����仯ʱ�������Ĭ��Ϊ����ȡ�κ���Ϊ
//
//������
//int32_t act = EPG_MANAGER_VER_ACT_DEL_EVENT;
//GxBus_ConfigSetInt(EPG_MANAGER_VER_ACT,&act);


#define EPG_MANAGER_VER_ACT	"epg_manager>ver_act"

#define EPG_MANAGER_VER_ACT_DEFAULT (0)
#define EPG_MANAGER_VER_ACT_DEL_EVENT (1)


/* Exported Types --------------------------------------------------------- */

/*�ڴ�ص�Ԫ�ռ�Ľṹ��*/
#ifdef EPG_MALLOC
typedef struct {
	int8_t* content;
	uint32_t  size;
} GxBusEpgMemPoolCell;
#else
typedef struct {
	uint8_t content[GX_BUS_MEM_POOL_CELL_SIZE-4]; ///< ǰ48�ֽڴ�����
	void* next_Cell;                              ///< ���ĸ��ֽ�����һ����Ԫ��ָ��
} GxBusEpgMemPoolCell;
#endif

/*ʱ����Ϣ*/
typedef struct {
	time_t  start_time; ///< ʹ��������ʾ
	time_t  duration;   ///< ����ʱ��,Ҳ��������ʾ
} GxBusEpgEventTime;

/* ��ǰ������Ϣ */
typedef struct {
	GxBusEpgMemPoolCell* name;                ///< event���ֵ���ʼָ��
	GxBusEpgMemPoolCell* detaile_description; ///< event��ϸ��������ʼָ��
	GxBusEpgEventTime time;                   ///< ��event�Ŀ�ʼʱ��ͳ���ʱ��
} GxBusEpgEventPFHead;

/* first event�ṹ���ӹ���pos�⻹�ü������Ե�iso639�� */
typedef struct {
	int8_t language[4];
	uint32_t pos;        ///< �������µĵ�һ��event���±�
	void* next;
} GxBusEpgFirstEvent;

/* ��ĸ����Ϣ�ýṹ */
typedef struct {
	int8_t country[4];
	uint32_t rating;
} GxBusEpgParentalRating;

/* channel ett�ṹ */
typedef struct {
	int8_t language[4];
	int8_t* info;
} GxBusEpgChannelEtt;

/*epg ��service��ͷ�ṹ,�൱��ÿ��service epg��Ϣ����ʼλ��*/
typedef struct {
	uint32_t use_flag;                       ///< ��ͷ���Ƿ�ʹ�� 1--��ʹ�� 0--����
	uint32_t ts_id;                          ///< ��service_idһ������ȷ��һ��service
	uint32_t service_id;                     ///< ��ts_idһ������ȷ��һ��service
	uint32_t reference_service_id;           ///< ��ts_idһ������ȷ��һ��service
	uint32_t original_id;                    ///< ����ȷ��һ��service
	GxBusEpgFirstEvent* first_event;         ///< ��service�ĵ�һ��event���±�
	//uint32_t last_event;                   ///< ��service�����һ��event�±�,���ڰ�ʱ�����eventʱ������,��ʱû����
	GxBusEpgEventPFHead present;             ///< ��ǰ��Ϣ
	GxBusEpgEventPFHead follow;              ///< ������Ϣ
	GxBusEpgParentalRating* parental_rating; ///< �洢��ĸ����Ϣ
	uint32_t parental_rating_num;            ///< ��ĸ����Ϣ������
	GxBusEpgChannelEtt* channel_ett;         ///< �洢channel ett��Ϣ
	uint32_t channel_ett_num;                ///< channel ett������
	uint16_t detaile_description_ver;        ///< ��ϸ�����İ汾��
} GxBusEpgServiceHead;

typedef struct {
	uint32_t event_id;                        ///< service id ts id��event idΨһ��ȷ��һ��event
	uint32_t reference_event_id;              ///< service id ts id��event idΨһ��ȷ��һ��event
	GxBusEpgMemPoolCell* name;                ///< event���ֵ���ʼָ��
	GxBusEpgMemPoolCell* detaile_description; ///< event��ϸ��������ʼָ��
	GxBusEpgEventTime time;                   ///< ��event�Ŀ�ʼʱ��ͳ���ʱ��
	uint32_t next_event;                      ///< ��һ��event���±�
} GxBusEpgEventHead;



/* event ����*/
typedef enum {
	GX_EVENT_PRESENT = 0, ///< present��Ϣ
	GX_EVENT_FOLLOW ,     ///< follow��Ϣ
	GX_EVENT_DETAILE,     ///< detaile��Ϣ
} GxBusEpgEventType;


/*�Ѿ���ӵ�serviceͷ�����е�service*/
typedef struct {
	uint32_t ts_id;       ///< ��service_idһ������ȷ��һ��service
	uint32_t service_id;  ///< ��ts_idһ������ȷ��һ��service
	uint32_t original_id; ///< ����ȷ��һ��service
	uint32_t pos;         ///< serviceͷ������±�
} GxBusEpgEventCurUseService;


/*���epg��Ϣʱ�Ľṹ��*/
typedef struct {
	uint32_t ts_id;                          ///< ��service_idһ��ȷ��һ����Ŀ
	uint32_t service_id;                     ///< ��ts_idһ��ȷ��һ����Ŀ
	uint32_t reference_service_id;           ///< ��ts_idһ������ȷ��һ��service
	uint32_t original_id;                    ///< ����ȷ��һ��service
	uint32_t event_id;                       ///< ��service id ts id original_idһ��ȷ��һ��event
	uint32_t reference_event_id;             ///< service id ts id��event idΨһ��ȷ��һ��event
	GxBusEpgEventTime* event_time;           ///< ��event��ʱ��
	uint8_t* name;                           ///< ��event������
	uint32_t name_length;                    ///< name�ĳ���
	uint8_t* detaile_description;            ///< ��event������
	uint32_t detaile_length;                 ///< detaile_description�ĳ���
	GxBusEpgEventType type;                  ///< ��event�������ǵ�ǰ ���Ǻ��� ��������ϸ��Ϣ
	int8_t language[4];                      ///< ��event������
	GxBusEpgParentalRating* parental_rating; ///< �洢��ĸ����Ϣ�����û�и�ĸ����Ϣ����ΪNULL
	uint32_t parental_rating_num;            ///< ��ĸ����Ϣ�����������û�и�ĸ����Ϣ����Ϊ0
	GxBusEpgChannelEtt* channel_ett;         ///< �洢channel ett��Ϣ�����û��channel ett����ΪNULL
	uint32_t channel_ett_num;                ///< channel ett�����������û��channel ett����Ϊ0
	uint32_t ver;
}GxBusEpgEventAddInfo;

/* ���ڱȽ�����event�Ƿ���ͬһ��event������GX_BUS_EPG_OK:��ʾ����event��ͬ��GX_BUS_EPG_ERR:��ʾ
 * ����event����ͬ�����û��ע��ȽϺ�������ʹ��Ĭ�ϵıȽϷ�ʽ�������Ƚ�service id
 */
typedef struct {
	uint32_t ts_id;       ///< ��service_idһ��ȷ��һ����Ŀ
	uint32_t service_id;  ///< ��ts_idһ��ȷ��һ����Ŀ
	uint32_t original_id; ///< ����ȷ��һ��service
}GxBusEpgEventComp;

typedef status_t (*GxBusEpgCheckEvent)(GxBusEpgEventComp* src,GxBusEpgEventComp* cur);
typedef status_t (*GxBusEpgModifyEvent)(GxBusEpgEventAddInfo* event);

/* Exported Functions ----------------------------------------------------- */

/**
 * @brief ��ʼ��epg,ʹ��epgǰ�����ó�ʼ��
 *
 * @param uint32_t service_count:��Ҫ�����serviceͷ�ĸ���
 *        uint32_t event_count:��Ҫ������ܵ�event����
 *        uint32_t event_size:ÿ��event�Ĵ�С ���� event name��event describe
 *        uint32_t epg_day:��Ҫ�����epg������ һ����7��
 *
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_ERR:ִ��ʧ��
 *          GX_BUS_EPG_MEM_ERR:epg�����ڴ�ʧ��
 */
status_t GxBus_EpgInit(uint32_t service_count, uint32_t event_count, uint32_t event_size, uint32_t epg_day);

/**
 * @brief �ͷ�epg��ռ��Դ,����Ӳ����Դ
 *
 * @param void
 *
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_ERR:ִ��ʧ��
 */
status_t GxBus_EpgRelease(void);

/**
 * @brief �ͷ�epg�洢�ռ�,ʹ���д洢�ռ����,��ʼȫ�ٽ���
 *
 * @param void
 *
 * @return GX_BUS_EPG_OK:ִ������
 *         GX_BUS_EPG_ERR:ִ��ʧ��
 */
status_t GxBus_EpgClean(void);

/**
 * @brief ��ȡ��ǰ�Ѿ���ӵ�serviceͷ�����е�service
 *
 * @param GxBusEpgEventCurUseService** service:���ص�ָ��
 *        uint32_t* num:����,���Ϊ0����serviceͷ�����ǿյ�
 *
 * @return   GX_BUS_EPG_OK:ִ������
 *           GX_BUS_EPG_NOT_LOCK:epgû������
 *           GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������
 */
status_t GxBus_EpgCurUseServiceGet(GxBusEpgEventCurUseService** service,uint32_t* num);

/**
 * @brief ���ĳ��service,
 *
 * @param uint32_t ts_id,
 *        uint32_t service_id
 *        uint32_t original_id
 *        GxBusEpgServiceHead* service_head:����ͷ��Ϣ�Ŀռ�
 *
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������ȷ,�޷�ƥ�䵽��ȷֵ
 *          GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_EpgServiceGet(uint32_t ts_id,
		uint32_t service_id,
		uint32_t original_id,
		GxBusEpgServiceHead* service_head);

/**
 * @brief ���ĳ��event,
 *
 * @param uint32_t event_pos:event��pos
 *        GxBusEpgEventHead* event_head:����ͷ��Ϣ�Ŀռ�
 *
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������ȷ,�޷�ƥ�䵽��ȷֵ
 *          GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_EpgEventGet(uint32_t event_pos,GxBusEpgEventHead* event_head);

/**
 * @brief   ���һ��event,
 *
 * @param   GxBusEpgEventAddInfo* info:��ӵ���Ϣ
 *
 * @return  GX_BUS_EPG_OK            : ִ������
 *          GX_BUS_EPG_SERVICE_FULL  : serviceͷ��������
 *          GX_BUS_EPG_EVENT_FULL    : eventͷ�����Ѿ�����
 *          GX_BUS_EPG_MEM_POOL_FULL : �ڴ������
 *          GX_BUS_EPG_NOT_LOCK      : epgû������
 *          GX_BUS_EPG_PARAMETER_ERR : ����Ĳ�������
 *          GX_BUS_EPG_EVENT_EXIST   : �����event�Ѿ�����
 */
status_t GxBus_EpgInfoAdd(GxBusEpgEventAddInfo* info);

/**
 * @brief ����ָ����service����Чevent��Ϣ,���ts_id,service_id,original_id
 *        ��Ϊ 0xffffffff �Ļ������������service����Чevent
 *
 * @param    uint32_t ts_id:ȷ��һ��service
 *           uint32_t service_id:ȷ��һ��service
 *           uint32_t original_id:ȷ��һ��service
 *
 * @return   GX_BUS_EPG_OK:ִ������
 *           GX_BUS_EPG_NOT_LOCK:epgû������
 *           GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������
 **/
status_t GxBus_EpgInvalidInfoClean(uint32_t ts_id,uint32_t service_id, uint32_t original_id);

/**
 * @brief ����ָ����service��ȫ��event��Ϣ,�����ͷ�service
 *
 * @param  uint32_t ts_id:ȷ��һ��service
 *         uint32_t service_id:ȷ��һ��service
 *         uint32_t original_id:ȷ��һ��service
 *
 * @return GX_BUS_EPG_OK:ִ������
 *         GX_BUS_EPG_NOT_LOCK:epgû������
 *         GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������
 **/
status_t GxBus_EpgServiceClean(uint32_t ts_id,uint32_t service_id, uint32_t original_id);

/**
 * @brief �����뵱ǰ���ŵ�service��Զ��service��epg��Ϣ,�ú����ǵ�add����full
 *        ʱ,��������Լ�����͵��ô˺���,
 * @param void
 *
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_ERR:ִ��ʧ��
 *          GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_EpgFarServiceClean(void);

/**
 * @brief ���ĳ��nvod ��event, ���ڻ�ȡnvod������
 * @param uint32_t reference_service_id:���ڶԱȵ� reference_service_id
 *        uint32_t reference_event_id:���ڶԱȵ� reference_event_id
 *	  GxBusEpgEventHead* event_head:����ͷ��Ϣ�Ŀռ�
 *
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������ȷ,�޷�ƥ�䵽��ȷֵ
 *          GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_NvodInfoGet(uint32_t ts_id,uint32_t reference_service_id,
		uint32_t reference_event_id,
		GxBusEpgEventHead* event);
/**
 * @brief  ע��event�Ƿ���ͬ�ıȽϺ�����û��ע����ʹ��Ĭ�ϵıȽϷ�ʽ�������Ƚ�service id
 * @param
 * @return GX_BUS_EPG_OK:ִ������
 *         GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������
 *         GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_RegisterCompFunc(GxBusEpgCheckEvent fun);
/**
 * @brief   ע��event�Ƿ���ͬ�ıȽϺ������Ӵ��Ժ�ʹ��Ĭ�ϵıȽϷ�ʽ�������Ƚ�service id
 * @param
 * @return  GX_BUS_EPG_OK:ִ������
 *          GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_UnregisterCompFunc(void);

/**
 * @brief     �޸�һ��event�����ݣ�����name��descriptor
 * @param     uint32_t event_pos:���ڶ�λ�޸�����event
 *            GxBusEpgEventAddInfo* info:�µ�event��Ϣ
 * @return    GX_BUS_EPG_OK:ִ������
 *            GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������ȷ,�޷�ƥ�䵽��ȷֵ
 *            GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_EpgEventModify(uint32_t event_pos,GxBusEpgEventAddInfo* info);

/**
 * @brief    ע���޸�event�Ļص��������ڱ���eventǰ����Ӷ
 * @param
 * @return   GX_BUS_EPG_OK:ִ������
 *           GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������ȷ,�޷�ƥ�䵽��ȷֵ
 *           GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_RegisterModifyEventCb(GxBusEpgModifyEvent fun);
/**
 * @brief    ע���޸�event�Ļص�����
 * @param
 * @return   GX_BUS_EPG_OK:ִ������
 *           GX_BUS_EPG_PARAMETER_ERR:����Ĳ�������ȷ,�޷�ƥ�䵽��ȷֵ
 *           GX_BUS_EPG_NOT_LOCK:epgû������
 */
status_t GxBus_UnregisterModifyEventCb(void);

__END_DECLS

#endif

/*@}*/

