/** @addtogroup si_module*/
/*@{*/
/* Define to prevent recursive inclusion */
#ifndef __SI_FILTER_H__
#define __SI_FILTER_H__

#include <gxtype.h>
#include <stdint.h>
#include <ctype.h>
#include "gxcore.h"

__BEGIN_DECLS

#define EQ_MATCH    (1)
#define NEQ_MATCH   (0)
#define CRC_ON      (0)
#define CRC_OFF     (0x1234)
#define SOFT_OFF    (0)
#define SOFT_ON     (0x1234)

/**
 *SiFilter info
 */
typedef struct {
	uint16_t   pid;         ///< pid ��ֵ
	uint8_t    match_depth; ///< ƥ�����
	uint8_t    eq_or_neq;   ///< ƥ�������д��EQ_MATCH  ����ƥ����д��NEQ_MATCH

	uint32_t   crc;         ///< ����ʱ�Ƿ�ʱ��crcУ��,CRC_ON ,CRC_OFF
	uint32_t   soft_filter; ///< ����ʱ�Ƿ�ʹ���������ƥ��,SOFT_OFF,SOFT_ON

	uint8_t    match[18];   ///< ƥ��ֵ
	uint8_t    mask[18];    ///< ƥ��ֵ�����룬��ӦλΪ1����ƥ������㹻���Żᰴƥ��ֵ������
	uint32_t   sw_buffer_size; ///fileter fifo��С�����С��64k��ʹ������Ĭ������
	uint32_t   hw_buffer_size; ///<
}GxSiFilter;

typedef enum {
	SI_TS_UNLOCK,
	SI_TS_LOCK,
}GxSiQueryStatus;

/**
 * @brief ����demux_id��demux�豸
 * @param demux_id   demux id ��ֵ��0 ��һ·demux�� 1 �ڶ�·demux...
 * @Return GXCORE_SUCCESS  demux�򿪳ɹ�
 *		   GXCORE_ERROR  demux��ʧ��
 */
status_t GxBus_SiFilterOpenAv(void);

/**
 * @brief ����demux_id�ر�demux�豸
 * @param demux_id   demux id��ֵ
 * @Return GXCORE_SUCCESS��demux�رճɹ�
 *		  GXCORE_ERROR��demux�ر�ʧ��
 */
status_t GxBus_SiFilterCloseAv(void);

/**
 * @brief ����si_filter����Ϣ������һ·si filter�����õ�si_filter_id
 * @param demux_id  ������SiFilter�������ĸ�Ӳ��demux��
 * @param si_filter[IN]   si_filter��������Ϣ
 * @Return SiFilter��IDֵ
 */
int16_t GxBus_SiFilterCreate (uint16_t ts_src, uint16_t demux_id, GxSiFilter *si_filter);

/**
 * @brief ����si_filter_id����һ·si_filter
 * @param si_filter_id   ����ʱ�õ���si_filter id
 * @Return GXCORE_SUCCESS   ����si filter�ɹ�
 GXCORE_ERROR  ����si filterʧ��
 */
status_t GxBus_SiFilterDestroy (uint16_t demux_id, int16_t si_filter_id);

/**
 * @brief ����si_filter _id����һ·si filter
 * @param si_filter_id  ����si filterʱ�õ���si filter id
 * @Return GXCORE_SUCCESS   ����si filter�ɹ�
 GXCORE_ERROR  ����si filterʧ��
 */
status_t GxBus_SiFilterStart (uint16_t demux_id, int16_t si_filter_id);

/**
 * @brief ����si_filter_idֹͣһ·si filter������λdmx_filter���ܣ���fifo reset
 * @param si_filter_id   ����ʱ�õ���si filter id
 * @Return GXCORE_SUCCESS   ֹͣsi filter�ɹ�
 GXCORE_ERROR  ֹͣsi filterʧ��
 */
status_t GxBus_SiFilterStop (uint16_t demux_id, int16_t si_filter_id);

/**
 * @brief ����si_filter_id�޸�si filter
 * @param si_filter_id   ����ʱ�õ���si filter id
 * @param si_filter[IN]  si filter ��������Ϣ
 * @Return GXCORE_SUCCESS   �޸�si filter�ɹ�
 GXCORE_ERROR  �޸�si filterʧ��
 */
status_t GxBus_SiFilterModify (uint16_t demux_id, int16_t si_filter_id, GxSiFilter *si_filter);

/**
 * @brief ��ѯ��һ·si filter�й��˵�����
 * @param si_filter_status[OUT]: һ��32λ������һλ��λ���ʹ����λ�������si_filter�й��˵����ݡ�
 * @Return GXCORE_SUCCESS  ��ѯsi filter״̬�ɹ�
 GXCORE_ERROR  ��ѯsi filter״̬ʧ��
 */
status_t GxBus_SiFilterQuery (uint16_t demux_id, uint64_t *si_filter_status);

/**
 * @brief ����si_filter_id���ĳ·si_filter������
 * @param si_filter_id   ����ʱ�õ���si filter id
 * @param data_buf   �洢si filter�����ݵ�buffer��ַ
 * @param data_len   �洢si filter�����ݵ�buffer��С
 * @Return size_t   ʵ�ʶ����Ĵ�С��Ϊ������section
 */
size_t GxBus_SiFilterRead(uint16_t demux_id, int16_t si_filter_id,	uint8_t  *data_buf, size_t  data_len);


/**
 * @brief ����si_filter_id��ȡsi filter
 * @param si_filter_id   ����ʱ�õ���si filter id
 * @Return GxSiFilter* si filter�ṹ��ָ��
 */
const GxSiFilter* GxBus_SiFilterGet(int16_t si_filter_id);

/**
 * @brief ����demux id���жϵ�ǰdemux�豸��ts���Ƿ�����
 * @param demux_id   demux id ��ֵ��0 ��һ·demux�� 1 �ڶ�·demux...
 * @Return SI_TS_UNLOCK  tsδ����
 *         SI_TS_LOCK   ts����
 */
GxSiQueryStatus GxBus_SiTsLockQuery (uint32_t demux_id);

/**
 * @brief ����si����filter���ź���
 * @param  * @Return
 */
void GxBus_SiFilterSemInit(void);

/**
 * @brief ��ȡDMX��FILTER��������ʼ��DMX��FILTER���ƿ�
 * @param
 * @Return 0       ��ʼ���ɹ�
 *         С��0   ��ʼ��ʧ��
 */
int32_t GxBus_SiDmxInit();

/**
 * @brief �������ù����õ�filter����Ҫ�����ź���
 * @param  * @Return
 */
void GxBus_SiFilterSemPost(void);

/**
 * @brief �ȴ�filter�������ź���
 * @param  * @Return
 */
void GxBus_SiFilterSemWait(void);

/**
 * @brief ɾ��filter�ź���
 * @param  * @Return
 */
void GxBus_SiFilterSemDel(void);

__END_DECLS

#endif /*__SI_FILTER_H__ */
/*@}*/

