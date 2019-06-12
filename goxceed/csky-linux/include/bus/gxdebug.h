#ifndef __GX_DEBUG_H__
#define __GX_DEBUG_H__

#include "gxcore.h"

__BEGIN_DECLS

#define GXDBG_OK	0
#define GXDBG_ERR	(-1)

typedef enum
{
	GXDBG_LEVEL_NONE = -1, /* 未做单独设置，使用全局输出级别 */
	GXDBG_LEVEL_VERB = 0,  /* 输出 Verbose 级别信息 */
	GXDBG_LEVEL_INFO = 1,  /* 输出 Info 级别信息 */
	GXDBG_LEVEL_WARN = 2,  /* 输出 Warning 级别信息 */
	GXDBG_LEVEL_FAIL = 3,  /* 输出 Fail 级别信息 */
	GXDBG_LEVEL_ERROR = 4, /* 输出 Error 级别信息*/
	GXDBG_LEVEL_FATAL = 5, /* 输出 Fatal Error 级别信息 */
}GXDBG_LEVEL_T;

typedef enum
{
	GXDBG_MODULE_DEFAULT = 0, //全体模块
	GXDBG_MODULE_PLAYER =1,
	GXDBG_MODULE_GUI,
	GXDBG_MODULE_SI,
	GXDBG_MODULE_PM,
	GXDBG_MODULE_HOTPLUG,
	GXDBG_MODULE_FRONTEND,
	GXDBG_MODULE_HDMI,
	GXDBG_MODULE_SI_CONSOLE,
	GXDBG_MODULE_OTHER
}GXDBG_MODULE_T;

typedef enum
{
	GXDBG_OUTPUT_SERIAL = 0,     /* 使用串口打印，默认输出方式 */
	GXDBG_OUTPUT_FILE,           /* 输出到文件，该方式最好为NFS调试时使用 */
	GXDBG_OUTPUT_ETHERNET        /* 使用网络输出 */
}GXDBG_OUTPUT_MODE_T;

// 定义保存模块debug配置信息的数组，该值必须大于PORT_MODULE_OTHER
#define GXDBG_MODULE_MAX  128

typedef struct
{
        //char m_id;  // 保存模块id
        char m_level; // 保存模块打印输出等级
}GXDBG_CONF_T;

/******************************************************************************
 *                                 Declar Functions                           *
 ******************************************************************************/
/* debug info output*/
int gx_debug_output(GXDBG_MODULE_T id, GXDBG_LEVEL_T level,
		const char *file, int line, const char *function,
		const char *fmt, ...) __attribute__((format(printf, 6, 7)));

int gx_debug_set_level (GXDBG_MODULE_T id, GXDBG_LEVEL_T lv); /* set module debug level*/
int gx_debug_get_level (GXDBG_MODULE_T id, int *lv); /* get module debug level*/

int gx_debug_set_output(GXDBG_OUTPUT_MODE_T param); /* set debug out mode*/

int gx_debug_init(void);
int gx_debug_exit(void);

/*1-open printf  0-close printf*/
int gx_debug_ctr(int flag);


/******************************************************************************
 *                               Redefine Functions                           *
 ******************************************************************************/
//#define CONFIG_RELEASE

#define GXDBG_FATAL(ID, FORMAT, ARGS... )     gx_debug_output( (ID), GXDBG_LEVEL_FATAL,__FILE__, __LINE__, __FUNCTION__, FORMAT, ##ARGS )

#ifndef GXDBG

#define GXDBG_ERROR(ID, FORMAT, ARGS... )
#define GXDBG_FAILURE(ID, FORMAT, ARGS... )
#define GXDBG_WARN(ID, FORMAT, ARGS... )
#define GXDBG_INFO(ID, FORMAT, ARGS... )
#define GXDBG_VEBR(ID, FORMAT, ARGS... )
#define GXDBG_ASSERT(Exp)
#define GXDBG_CHECK_RET(Ret)
#else
#define GXDBG_ERROR(ID, FORMAT, ARGS... )     gx_debug_output( (ID), GXDBG_LEVEL_ERROR, __FILE__, __LINE__, __FUNCTION__, FORMAT, ##ARGS )
#define GXDBG_FAILURE(ID, FORMAT, ARGS... )   gx_debug_output( (ID), GXDBG_LEVEL_FAIL,  __FILE__, __LINE__, __FUNCTION__, FORMAT, ##ARGS )
#define GXDBG_WARN(ID, FORMAT, ARGS... )      gx_debug_output( (ID), GXDBG_LEVEL_WARN,  __FILE__, __LINE__, __FUNCTION__, FORMAT, ##ARGS )
#define GXDBG_INFO(ID, FORMAT, ARGS... )      gx_debug_output( (ID), GXDBG_LEVEL_INFO,  __FILE__, __LINE__, __FUNCTION__, FORMAT, ##ARGS )
#define GXDBG_VEBR(ID, FORMAT, ARGS... )      gx_debug_output( (ID), GXDBG_LEVEL_VERB,  __FILE__, __LINE__, __FUNCTION__, FORMAT, ##ARGS )

#define GXDBG_ASSERT(Exp)\
{\
	if (!(Exp))\
	{\
		printf("!!!Assertion failed: %s %d \n", __FILE__,__LINE__);\
		while(1);\
	}\
}

#define GXDBG_CHECK_RET(Ret) if (0 != (Ret))\
{printf("!!!CHECK_RET failed: %s %d \n", __FILE__,__LINE__);}

#endif

__END_DECLS

#endif  /* __GX_DEBUG_H__ */

