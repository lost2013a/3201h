/**
 * @file gxca_demux.h
 * @author lixb
 * @brief CAS系统DEMUX接口抽象模块
 * @defgroup ca_module CA Module
 */
 /*@{*/
#ifndef __GX_CA_DEMUX_H__
#define __GX_CA_DEMUX_H__

#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

/**定义硬件支持的DEMUX数量*/
#define GXCA_MAX_DEMUX_SUPPORT                  (2)

#define GXCA_DEMUX_DEFAULT_CHANNEL_NUM          (8)
#define GXCA_DEMUX_DEFAULT_FILTER_NUM           (8)

/**FILTER状态*/
typedef enum {
	GXCA_TIMEOUT,               /**<FILTER超时*/
	GXCA_RECEIVED_SECTION       /**<FILTER收到一个SECTION*/
}GxCA_FilterStatus;

/**
 * @brief FILTER通知函数
 * @param [in] Filter          Filter句柄
 * @param [in] Section         SECTION指针
 * @param [in] Size            Section大小
 * @return void
 * @remark     Filter通知函数是采用回调的形式实现的.当一个Filter过滤到数据时
 * 将会调用本函数通知这个filter已经过滤到数据,这时Channel是过滤到
 * 数据的Filter所在Channel的句柄,Filter是本Filter的句柄,Status是
 * GXCA_RECEIVED_SECTION,Section是过滤到的Section数据.
 * 而当Filter超时时,Status的值为GXCA_TIMEOUT,Section等于NULL,
 * 其它值的意义与过滤到数据时的意义相同.
 * FilterNotify与SectionNotify函数的区别是,FilterNotify是针对每一个
 * Filter的,即每一个Fitler都有一个FilterNotify.而SectionNotify是
 * 针对所有过滤器的,所有的过滤器都共用一个通知函数SectionNotify
 * 因此FilterNotify是针对显式分配调用GxCA_DemuxChannelAllocate,
 * GxCA_DemuxFilterAllocate的情况下
 * * @see ::GxCA_DemuxChannelAllocate ::GxCA_DemuxChannelFree ::GxCA_DemuxChannelSetPID
 * ::GxCA_DemuxChannelEnable ::GxCA_DemuxChannelDisable ::GxCA_CaDemuxChannelReset
 * ::GxCA_DemuxFilterAllocate ::GxCA_DemuxFilterFree ::GxCA_CaDemuxFilterSetup
 * ::GxCA_DemuxFilterEnable ::GxCA_DemuxFilterDisable ::GxCA_DemuxFilterRegisterNotify
 */
typedef void ((*FilterNotify)(handle_t Filter, const uint8_t* Section, size_t Size));
/**
 * @brief FILTER超时通知函数
 * @param [in] Filter          Filter句柄
 * @return void
 * @remark     当一个ca的某个filter超时时，需要通知ca发生了过滤超时，使用
 * 回调形式实现
 */
typedef void ((*FilterTimeOut)(handle_t Filter));
/**
 * @brief       初始化Demux
 * @param [in]  Prior               线程优先级
 * @param [in]  TotalChannelNum     总共需要使用多少Channel数量
 * @param [in]  TotalFitlerNum      总共需要使用多少filter数量
 * @return      void                无
 * @see ::GxCA_DemuxChannelFree ::GxCA_DemuxChannelSetPID
 */
void GxCA_DemuxInit(uint8_t Prior, uint32_t TotalChannelNum, uint32_t TotalFitlerNum);
void GxCA_DemuxDestroy(void);
void GxCA_DemuxDisable(void);
void GxCA_DemuxEnable(void);
/**
 * @brief       分配一个Channel
 * @param [in]  DemuxID    使用的Demux设备号
 * @return      handle_t   分配成功,返回Channel句柄,失败返回
 GXCORE_INVALID_POINTER
 * @see ::GxCA_DemuxChannelFree ::GxCA_DemuxChannelSetPID
 */
handle_t GxCA_DemuxChannelAllocate(uint32_t DemuxID, int16_t PID, bool repeatFlag);
/**
 * @brief       释放一个Channel
 * @param [in]  Channel    释放的Channel句柄
 * @return      bool       释放成功,返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxChannelAllocate ::GxCA_DemuxChannelSetPID
 */
