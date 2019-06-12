/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DMX_SUB_SYSTEM_H__
#define __DMX_SUB_SYSTEM_H__

#include "gxcore.h"

__BEGIN_DECLS

/*����ֵ*/
#define GX_DMX_SUB_PARAMETER_ERR (-1)
#define GX_DMX_SUB_ERR           (-2)
#define GX_DMX_SUB_SUCCESS       (0)

/* Exported Types --------------------------------------------------------- */

#if 0
#define DMX_SUB_SLOT_NUM   (64)//slot��֧������
#define DMX_SUB_FILTER_NUM   (64)//filter��֧������
#define DMX_SUB_NUM       (2)//dmx��֧������
#else
uint32_t DMX_SUB_FILTER_NUM;
uint32_t DMX_SUB_SLOT_NUM;
uint32_t DMX_SUB_NUM;
#endif
#define DMX_SUB_MAX_NAME       (8)//dmx�����ֳ���

#define SUBSYSTEM_DMX_EQ_MATCH    (1)
#define SUBSYSTEM_DMX_NEQ_MATCH   (0)
#define SUBSYSTEM_DMX_CRC_ON      (0)
#define SUBSYSTEM_DMX_CRC_OFF     (0x1234)
#define SUBSYSTEM_DMX_SOFT_OFF      (0)
#define SUBSYSTEM_DMX_SOFT_ON     (0x1234)

typedef enum
{
    GX_SUB_DMX_FILTER_TYPE_PSI,
    GX_SUB_DMX_FILTER_TYPE_PES,
}GxSubsystemDmxFilterType;

typedef struct
{
    GxSubsystemDmxFilterType  type;
    uint16_t   pid;         ///< pid ��ֵ
    uint8_t    match_depth;     ///< ƥ�����
    uint8_t    eq_or_neq;       ///< ƥ�������д��SUBSYSTEM_DMX_EQ_MATCH  ����ƥ����д��SUBSYSTEM_DMX_NEQ_MATCH
    uint32_t   crc;        ///< ����ʱ�Ƿ�ʱ��crcУ��,SUBSYSTEM_DMX_CRC_ON ,SUBSYSTEM_DMX_CRC_OFF 
    uint32_t   soft_filter;///< ����ʱ�Ƿ�ʹ���������ƥ��,SUBSYSTEM_DMX_SOFT_OFF,SUBSYSTEM_DMXSOFT_ON

    uint8_t    match[18];       ///< ƥ��ֵ
    uint8_t    mask[18];        ///< ƥ��ֵ�����룬��ӦλΪ1����ƥ������㹻���Ż�///��ƥ��ֵ������
	uint32_t sw_buffer_size;//filter fifo�Ĵ�С С��64K ʹ������Ĭ������
} GxSubsystemDmxAllocFilter;


typedef  int32_t dmx_handle_t;
typedef  int32_t filter_handle_t;

/* Exported Functions ----------------------------------------------------- */

/**
 * @brief      ��ʼ��dmx��ϵͳ
 * 
 * @param     
 *           
 * 
 * @return     GX_DMX_SUB_ERR:ִ�д���
 *             GX_DMX_SUB_SUCCESS��ִ�гɹ�  
 */
int32_t GxSubSystem_DmxInit(void);

/**
 * @brief      ��dmx��ϵͳ����ȡ���ƾ��
 * 
 * @param       uint32_t dmx_id:dmx��id�������ǵ�ϵͳ������·dmx��idΪ0������1
 *              uint32_t ts����dmx�󶨵�ts��ţ���0��ʼ
 * 
 * @return      dmx��ϵͳ�Ŀ��ƿ�,�����-1��ʾ��ʧ��
 */
dmx_handle_t GxSubSystem_DmxOpen(uint32_t dmx_id,uint32_t ts);


/**
 * @brief      ��ȡdmx��ϵͳ�е�device���
 * 
 * @param       dmx_handle_t dmx:dmx��ϵͳ�ľ��
 * 
 * @return      dmx��ϵͳ����Ӧ��device��� -1�������˴���
 */
handle_t  GxSubSystem_DmxGetDevice(dmx_handle_t dmx);

/**
 * @brief      ��ȡdmx��ϵͳ�е�module���
 * 
 * @param       dmx_handle_t dmx:dmx��ϵͳ�ľ��
 * 
 * @return      dmx��ϵͳ����Ӧ��module��� -1�������˴���
 */
handle_t  GxSubSystem_DmxGetModule(dmx_handle_t dmx);

