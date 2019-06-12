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
	uint16_t   pid;         ///< pid 的值
	uint8_t    match_depth; ///< 匹配深度
	uint8_t    eq_or_neq;   ///< 匹配过滤填写宏EQ_MATCH  不等匹配填写宏NEQ_MATCH

	uint32_t   crc;         ///< 过滤时是否时能crc校验,CRC_ON ,CRC_OFF
	uint32_t   soft_filter; ///< 过滤时是否使用软件进行匹配,SOFT_OFF,SOFT_ON

	uint8_t    match[18];   ///< 匹配值
	uint8_t    mask[18];    ///< 匹配值的掩码，对应位为1并且匹配深度足够，才会按匹配值来过滤
	uint32_t   sw_buffer_size; ///fileter fifo大小，如果小于64k则使用驱动默认配置
	uint32_t   hw_buffer_size; ///<
}GxSiFilter;

typedef enum {
	SI_TS_UNLOCK,
	SI_TS_LOCK,
}GxSiQueryStatus;

/**
 * @brief 根据demux_id打开demux设备
 * @param demux_id   demux id 的值，0 第一路demux， 1 第二路demux...
 * @Return GXCORE_SUCCESS  demux打开成功
 *		   GXCORE_ERROR  demux打开失败
 */
status_t GxBus_SiFilterOpenAv(void);

/**
 * @brief 根据demux_id关闭demux设备
 * @param demux_id   demux id的值
 * @Return GXCORE_SUCCESS：demux关闭成功
 *		  GXCORE_ERROR：demux关闭失败
 */
status_t GxBus_SiFilterCloseAv(void);

/**
 * @brief 根据si_filter的信息，创建一路si filter，并得到si_filter_id
 * @param demux_id  创建的SiFilter挂载在哪个硬件demux下
 * @param si_filter[IN]   si_filter的配置信息
 * @Return SiFilter的ID值
 */
int16_t GxBus_SiFilterCreate (uint16_t ts_src, uint16_t demux_id, GxSiFilter *si_filter);

/**
 * @brief 根据si_filter_id销毁一路si_filter
 * @param si_filter_id   创建时得到的si_filter id
 * @Return GXCORE_SUCCESS   销毁si filter成功
 GXCORE_ERROR  销毁si filter失败
 */
status_t GxBus_SiFilterDestroy (uint16_t demux_id, int16_t si_filter_id);

/**
 * @brief 根据si_filter _id启动一路si filter
 * @param si_filter_id  创建si filter时得到的si filter id
 * @Return GXCORE_SUCCESS   启动si filter成功
 GXCORE_ERROR  启动si filter失败
 */
status_t GxBus_SiFilterStart (uint16_t demux_id, int16_t si_filter_id);

/**
 * @brief 根据si_filter_id停止一路si filter，带复位dmx_filter功能，即fifo reset
 * @param si_filter_id   创建时得到的si filter id
 * @Return GXCORE_SUCCESS   停止si filter成功
 GXCORE_ERROR  停止si filter失败
 */
status_t GxBus_SiFilterStop (uint16_t demux_id, int16_t si_filter_id);

/**
 * @brief 根据si_filter_id修改si filter
 * @param si_filter_id   创建时得到的si filter id
 * @param si_filter[IN]  si filter 的配置信息
 * @Return GXCORE_SUCCESS   修改si filter成功
 GXCORE_ERROR  修改si filter失败
 */
status_t GxBus_SiFilterModify (uint16_t demux_id, int16_t si_filter_id, GxSiFilter *si_filter);

/**
 * @brief 查询哪一路si filter有过滤到数据
 * @param si_filter_status[OUT]: 一共32位，任意一位置位，就代表该位所代表的si_filter有过滤到数据。
 * @Return GXCORE_SUCCESS  查询si filter状态成功
 GXCORE_ERROR  查询si filter状态失败
 */
status_t GxBus_SiFilterQuery (uint16_t demux_id, uint64_t *si_filter_status);

/**
 * @brief 根据si_filter_id获得某路si_filter的数据
 * @param si_filter_id   创建时得到的si filter id
 * @param data_buf   存储si filter中数据的buffer地址
 * @param data_len   存储si filter中数据的buffer大小
 * @Return size_t   实际读到的大小，为整数个section
 */
size_t GxBus_SiFilterRead(uint16_t demux_id, int16_t si_filter_id,	uint8_t  *data_buf, size_t  data_len);


/**
 * @brief 根据si_filter_id获取si filter
 * @param si_filter_id   创建时得到的si filter id
 * @Return GxSiFilter* si filter结构体指针
 */
const GxSiFilter* GxBus_SiFilterGet(int16_t si_filter_id);

/**
 * @brief 根据demux id来判断当前demux设备的ts流是否锁定
 * @param demux_id   demux id 的值，0 第一路demux， 1 第二路demux...
 * @Return SI_TS_UNLOCK  ts未锁定
 *         SI_TS_LOCK   ts锁定
 */
GxSiQueryStatus GxBus_SiTsLockQuery (uint32_t demux_id);

/**
 * @brief 建立si管理filter的信号量
 * @param  * @Return
 */
void GxBus_SiFilterSemInit(void);

/**
 * @brief 获取DMX和FILTER数量并初始化DMX和FILTER控制块
 * @param
 * @Return 0       初始化成功
 *         小于0   初始化失败
 */
int32_t GxBus_SiDmxInit();

/**
 * @brief 当建立好过滤用的filter是需要发送信号量
 * @param  * @Return
 */
void GxBus_SiFilterSemPost(void);

/**
 * @brief 等待filter建立的信号量
 * @param  * @Return
 */
void GxBus_SiFilterSemWait(void);

/**
 * @brief 删除filter信号量
 * @param  * @Return
 */
void GxBus_SiFilterSemDel(void);

__END_DECLS

#endif /*__SI_FILTER_H__ */
/*@}*/

