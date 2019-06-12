#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "gxcore.h"

__BEGIN_DECLS


#define     GXCONFIG_OK                     (0)                       /** 执行成功*/
#define     GXCONFIG_FAILURE                (-1)                      /** 执行失败*/
#define     EINPUT                          (-2)                      /** 输入参数错误*/
#define     MAX_CONFIG_VALUE_LEN            (64)                      /** 值最大长度*/
#define     GXBUS_CONFIG_FILE_NAME          "/home/gx/config.ini"     /** 配置文件名*/
#define     GXBUS_CONFIG_FILE_BACKUP        "/home/gx/config.ini.bak" /** 配置文件备份名*/
#define     GXBUS_FILE_PROTECT              "end"                     /** 文件完整性保护字符串*/
#define     KEY_SEPARATOR                   '>'                       /** Section与Parameter字符串间隔符*/

/**
 * @brief       将配置表恢复成默认设置
 * @param       void
 * @return      void
 * @see
 * @remarks     恢复成默认设置，相当于恢复成出厂设置
 */
void GxBus_ConfigLoadDefault(void);

/**
 * @brief       从配置表中获取key标识的变量的值
 * @param [in]  key         变量标识字符串
 * @param [out] buf         存储缓冲，当函数执行成功时，其值为key的字符串值
 * @param [in]  buf_size    存储缓冲的大小
 * @param [in]  dvalue      key变量的默认字符串值
 * @return      char*       NULL,输入参数错误
 *                          其它值，表示执行成功，返回buf指针，以用于左值表达式
 * @see         ::GxBus_ConfigSet
 * @remarks     获取key标识的变量的值时，存在两种可能情况，即key变量在配置表中存
 *              在时，返回其在配置表中的值；key变量在配置表不存在时，返回dvalue,
 *              并将在配置表中增加变量key，并以dvalue为变量key的值写入配置表
 */
char *GxBus_ConfigGet(const char *key, char *buf, size_t buf_size, const char *dvalue);

/**
 * @brief       从配置表中获取key标识的变量的值
 * @param [in]  key         变量标识字符串
 * @param [out] buf         存储缓冲，当函数执行成功时，其值为key的整型值
 * @return      int32_t*    NULL,输入参数错误
 *                          其它值，表示执行成功，返回buf指针，以用于左值表达式
 * @see         ::GxBus_ConfigSetInt
 * @remarks     获取key标识的变量的值时，存在两种可能情况，即key变量在配置表中存
 *              在时，返回其在配置表中的值；key变量在配置表不存在时，返回dvalue,
 *              并将在配置表中增加变量key，并以dvalue为变量key的值写入配置表
 */
int32_t *GxBus_ConfigGetInt(const char *key, int32_t *buf, int32_t dvalue);

/**
 * @brief       从配置表中获取key标识的变量的值
 * @param [in]  key         变量标识字符串
 * @param [out] buf         存储缓冲，当函数执行成功时，其值为key的双精浮点值
 * @param [in]  dvalue      key变量的默认双精浮点值
 * @return      double*     NULL,输入参数错误
 *                          其它值，表示执行成功，返回buf指针，以用于左值表达式
 * @see         ::GxBus_ConfigSetInt
 * @remarks     获取key标识的变量的值时，存在两种可能情况，即key变量在配置表中存
 *              在时，返回其在配置表中的值；key变量在配置表不存在时，返回dvalue,
 *              并将在配置表中增加变量key，并以dvalue为变量key的值写入配置表
 */
double *GxBus_ConfigGetDouble(const char *key, double *buf, double dvalue);

/**
 * @brief       设置key标识的变量的值到配置表
 * @param [in]  key         变量标识字符串
 * @param [in]  value       需要存储变量的字符串值
 * @return      int32_t     GXCONFIG_OK,设置成功
 *                          EINPUT, 输入参数错误
 *                          GXCONFIG_FAILURE,设置失败
 * @see         ::GxBus_ConfigSet
 * @remarks     如果设置的key在配置表中不存在，则函数将在配置表中增加这个KEY
 */
