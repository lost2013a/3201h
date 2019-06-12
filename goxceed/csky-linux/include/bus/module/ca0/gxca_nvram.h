/*@{*/
#ifndef __GXCA_NVRAM_H__
#define __GXCA_NVRAM_H__

#include <gxtype.h>
#include "gxcore.h"

__BEGIN_DECLS


/**定义NVRAM文件名最大长度*/
#define     GXCA_MAX_NVRAM_FILE_NAME         (128)

/**
 * @brief       NVRAM初始化
 * @param [in]  size     NVRAM大小
 * @return      void
 * @see
 */
void GxCA_NvramInit(size_t size);
/**
 * @brief       NVRAM读接口
 * @param [in]   Offset       偏移地址
 * @param [in]   Buf          缓冲地址
 * @param [in]   BufSize      缓冲大小
 * @return      size_t        实际读数据大小
 * @see ::GxCA_NvramInit ::GxCA_NvramWrite ::GXCA_NvramClean
 */
size_t GxCA_NvramRead(uint32_t Offset, uint8_t *Buf, size_t BufSize);
/**
 * @brief       NVRAM写接口
 * @param [in]  Offset        偏移地址
 * @param [in]  Data          写数据指针
 * @param [in]  DataSize      数据大小
 * @return      size_t        实际与入数据大小
 * @see
 */
size_t GxCA_NvramWrite(uint32_t Offset, const uint8_t *Data, size_t DataSize);
/**
 * @brief       NVRAM清除接口
 * @param [in]  Offset        偏移地址
 * @param [in]  Len           清除块大小
 * @return      void
 * @see
 */
void GXCA_NvramClean(uint32_t Offset, size_t Len);

/**
 * @brief       NVRAM信息获取接口
 * @param [in]  StartOffset   NVRAM起始地址
 * @param [in]  Len           NVRAM总大小
 * @return      void
 * @see
 */
void GxCA_NvramGet(uint32_t *StartOffset, size_t *Len );
/**
 * @brief       NVRAM获取STB ID
 * @param       无
 * @return      uint32_t 4字节STB ID
 * @see
 */
uint32_t GxCA_NvramGetSTBID(void);

__END_DECLS

#endif
/*@}*/