/**
 * @brief      ��ѯts�Ƿ�����
 * 
 * @param       dmx_handle_t dmx:dmx��ϵͳ�ľ��
 * 
 * @return      1��ts����
 *              0��tsû������
 *              -1�����д���
 */
int32_t GxSubSystem_DmxQueryStatus(dmx_handle_t dmx);

/**
 * @brief      �رմ򿪵�dmx��ϵͳ
 * 
 * @param       dmx_handle_t dmx:dmx��ϵͳ�ľ��
 * 
 * @return     GX_DMX_SUB_ERR:ִ�д���
 *             GX_DMX_SUB_SUCCESS��ִ�гɹ�  
 */
int32_t  GxSubSystem_DmxClose(dmx_handle_t dmx);

/**
 * @brief      �������
 * 
 * @param       dmx_handle_t dmx:dmx��ϵͳ�ľ��
 *              GxSubsystemDmxAllocFilter* para�����˲���
 * 
 * @return     -1:ִ�д���
 *              ����ֵ�����˵Ŀ��ƾ��
 *             
 */
filter_handle_t GxSubSystem_DmxFilterAlloc(dmx_handle_t dmx, GxSubsystemDmxAllocFilter* para);

/**
 * @brief      ��ʼ����
 * 
 * @param      filt_handle_t filter:filter�ľ��
 * 
 * @return     GX_DMX_SUB_ERR: ִ�д���
 *             GX_DMX_SUB_PARAMETER_ERR����������
 *             GX_DMX_SUB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubSystem_DmxFilterStart(filter_handle_t filter);

/**
 * @brief      ֹͣ����
 * 
 * @param      filt_handle_t filter:filter�ľ��
 * 
 * @return     GX_DMX_SUB_ERR: ִ�д���
 *             GX_DMX_SUB_PARAMETER_ERR����������
 *             GX_DMX_SUB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubSystem_DmxFilterStop(filter_handle_t filter);

/**
 * @brief      �ͷŹ���
 * 
 * @param      filt_handle_t filter:filter�ľ��
 * 
 * @return     GX_DMX_SUB_ERR: ִ�д���
 *             GX_DMX_SUB_PARAMETER_ERR����������
 *             GX_DMX_SUB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubSystem_DmxFilterRelease(filter_handle_t filter);

/**
 * @brief      �ȴ���������,����ȷ������filter��ýӿ��ڵȴ������л������߳���
 * ��
 * 
 * @param       dmx_handle_t dmx:dmx��ϵͳ�ľ�� 
 *              filt_handle_t* filter:���������ݵ�filter�ľ�����ռ���Ӧ�ÿ���
 *              Ϊ�˰�ȫ,�ռ��С��õ���
 *              sizeof(filter_handle_t)*SI_DMX_SUB_FILTER_NUM
 * 
 * @return     0: û���κ�filter���˵�����
 *              1~64�������ݵ�filter����
 *              GX_DMX_SUB_ERR: ִ�д���
 */
int32_t  GxSubSystem_DmxFilterWait(dmx_handle_t dmx,filter_handle_t* filter);

/**
 * @brief      ��ȡ���˵������ݣ���������n��section����
 * 
 * @param      filt_handle_t filter:filter�ľ��
 *              data_out:��Ŷ�ȡ�������ݵ�buf
 *              buf_size��data_out�Ĵ�С
 * 
 * @return     ʵ�ʶ�ȡ��������
 *             GX_DMX_SUB_ERR: ִ�д���
 */
int32_t  GxSubSystem_DmxFilterRead(filter_handle_t filter,uint8_t* data_out, uint32_t buf_size);


/**
 * @brief      ��ȡDMX SLOT FILTER������
 * 
 * @param     dmx,slot,filter:��������ʵ��Ӳ�������ı�����ַ
 *          
 * 
 * @return     
 */
void GxSubsystem_DmxGetHardwareNum(uint32_t * dmx,uint32_t * channel_num);

/**
 * @brief      �ı���� ������֮ǰ������stop
 * 
 * @param      filt_handle_t filter:filter�ľ��
 *              GxSubsystemDmxAllocFilter* para�����˲���
 * 
 * @return     GX_DMX_SUB_ERR: ִ�д���
 *             GX_DMX_SUB_PARAMETER_ERR����������
 *             GX_DMX_SUB_SUCCESS��ִ�гɹ�
 *             
 */
int32_t GxSubSystem_DmxFilterModify(filter_handle_t filter, GxSubsystemDmxAllocFilter* para);
__END_DECLS

#endif
/*@}*/