int32_t GxBus_ConfigSet(const char *key, const char *value);

/**
 * @brief       设置key标识的变量的值到配置表
 * @param [in]  key         变量标识字符串
 * @param [in]  value       需要存储变量的整型值
 * @return      int32_t     GXCONFIG_OK,设置成功
                            GXCONFIG_FAILURE,设置失败
 * @see         ::GxBus_ConfigSet
 * @remarks     如果设置的key在配置表中不存在，则函数将在配置表中增加这个KEY
 */
int32_t GxBus_ConfigSetInt(const char *key, int32_t value);

/**
 * @brief       设置key标识的变量的值到配置表
 * @param [in]  key         变量标识字符串
 * @param [in]  value       需要存储变量的浮点值
 * @return      int32_t     GXCONFIG_OK,设置成功
 *                          GXCONFIG_FAILURE,设置失败
 * @see         ::GxBus_ConfigSet
 * @remarks     如果设置的key在配置表中不存在，则函数将在配置表中增加这个KEY
 */
int32_t GxBus_ConfigSetDouble(const char *key, double value);

/**
 * @brief       打开配置表组
 * @param       void
 * @return      handle_t    组句柄,如果打开成功,返回组句柄,如果失败,返回值小于0
 * @see         ::GxBus_ConfigGroupClose ::GxBus_ConfigGroupSet
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     配置表的组的作用在于：当用户以组的方式调用 GxBus_ConfigGroupSet()
 *              接口设置某个key变量的值时，接口并没有将其值实际写入配置表，而是
 *              暂存变量的值，只有当用户调用 GxBus_ConfigGroupSave()接口时，才会
 *              根据其输入参数决定是否将缓冲的变量的值写入配置表；
 *              用户可以用同一个组句柄调用 GxBus_ConfigGroupSet()接口设置一个或多
 *              个变量的值，接口将会暂时缓冲这些变量的值，直到用户调用
 *              GxBus_ConfigGroupClose()接口时才会决定是否将缓冲的这些变量值写入
 *              配置表
 */
handle_t GxBus_ConfigGroupOpen(void);

/**
 * @brief       关闭配置表组
 * @param [in]  group       组句柄
 * @return      int32_t     EINPUT,输入参数错误
                            GXCONFIG_OK,执行成功
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupSet
                ::GxBus_ConfigGroupIsChanged
 * @remarks     关闭配置表组时,将会释放组的资源;因此如果将组中的变量值存入配置表
                必须先调用GxBus_ConfigGroupSave()接口.否则将会把组中变量值的改变
                丢弃
 */
int32_t GxBus_ConfigGroupClose(handle_t group);

/**
 * @brief       存储配置表组中变量的值到配置表
 * @param [in]  group       组句柄
 * @see
 * @remarks     将缓存在组中的变量值写入配置表
 */
int32_t GxBus_ConfigGroupSave(handle_t group);

/**
 * @brief       获取组变量的值
 * @param       group           组句柄
 * @param       key             变量标识字符串
 * @param       buf             存储缓冲，当函数执行成功时，其值为key的字符串值
 * @param       buf_size        存储缓冲大小
 * @param       dvalue          key变量的默认字符串值
 * @return      char*           NULL,输入参数错误
 *                              其它值，表示执行成功，返回buf指针，以用于左值表达式
 * @see
 * @remarks     获取组变量的值时,除出错情况之外,存在两种可能:如果这个变量的值没
 *              有以组方式设置改变过,则获取的值是配置表中的值,如果这个变量调用过
 *              GxBus_ConfigGroupSet()接口改变过,则获取的是组中缓冲的值
 */
char *GxBus_ConfigGroupGet(handle_t group, const char *key, char *buf, size_t buf_size, const char *dvalue);

