/*@{*/
#ifndef __GXCA_NVRAM_H__
#define __GXCA_NVRAM_H__

#include <gxtype.h>
#include "gxcore.h"

__BEGIN_DECLS


/**����NVRAM�ļ�����󳤶�*/
#define     GXCA_MAX_NVRAM_FILE_NAME         (128)

/**
 * @brief       NVRAM��ʼ��
 * @param [in]  size     NVRAM��С
 * @return      void
 * @see
 */
void GxCA_NvramInit(size_t size);
/**
 * @brief       NVRAM���ӿ�
 * @param [in]   Offset       ƫ�Ƶ�ַ
 * @param [in]   Buf          �����ַ
 * @param [in]   BufSize      �����С
 * @return      size_t        ʵ�ʶ����ݴ�С
 * @see ::GxCA_NvramInit ::GxCA_NvramWrite ::GXCA_NvramClean
 */
size_t GxCA_NvramRead(uint32_t Offset, uint8_t *Buf, size_t BufSize);
/**
 * @brief       NVRAMд�ӿ�
 * @param [in]  Offset        ƫ�Ƶ�ַ
 * @param [in]  Data          д����ָ��
 * @param [in]  DataSize      ���ݴ�С
 * @return      size_t        ʵ���������ݴ�С
 * @see
 */
size_t GxCA_NvramWrite(uint32_t Offset, const uint8_t *Data, size_t DataSize);
/**
 * @brief       NVRAM����ӿ�
 * @param [in]  Offset        ƫ�Ƶ�ַ
 * @param [in]  Len           ������С
 * @return      void
 * @see
 */
void GXCA_NvramClean(uint32_t Offset, size_t Len);

/**
 * @brief       NVRAM��Ϣ��ȡ�ӿ�
 * @param [in]  StartOffset   NVRAM��ʼ��ַ
 * @param [in]  Len           NVRAM�ܴ�С
 * @return      void
 * @see
 */
void GxCA_NvramGet(uint32_t *StartOffset, size_t *Len );
/**
 * @brief       NVRAM��ȡSTB ID
 * @param       ��
 * @return      uint32_t 4�ֽ�STB ID
 * @see
 */
uint32_t GxCA_NvramGetSTBID(void);

__END_DECLS

#endif
/*@}*/