bool GxCA_DemuxChannelFree(handle_t Channel);
/**
 * @brief       设置Channel的PID
 * @param [in]  Channel    Channel句柄
 * @param [in]  PID        PID
 * @return      bool       设置成功,返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxChannelAllocate  ::GxCA_DemuxChannelFree
 */
bool GxCA_DemuxChannelSetPID(handle_t Channel, uint16_t PID, bool repeatFlag);

/**
 * @brief       启动Channel
 * @param [in]  Channel    Channel句柄
 * @return      bool       启动成功,返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxChannelDisable
 */
bool GxCA_DemuxChannelEnable(handle_t Channel);
/**
 * @brief       停止Channel
 * @param [in]  Channel    Channel句柄
 * @return      bool       停止成功,返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxChannelEnable
 */
bool GxCA_DemuxChannelDisable(handle_t Channel);
/**
 * @brief       复位Channel
 * @param [in]  Channel    Channel句柄
 * @return      bool       复位成功,返回TRUE,失败返回FALSE
 * @see
 */
bool GxCA_DemuxChannelReset(handle_t Channel);
/**
 * @brief       通过PID获取Channel句柄
 * @param [in]  pid         MPEG2TS PID
 * @return      handle_t    返回获取到的名柄
 * @see
 */
handle_t GxCA_DemuxChannelGetByPid(uint16_t pid);

/**
 * @brief       分配FILTER
 * @param [in]  Channel    Channel句柄
 * @param [in]  ID         标识Filter的数值
 * @return      handle_t   分配成功,返回FILTER句柄,失败返回GXCORE_INVALID_POINTER
 * @see
 */
handle_t GxCA_DemuxFilterAllocate(handle_t Channel, uint8_t ID);
/**
 * @brief       通过标识Filter的数值ID找到filter句柄
 * @param [in]  Channel     Channel句柄
 * @param [in]  ID          标识Filter的数值ID
 * @return      handle_t    查找成功,返回FILTER句柄,失败返回GXCORE_INVALID_POINTER
 * @see
 */
handle_t GxCA_DemuxFilterGetByID(handle_t Channel, uint8_t ID);
/**
 * @brief       通过filter句柄找到PID
 * @param [in]  Filter      Filter句柄
 * @param [in]  uint16_t    PID
 * @return      handle_t    查找成功,返回PID,失败返回0xFFFF
 * @see
 */
uint16_t GxCA_DemuxFilterGetPID(handle_t Filter);
/**
 * @brief       释放FILTER
 * @param [in]  Filter   Filter句柄
 * @return      bool     释放成功,返回TRUE,失败返回FALSE
 * @see
 */
uint8_t GxCA_DemuxFilteGetID(handle_t Filter);


bool GxCA_DemuxFilterFree(handle_t Filter);
/**
 * @brief       设置FILTER
 * @param [in]  Filter   Filter句柄
 * @param [in]  Match    匹配条件数组指针
 * @param [in]  Mask     匹配条件掩码
 * @param [in]  Equal    是否不等过滤
 * @param [in]  Depth    过滤深度
 * @param [in]  Timeout  超时时间  单位是ms
 * @return      bool     设置成功,返回TRUE,失败返回FALSE
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
 * @brief       注册回调函数
 * @param [in]  Filter           Filter句柄
 * @param [in]  Callback         回传过滤数据回调函数
 * @param [in]  TimeOutCallback  超时回调函数回调函数
 * @return      bool             启动成功返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxFilterDisable ::GxCA_CaDemuxFilterSetup
 */
bool GxCA_DemuxFilterRigsterNotify(handle_t Filter, FilterNotify Callback, FilterTimeOut TimeOutCallback);

/**
 * @brief       启动FILTER
 * @param [in]  Filter         Filter句柄
 * @return      bool           启动成功返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxFilterDisable ::GxCA_CaDemuxFilterSetup
 */
bool GxCA_DemuxFilterEnable(handle_t Filter);
/**
 * @brief       停止FILTER
 * @param [in]  Filter         Filter句柄
 * @return      bool           停止成功返回TRUE,失败返回FALSE
 * @see ::GxCA_DemuxFilterEnable
 */
bool GxCA_DemuxFilterDisable(handle_t Filter);
/**
 * @brief       复位FILTER
 * @param [in]  Filter         Filter句柄
 * @return      bool           复位成功返回TRUE,失败返回FALSE
 * @see
 */
bool GxCA_DemuxFilterReset(handle_t Filter);

__END_DECLS

#endif
/*@}*/
