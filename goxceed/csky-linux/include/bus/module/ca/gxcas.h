#ifndef __GXCAS_HHH__
#define __GXCAS_HHH__
//
///< 配置是否打开参数检测功能
#define CHECK_STRING_PARAM			(0)

#include "gxcore.h"
#include "gxcas_dbg.h"
#include "gx_jansson.h"
#include "gxcas_template.h"
#include "gxcas_func_lib.h"
#include "gx_demux.h"
#include "gx_smartcard.h"
#include "gx_descrambler.h"
#include "gxcas_template.h"

__BEGIN_DECLS

///< 配置注册到CA名称长度
#define GXCA_NAME_SIZE		(32)


///< 函数状态返回值
#ifndef E_OK
#define E_SUCESS                (0)
#endif
#ifndef E_FAILURE
#define E_FAILURE               (-1)
#endif

#ifndef E_INVALID_PARAM
#define E_INVALID_PARAM         (-2)
#endif

#ifndef E_INVALID_HANDLE
#define E_INVALID_HANDLE        (0)
#endif


///< GXCAS state
typedef enum {
	GXCAS_SUCCESS           = 0,    ///< 成功
	GXCAS_ERR               = -1,   ///< 错误
	GXCAS_PARAM_ERR         = -2,   ///< 参数错误
	GXCAS_CANT_FIND_OPS     = -3,   ///< 对应的ops不存在

	GXCAS_PIN_ERR           = -100, ///< 密码错误
	GXCAS_PIN_LOCKED        = -101, ///< 密码错误

	GXCAS_SMC_ERR           = -200, ///< 智能卡错误
	GXCAS_SMC_INVALID_CARD  = -201, ///< 无效智能卡
	GXCAS_SMC_CARD_OUT      = -202, ///< 智能卡未插入
	GXCAS_SMC_VER_ERR       = -203, ///< 智能卡版本错误

	GXCAS_ENTITLE_ERR       = -300, ///< 授权错误
	GXCAS_ENTITLE_NOENTITLE = -301, ///< 节目未授权
	GXCAS_ENTITLE_OVERDUE   = -302, ///< 节目授权过期
} GxCasErr_t;

///< GXCAS 控制块
typedef struct CasOps_s {
	const char* name;/*ops 名称,见文档*/
	GxCasErr_t (*ops)(int32_t ,const char*,const char**);/*ops 函数实现*/
#if CHECK_STRING_PARAM
	int32_t (*input_check)(const char*); /*输入字符串检查函数*/
	int32_t (*output_check)(const char*);/*输出字符串检查函数*/
#endif
} GxCasOps_t;

typedef struct CasEvent_s {
	const char* name;/*事件 名称,见文档*/
#if CHECK_STRING_PARAM
	int32_t (*context_check)(const char*);/*事件内容检测函数*/
#endif
} GxCasEvents_t;

typedef struct GXCASystem_s {
	uint32_t magic;       ///< 魔数用于确定是否为正确的句柄
	uint32_t count;       ///< 多次打开这份CA的计数，用于判断是否能释放全部资源
	handle_t handle;      ///< 记录多次打开的同一份CA的返回句柄
	handle_t lock;        ///< 互斥锁句柄

	/*以下成员注册时需要赋值 */
	char *name;           ///< 注册的CA名称,打开时与此对应
	int32_t ops_num;      ///< 注册的CA Ops 个数
	GxCasOps_t *ops;      ///< 注册的CA ops 列表

	int32_t event_num;    ///< 注册的CA 事件个数
	GxCasEvents_t *event; ///< 注册的CA 事件列表
} GxCasSystem_t;


/**
* @brief	open a ca with name.
* @param	const char * name:name of cas;
* @param        const char* pOpenParam:JSON string type param to open the CA.
*               see <代码设计－GxCas_IOCTL定义及参数集合模板说明.doc>
* @return	handle_t: E_INVALID_HANDLE,open failure. else the handle of ca
*/
handle_t GxCas_OpenCa(const char * name,IN const char* pOpenString);

/**
* @brief	close a ca with the handle.
* @param	handle_t handle: handle of ca.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_CloseCa(handle_t handle);

/**
* @brief	ioctl, call function of cas via ops name.
* @param	handle_t handle: handle of ca.
* @param	IN const char* input: input param string.
* @param	OUT char** output:  output param string.
*               see <代码设计－GxCas_IOCTL定义及参数集合模板说明.doc>
* @return	GxCasErr_t: enum of state.
*/
GxCasErr_t GxCas_Ioctl(int32_t  handle,const char* ops_name, IN const char* input,OUT const char** output);

/**
* @brief	wait event.function must be called circular
* @param	handle_t handle: handle of ca.
* @param	OUT char** event_string: out put json string that descript event.
*               see <代码设计－GxCas_事件定义及参数集合模板说明.doc>
* @param	uint32_t time_out:time out.if cant get event within the time, task will be suspended.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_WaitEvent(int32_t handle,OUT const char** event_string,uint32_t time_out);

/**
* @brief	register a ca with name, ops list.
* @param	GxCasystem_t cas: name  ops list of the ca.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_RegisterCa(GxCasSystem_t* cas);

/**
* @brief	unregister a ca via ca's name.
* @param	const char * name: name of the ca.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_UnRegisterCa(const char * name);

__END_DECLS

#endif


