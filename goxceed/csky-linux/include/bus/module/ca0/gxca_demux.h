/**
 * @file gxca_demux.h
 * @author lixb
 * @brief CASϵͳDEMUX�ӿڳ���ģ��
 * @defgroup ca_module CA Module
 */
 /*@{*/
#ifndef __GX_CA_DEMUX_H__
#define __GX_CA_DEMUX_H__

#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

/**����Ӳ��֧�ֵ�DEMUX����*/
#define GXCA_MAX_DEMUX_SUPPORT                  (2)

#define GXCA_DEMUX_DEFAULT_CHANNEL_NUM          (8)
#define GXCA_DEMUX_DEFAULT_FILTER_NUM           (8)

/**FILTER״̬*/
typedef enum {
	GXCA_TIMEOUT,               /**<FILTER��ʱ*/
	GXCA_RECEIVED_SECTION       /**<FILTER�յ�һ��SECTION*/
}GxCA_FilterStatus;

/**
 * @brief FILTER֪ͨ����
 * @param [in] Filter          Filter���
 * @param [in] Section         SECTIONָ��
 * @param [in] Size            Section��С
 * @return void
 * @remark     Filter֪ͨ�����ǲ��ûص�����ʽʵ�ֵ�.��һ��Filter���˵�����ʱ
 * ������ñ�����֪ͨ���filter�Ѿ����˵�����,��ʱChannel�ǹ��˵�
 * ���ݵ�Filter����Channel�ľ��,Filter�Ǳ�Filter�ľ��,Status��
 * GXCA_RECEIVED_SECTION,Section�ǹ��˵���Section����.
 * ����Filter��ʱʱ,Status��ֵΪGXCA_TIMEOUT,Section����NULL,
 * ����ֵ����������˵�����ʱ��������ͬ.
 * FilterNotify��SectionNotify������������,FilterNotify�����ÿһ��
 * Filter��,��ÿһ��Fitler����һ��FilterNotify.��SectionNotify��
 * ������й�������,���еĹ�����������һ��֪ͨ����SectionNotify
 * ���FilterNotify�������ʽ�������GxCA_DemuxChannelAllocate,
 * GxCA_DemuxFilterAllocate�������
 * * @see ::GxCA_DemuxChannelAllocate ::GxCA_DemuxChannelFree ::GxCA_DemuxChannelSetPID
 * ::GxCA_DemuxChannelEnable ::GxCA_DemuxChannelDisable ::GxCA_CaDemuxChannelReset
 * ::GxCA_DemuxFilterAllocate ::GxCA_DemuxFilterFree ::GxCA_CaDemuxFilterSetup
 * ::GxCA_DemuxFilterEnable ::GxCA_DemuxFilterDisable ::GxCA_DemuxFilterRegisterNotify
 */
typedef void ((*FilterNotify)(handle_t Filter, const uint8_t* Section, size_t Size));
/**
 * @brief FILTER��ʱ֪ͨ����
 * @param [in] Filter          Filter���
 * @return void
 * @remark     ��һ��ca��ĳ��filter��ʱʱ����Ҫ֪ͨca�����˹��˳�ʱ��ʹ��
 * �ص���ʽʵ��
 */
typedef void ((*FilterTimeOut)(handle_t Filter));
/**
 * @brief       ��ʼ��Demux
 * @param [in]  Prior               �߳����ȼ�
 * @param [in]  TotalChannelNum     �ܹ���Ҫʹ�ö���Channel����
 * @param [in]  TotalFitlerNum      �ܹ���Ҫʹ�ö���filter����
 * @return      void                ��
 * @see ::GxCA_DemuxChannelFree ::GxCA_DemuxChannelSetPID
 */
void GxCA_DemuxInit(uint8_t Prior, uint32_t TotalChannelNum, uint32_t TotalFitlerNum);
void GxCA_DemuxDestroy(void);
void GxCA_DemuxDisable(void);
void GxCA_DemuxEnable(void);
/**
 * @brief       ����һ��Channel
 * @param [in]  DemuxID    ʹ�õ�Demux�豸��
 * @return      handle_t   ����ɹ�,����Channel���,ʧ�ܷ���
 GXCORE_INVALID_POINTER
 * @see ::GxCA_DemuxChannelFree ::GxCA_DemuxChannelSetPID
 */
handle_t GxCA_DemuxChannelAllocate(uint32_t DemuxID, int16_t PID, bool repeatFlag);
/**
 * @brief       �ͷ�һ��Channel
 * @param [in]  Channel    �ͷŵ�Channel���
 * @return      bool       �ͷųɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxChannelAllocate ::GxCA_DemuxChannelSetPID
 */
