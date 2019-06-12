/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DMX_SUB_SYSTEM_H__
#define __DMX_SUB_SYSTEM_H__

#include "gxcore.h"

__BEGIN_DECLS

/*返回值*/
#define GX_DMX_SUB_PARAMETER_ERR (-1)
#define GX_DMX_SUB_ERR           (-2)
#define GX_DMX_SUB_SUCCESS       (0)

/* Exported Types --------------------------------------------------------- */

#if 0
#define DMX_SUB_SLOT_NUM   (64)//slot的支持数量
#define DMX_SUB_FILTER_NUM   (64)//filter的支持数量
#define DMX_SUB_NUM       (2)//dmx的支持数量
#else
uint32_t DMX_SUB_FILTER_NUM;
uint32_t DMX_SUB_SLOT_NUM;
uint32_t DMX_SUB_NUM;
#endif
#define DMX_SUB_MAX_NAME       (8)//dmx的名字长度

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
    uint16_t   pid;         ///< pid 的值
    uint8_t    match_depth;     ///< 匹配深度
    uint8_t    eq_or_neq;       ///< 匹配过滤填写宏SUBSYSTEM_DMX_EQ_MATCH  不等匹配填写宏SUBSYSTEM_DMX_NEQ_MATCH
    uint32_t   crc;        ///< 过滤时是否时能crc校验,SUBSYSTEM_DMX_CRC_ON ,SUBSYSTEM_DMX_CRC_OFF 
    uint32_t   soft_filter;///< 过滤时是否使用软件进行匹配,SUBSYSTEM_DMX_SOFT_OFF,SUBSYSTEM_DMXSOFT_ON

    uint8_t    match[18];       ///< 匹配值
    uint8_t    mask[18];        ///< 匹配值的掩码，对应位为1并且匹配深度足够，才会///按匹配值来过滤
	uint32_t sw_buffer_size;//filter fifo的大小 小于64K 使用驱动默认配置
} GxSubsystemDmxAllocFilter;


typedef  int32_t dmx_handle_t;
typedef  int32_t filter_handle_t;

/* Exported Functions ----------------------------------------------------- */

/**
 * @brief      初始化dmx子系统
 * 
 * @param     
 *           
 * 
 * @return     GX_DMX_SUB_ERR:执行错误
 *             GX_DMX_SUB_SUCCESS：执行成功  
 */
int32_t GxSubSystem_DmxInit(void);

/**
 * @brief      打开dmx子系统，获取控制句柄
 * 
 * @param       uint32_t dmx_id:dmx的id，在我们的系统中有两路dmx，id为0或者是1
 *              uint32_t ts：和dmx绑定的ts编号，从0开始
 * 
 * @return      dmx子系统的控制块,如果是-1表示打开失败
 */
dmx_handle_t GxSubSystem_DmxOpen(uint32_t dmx_id,uint32_t ts);


/**
 * @brief      获取dmx子系统中的device句柄
 * 
 * @param       dmx_handle_t dmx:dmx子系统的句柄
 * 
 * @return      dmx子系统所对应的device句柄 -1代表发生了错误
 */
handle_t  GxSubSystem_DmxGetDevice(dmx_handle_t dmx);

/**
 * @brief      获取dmx子系统中的module句柄
 * 
 * @param       dmx_handle_t dmx:dmx子系统的句柄
 * 
 * @return      dmx子系统所对应的module句柄 -1代表发生了错误
 */
handle_t  GxSubSystem_DmxGetModule(dmx_handle_t dmx);

/**
 * @brief      查询ts是否锁定
 * 
 * @param       dmx_handle_t dmx:dmx子系统的句柄
 * 
 * @return      1：ts锁定
 *              0：ts没有锁定
 *              -1：运行错误
 */
int32_t GxSubSystem_DmxQueryStatus(dmx_handle_t dmx);

/**
 * @brief      关闭打开的dmx子系统
 * 
 * @param       dmx_handle_t dmx:dmx子系统的句柄
 * 
 * @return     GX_DMX_SUB_ERR:执行错误
 *             GX_DMX_SUB_SUCCESS：执行成功  
 */