/**
 * @brief       获取组变量的值
 * @param       group           组句柄
 * @param       key             变量标识字符串
 * @param       buf             存储缓冲，当函数执行成功时，其值为key的整形值
 * @param       dvalue          key变量的默认字符串值
 * @return      int32_t*        NULL,输入参数错误
 *                              其它值，表示执行成功，返回buf指针，以用于左值表达式
 * @see
 * @remarks     获取组变量的值时,除出错情况之外,存在两种可能:如果这个变量的值没
 *              有以组方式设置改变过,则获取的值是配置表中的值,如果这个变量调用过
 *              GxBus_ConfigGroupSet()接口改变过,则获取的是组中缓冲的值
 */
int32_t *GxBus_ConfigGroupGetInt(handle_t group, const char *key, int32_t *buf, int32_t dvalue);

/**
 * @brief       获取组变量的值
 * @param       group           组句柄
 * @param       key             变量标识字符串
 * @param       buf             存储缓冲，当函数执行成功时，其值为key的双精浮点值
 * @param       dvalue          key变量的默认字符串值
 * @return      double*         NULL,输入参数错误
 *                              其它值，表示执行成功，返回buf指针，以用于左值表达式
 * @see
 * @remarks     获取组变量的值时,除出错情况之外,存在两种可能:如果这个变量的值没
 *              有以组方式设置改变过,则获取的值是配置表中的值,如果这个变量调用过
 *              GxBus_ConfigGroupSet()接口改变过,则获取的是组中缓冲的值
 */
double *GxBus_ConfigGroupGetDouble(handle_t group, const char *key, double *buf, double dvalue);

/**
 * @brief       以组的方式设置key标识的变量值
 * @param [in]  group       组句柄
 * @param [in]  key         变量标识字符串
 * @param [in]  value       key变量的字符串值
 * @return      int32_t     GXCONFIG_OK,设置成功
 *                          EINPUT, 输入参数错误
 *                          GXCONFIG_FAILURE,设置失败
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     调用本接口设置变量的值时,并没有将变量值设置入配置表,而是将值进行
 *              缓冲,只有调用GxBus_ConfigGroupClose()时才会实际设置入配置表
 */
int32_t GxBus_ConfigGroupSet(handle_t group, const char *key, const char *value);

/**
 * @brief       以组的方式设置key标识的变量值
 * @param [in]  group       组句柄
 * @param [in]  key         变量标识字符串
 * @param [in]  value       key变量的整型值
 * @return      int32_t     GXCONFIG_OK,设置成功
 *                          EINPUT, 输入参数错误
 *                          GXCONFIG_FAILURE,设置失败
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     调用本接口设置变量的值时,并没有将变量值设置入配置表,而是将值进行
 *              缓冲,只有调用GxBus_ConfigGroupClose()时才会实际设置入配置表
 */
int32_t GxBus_ConfigGroupSetInt(handle_t group, const char *key, int32_t value);

/**
 * @brief       以组的方式设置key标识的变量值
 * @param [in]  group       组句柄
 * @param [in]  key         变量标识字符串
 * @param [in]  value       key变量的双精浮点值
 * @return      int32_t     GXCONFIG_OK,设置成功
 *                          EINPUT, 输入参数错误
 *                          GXCONFIG_FAILURE,设置失败
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     调用本接口设置变量的值时,并没有将变量值设置入配置表,而是将值进行
 *              缓冲,只有调用GxBus_ConfigGroupClose()时才会实际设置入配置表
 */
int32_t GxBus_ConfigGroupSetDouble(handle_t group, const char *key, double value);

/**
 * @brief       查询组中的变量值是否有改变
 * @param       group       组句柄
 * @return      bool        TRUE,组中的变量值已经改变
 *                          FALSE,组中的变量值没有改变
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupSet
 * @remarks
 */
bool GxBus_ConfigGroupIsChanged(handle_t group);

__END_DECLS

#endif

