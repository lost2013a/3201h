/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_SUB_ENGINE_H__
#define __SI_SUB_ENGINE_H__

#include "gxcore.h"
#include "sub_system/dmx_sub_system/dmx_sub_system.h"

__BEGIN_DECLS

/*返回值*/
#define GX_SI_ENGINE_PARAMETER_ERR (-1)
#define GX_SI_ENGINE_ERR           (-2)
#define GX_SI_ENGINE_SUCCESS       (0)
#define SI_ENGINE_NUM              (DMX_SUB_FILTER_NUM)//最多支持的过滤数，等于硬件支持的filter个数
#define SI_READ_SIZE               (64*1024)//每次读取的section字节数

typedef int32_t SiEngineHandle;
/* Exported Types --------------------------------------------------------- */

typedef enum {
    SECTION_OK = 0,
    TABLE_OK,
	REPEAT_SECTION,//重复的section
    ERR_PARAMS,
}SiEngineParseStatus;


typedef enum{
    GX_SEARCH_FRONT_ATSC_T = 0,
    GX_SEARCH_FRONT_ATSC_C,
    GX_SEARCH_FRONT_DVB_S,
    GX_SEARCH_FRONT_DVB_T,
    GX_SEARCH_FRONT_DVB_C,
    GX_SEARCH_FRONT_DVB_DTMB,
    GX_SEARCH_FRONT_DVB_DVBT2,
}GxSearchFrontType;



/*定义获取到原始section数据时的行为当,返回1时将会继续进行标准的section的表解析;
 * 如果想停止本次过滤，需要调用GxSubSystem_SiEngineFree或者GxSubSystem_SiEnginePause并返回0
 * 如果不注册务必写NULL,此时会执行默认的处理，相当于返回1,此函数执行时间不能超过5S。
 * status中存放了当前的表是否过滤完全*
 * si是本次过滤的句柄*/
typedef int32_t (*OriginalSection)(SiEngineHandle si,uint8_t *section, uint32_t len,SiEngineParseStatus status);


/*定义获取到解析好的section数据时的行为,当返回1时将会继续进行表过滤;
 * 如果想停止本次过滤，需要调用GxSubSystem_SiEngineFree或者GxSubSystem_SiEnginePause并返回0
 * 如果不注册务必写NULL,此时会执行默认的过滤处理,此函数执行时间不能超过5S.
 * table可以强制转换成本次解析的表结构
 * status中存放了当前的表是否过滤完全
 * si是本次过滤的句柄*/
typedef int32_t (*TableSection)(SiEngineHandle si, void *table, SiEngineParseStatus status);

/*定义超时的行为当返回1时将会继续进行表过滤;
 * 如果想停止本次过滤，需要调用GxSubSystem_SiEngineFree或者GxSubSystem_SiEnginePause并返回0
 * 如果不注册务必写NULL，此时会执行默认的超时处理，相当于返回0，函数执行时间不能超过5S
 * si是本次过滤的句柄*/
typedef int32_t (*TimeOut)(SiEngineHandle si);

/*定义检测是否过滤完成,函数执行时间不能超过5S;
 * 如果不注册务必写NULL，此时会执行默认的检测。
 * si是本次过滤的句柄
 * sec是原始sec数据*/
typedef  SiEngineParseStatus (*SecNumCheck)(SiEngineHandle si,uint8_t* sec);

typedef struct
{
	uint32_t dmx_id;
	uint32_t ts;
	GxSubsystemDmxAllocFilter filter;
	OriginalSection original;
	TableSection table;
    TimeOut time_out;
	SecNumCheck sec_num_check;
	uint32_t time_ms;
    GxSearchFrontType front_type;
    void * p;//用来存储用户数据的指针
} GxSubsystemSiEngineAlloc;



typedef enum{
    PROTOCOL_DVB = 1,
    PROTOCOL_ATSC,
}PROTOCOL_TYPE;

typedef struct{
    uint32_t dmx_id;//硬件dmx id，由驱动提供，目前分别是0,1.
    PROTOCOL_TYPE protocol;//dmx的解析协议，主要用于注册对应协议的解析库
}GxSubsystemSiProtocol;

typedef struct
{
	uint32_t parse_thread_count;//用于解析的线程数，传入0使用默认数量（1）.如果觉得解析慢可以增加解析线程
	uint32_t parse_stack;//解析栈大小，传入0使用默认值（16*1024）
	uint32_t parse_pri;//解析优先级，传入0使用默认值（11）
	uint32_t read_stack;//解析栈大小，传入0使用默认值（16*1024）
	uint32_t read_pri;//读数据优先级，传入0使用默认值（10）
    uint32_t init_dmx_num;//注册dmx解析协议数量，需要与下面dmx_protocol申请的数量对应
    GxSubsystemSiProtocol * dmx_protocol;//注册dmx的解析协议,使用时需要清楚要使用多少个dmx来进行初始化
}GxSubsystemSiEngineInit;

/**
 * @brief      初始化si
 * 
 * @param      parse_thread_count 
 * 
 * @return    GX_SI_ENGINE_ERR  失败
 *            GX_SI_ENGINE_SUCCESS   成功
 */
status_t GxSubSystem_SiEngineInit(GxSubsystemSiEngineInit* init);

/**
 * @brief      申请一次过滤
 * 
 * @param      
 * 
 * @return     成功申请到的si句柄，如果返回-1 则申请失败
 */
SiEngineHandle GxSubSystem_SiEngineAlloc(GxSubsystemSiEngineAlloc* para);

/**
 * @brief      启动过滤
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR 传入的参数不对
 *            GX_SI_ENGINE_ERR  失败
 *            GX_SI_ENGINE_SUCCESS   成功
 */
status_t  GxSubSystem_SiEngineStart(SiEngineHandle si);

/**
 * @brief      释放过滤
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR 传入的参数不对
 *            GX_SI_ENGINE_ERR  失败
 *            GX_SI_ENGINE_SUCCESS   成功
 */
status_t  GxSubSystem_SiEngineFree(SiEngineHandle si);

/**
 * @brief      暂停过滤 不会释放硬件，但是会清除所有数据缓冲
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR 传入的参数不对
 *            GX_SI_ENGINE_ERR  失败
 *            GX_SI_ENGINE_SUCCESS   成功
 */
status_t  GxSubSystem_SiEnginePause(SiEngineHandle si);

/**
 * @brief      改变过滤参数。
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR 传入的参数不对
 *            GX_SI_ENGINE_ERR  失败
 *            GX_SI_ENGINE_SUCCESS   成功
 */
status_t  GxSubSystem_SiEngineModify(SiEngineHandle si,GxSubsystemSiEngineAlloc* para);

/**
 * @brief      重启过滤 不会释放硬件，不会清除数据缓冲
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR 传入的参数不对
 *            GX_SI_ENGINE_ERR  失败
 *            GX_SI_ENGINE_SUCCESS   成功
 */
status_t  GxSubSystem_SiEngineRestart(SiEngineHandle si);
/**
 * @brief      获取用户私有信息
 * 
 * @param      
 * 
 * @return    用户申请si时传入的私有信息指针
 */
void* GxSubSystem_SiEngineGetUser(SiEngineHandle si);

__END_DECLS

#endif
/*@}*/

