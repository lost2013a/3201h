#ifndef  GXCAS_TEMPLATE_HH
#define  GXCAS_TEMPLATE_HH

#include "gxcas.h"
///< 提示参数到输入输出状态
#define IN
#define OUT

/*定义用于注册命令,事件的宏，在命令数组中直接添加宏即可 */
#if  CHECK_STRING_PARAM >0
#  define REGISTER_OPS(ops_name,ca_name)  {#ops_name,ca_name##ops_name,InputCheck##ops_name,OutputCheck##ops_name}
#  define REGISTER_EVENT(event_name)      {#event_name,EventCheck##event_name}
#else      /*register ops  with param check */
#  define REGISTER_OPS(ops_name,ca_name)  {#ops_name,ca_name##ops_name}
#  define REGISTER_EVENT(event_name)      {#event_name}
#endif     /*register ops with out param check*/

/*定义组成函数名称到宏，由CA前缀和操作名称组成 */
#define OPSFUN(cas_prefix,ops) cas_prefix##ops

#endif   /* ----- #ifndef GXCAS_TEMPLATE_INC  ----- */