bool GxCA_DemuxChannelFree(handle_t Channel);
/**
 * @brief       ����Channel��PID
 * @param [in]  Channel    Channel���
 * @param [in]  PID        PID
 * @return      bool       ���óɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxChannelAllocate  ::GxCA_DemuxChannelFree
 */
bool GxCA_DemuxChannelSetPID(handle_t Channel, uint16_t PID, bool repeatFlag);

/**
 * @brief       ����Channel
 * @param [in]  Channel    Channel���
 * @return      bool       �����ɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxChannelDisable
 */
bool GxCA_DemuxChannelEnable(handle_t Channel);
/**
 * @brief       ֹͣChannel
 * @param [in]  Channel    Channel���
 * @return      bool       ֹͣ�ɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxChannelEnable
 */
bool GxCA_DemuxChannelDisable(handle_t Channel);
/**
 * @brief       ��λChannel
 * @param [in]  Channel    Channel���
 * @return      bool       ��λ�ɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see
 */
bool GxCA_DemuxChannelReset(handle_t Channel);
/**
 * @brief       ͨ��PID��ȡChannel���
 * @param [in]  pid         MPEG2TS PID
 * @return      handle_t    ���ػ�ȡ��������
 * @see
 */
handle_t GxCA_DemuxChannelGetByPid(uint16_t pid);

/**
 * @brief       ����FILTER
 * @param [in]  Channel    Channel���
 * @param [in]  ID         ��ʶFilter����ֵ
 * @return      handle_t   ����ɹ�,����FILTER���,ʧ�ܷ���GXCORE_INVALID_POINTER
 * @see
 */
handle_t GxCA_DemuxFilterAllocate(handle_t Channel, uint8_t ID);
/**
 * @brief       ͨ����ʶFilter����ֵID�ҵ�filter���
 * @param [in]  Channel     Channel���
 * @param [in]  ID          ��ʶFilter����ֵID
 * @return      handle_t    ���ҳɹ�,����FILTER���,ʧ�ܷ���GXCORE_INVALID_POINTER
 * @see
 */
handle_t GxCA_DemuxFilterGetByID(handle_t Channel, uint8_t ID);
/**
 * @brief       ͨ��filter����ҵ�PID
 * @param [in]  Filter      Filter���
 * @param [in]  uint16_t    PID
 * @return      handle_t    ���ҳɹ�,����PID,ʧ�ܷ���0xFFFF
 * @see
 */
uint16_t GxCA_DemuxFilterGetPID(handle_t Filter);
/**
 * @brief       �ͷ�FILTER
 * @param [in]  Filter   Filter���
 * @return      bool     �ͷųɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see
 */
uint8_t GxCA_DemuxFilteGetID(handle_t Filter);


bool GxCA_DemuxFilterFree(handle_t Filter);
/**
 * @brief       ����FILTER
 * @param [in]  Filter   Filter���
 * @param [in]  Match    ƥ����������ָ��
 * @param [in]  Mask     ƥ����������
 * @param [in]  Equal    �Ƿ񲻵ȹ���
 * @param [in]  Depth    �������
 * @param [in]  Timeout  ��ʱʱ��  ��λ��ms
 * @return      bool     ���óɹ�,����TRUE,ʧ�ܷ���FALSE
 * @see
 */
bool GxCA_DemuxFilterSetup(handle_t Filter,
		const uint8_t*  Match,
		const uint8_t*  Mask,
		bool            Equal,
		bool            CRCFlag,
		size_t          Depth,
		int32_t         Timeout);

/**
 * @brief       ע��ص�����
 * @param [in]  Filter           Filter���
 * @param [in]  Callback         �ش��������ݻص�����
 * @param [in]  TimeOutCallback  ��ʱ�ص������ص�����
 * @return      bool             �����ɹ�����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxFilterDisable ::GxCA_CaDemuxFilterSetup
 */
bool GxCA_DemuxFilterRigsterNotify(handle_t Filter, FilterNotify Callback, FilterTimeOut TimeOutCallback);

/**
 * @brief       ����FILTER
 * @param [in]  Filter         Filter���
 * @return      bool           �����ɹ�����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxFilterDisable ::GxCA_CaDemuxFilterSetup
 */
bool GxCA_DemuxFilterEnable(handle_t Filter);
/**
 * @brief       ֹͣFILTER
 * @param [in]  Filter         Filter���
 * @return      bool           ֹͣ�ɹ�����TRUE,ʧ�ܷ���FALSE
 * @see ::GxCA_DemuxFilterEnable
 */
bool GxCA_DemuxFilterDisable(handle_t Filter);
/**
 * @brief       ��λFILTER
 * @param [in]  Filter         Filter���
 * @return      bool           ��λ�ɹ�����TRUE,ʧ�ܷ���FALSE
 * @see
 */
bool GxCA_DemuxFilterReset(handle_t Filter);

__END_DECLS

#endif
/*@}*/