int32_t  GxSubSystem_DmxClose(dmx_handle_t dmx);

/**
 * @brief      申请过滤
 * 
 * @param       dmx_handle_t dmx:dmx子系统的句柄
 *              GxSubsystemDmxAllocFilter* para：过滤参数
 * 
 * @return     -1:执行错误
 *              其他值：过滤的控制句柄
 *             
 */
filter_handle_t GxSubSystem_DmxFilterAlloc(dmx_handle_t dmx, GxSubsystemDmxAllocFilter* para);

/**
 * @brief      开始过滤
 * 
 * @param      filt_handle_t filter:filter的句柄
 * 
 * @return     GX_DMX_SUB_ERR: 执行错误
 *             GX_DMX_SUB_PARAMETER_ERR：参数错误
 *             GX_DMX_SUB_SUCCESS：执行成功
 */
int32_t  GxSubSystem_DmxFilterStart(filter_handle_t filter);

/**
 * @brief      停止过滤
 * 
 * @param      filt_handle_t filter:filter的句柄
 * 
 * @return     GX_DMX_SUB_ERR: 执行错误
 *             GX_DMX_SUB_PARAMETER_ERR：参数错误
 *             GX_DMX_SUB_SUCCESS：执行成功
 */
int32_t  GxSubSystem_DmxFilterStop(filter_handle_t filter);

/**
 * @brief      释放过滤
 * 
 * @param      filt_handle_t filter:filter的句柄
 * 
 * @return     GX_DMX_SUB_ERR: 执行错误
 *             GX_DMX_SUB_PARAMETER_ERR：参数错误
 *             GX_DMX_SUB_SUCCESS：执行成功
 */
int32_t  GxSubSystem_DmxFilterRelease(filter_handle_t filter);

/**
 * @brief      等待过滤数据,当正确申请了filter后该接口在等待过程中会引起线程休
 * 眠
 * 
 * @param       dmx_handle_t dmx:dmx子系统的句柄 
 *              filt_handle_t* filter:返回有数据的filter的句柄，空间由应用开，
 *              为了安全,空间大小最好等于
 *              sizeof(filter_handle_t)*SI_DMX_SUB_FILTER_NUM
 * 
 * @return     0: 没有任何filter过滤到数据
 *              1~64：有数据的filter数量
 *              GX_DMX_SUB_ERR: 执行错误
 */
int32_t  GxSubSystem_DmxFilterWait(dmx_handle_t dmx,filter_handle_t* filter);

/**
 * @brief      读取过滤到的数据，是连续的n个section数据
 * 
 * @param      filt_handle_t filter:filter的句柄
 *              data_out:存放读取到得数据的buf
 *              buf_size：data_out的大小
 * 
 * @return     实际读取的数据量
 *             GX_DMX_SUB_ERR: 执行错误
 */
int32_t  GxSubSystem_DmxFilterRead(filter_handle_t filter,uint8_t* data_out, uint32_t buf_size);


/**
 * @brief      获取DMX SLOT FILTER的数量
 * 
 * @param     dmx,slot,filter:用来保存实际硬件数量的变量地址
 *          
 * 
 * @return     
 */
void GxSubsystem_DmxGetHardwareNum(uint32_t * dmx,uint32_t * channel_num);

/**
 * @brief      改变过滤 条件，之前必须先stop
 * 
 * @param      filt_handle_t filter:filter的句柄
 *              GxSubsystemDmxAllocFilter* para：过滤参数
 * 
 * @return     GX_DMX_SUB_ERR: 执行错误
 *             GX_DMX_SUB_PARAMETER_ERR：参数错误
 *             GX_DMX_SUB_SUCCESS：执行成功
 *             
 */
int32_t GxSubSystem_DmxFilterModify(filter_handle_t filter, GxSubsystemDmxAllocFilter* para);
__END_DECLS

#endif
/*@}*/

