#ifndef __GX_LIBINI_H__
#define __GX_LIBINI_H__

#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

#define EINVALID_HANDLE             (0)

/*********************************************************
 * @brief           从内存中，打开一个INI文件格式的INI句柄
 * @param [in]      memory 指内一块存储INI文件格式的内存
 * @param [in]      size memory内存大小
 * @return handle_t 成功返回值INI句柄，失败返回EINVALID_HANDLE
 * @remarks
 */
handle_t ini_loadmemory(const char *memory, int size);


/** ******************************************************
 * @brief           打开一个INI文件
 * @param [in]      fname INI文件名
 * @return handle_t 成功返回值INI句柄，失败返回EINVALID_HANDLE
 * @remarks
 */
handle_t ini_open(const char*   fname);

/*********************************************************
 * @brief               创建一个新的INI文件
 * @param [in]          fname 要创建的INI文件名
 * @return handle_t     成功返回值INI句柄，失败返回EINVALID_HANDLE
 * @remarks             当fname文件名为NULL时，创建的是一个在内存中的虚拟
                        INI文件，对虚拟INI文件ini_save操作将不会有任何改变，
                        ini_close将会释放虚拟INI文件相关资源
 */
handle_t ini_create(const char* fname);

/*********************************************************
 * @brief           将缓冲区中的INI文件内容保存到文件
 * @param [in]      pini要保存的INI文件指针
 * @return int      返回值为存储文件名指针保存成功，返回NULL失败
 * @remarks
 */
char* ini_save(handle_t           ini);

/*********************************************************
 * @brief           将缓冲区中的INI文件内容，以INI文本格式保存到内存
 * @param [in]      ini要保存的INI文件句柄
 * @param [in]      mem保存的目标内存
 * @param [in]      size目标内存的mem大小
 * @return int      返回值为mem实际存储字节大小，如果返回0表示出错
 * @remarks
 */
size_t ini_savememory(handle_t ini, char* mem, size_t size);

/*********************************************************
 * @brief           释放INI文件占用的内存资源
 * @param [in] pini 要释放的INI文件指针
 * @return void     无返回值
 * @remarks
 */
void ini_close(handle_t           ini);

/*********************************************************
 * @brief               取得指定键的键值
 * @param [in] pini     INI文件指针
 * @param [in] section  段名字符串指针
 * @param [in] param    参数名字符串指针
 * @return char*        用于value返回值的字符串指针，返回NULL获取失败
 * @remarks
 */
char *ini_get(handle_t           ini,
              const char*   section,
              const char*   param);

/*********************************************************
 * @brief               设置指定键的键值
 * @param [in] pini     INI文件指针
 * @param [in] param    键名字符串指针
 * @value [in]          用于保存要设置的值的字符串指针
 * @return int          返回值为0设置成功，-1设置失败
 * @remarks
*/
int ini_set(handle_t ini, const char *section, const char *param, const char *value);

/*********************************************************
 * @brief               添加新键
 * @param [in] pini     INI文件指针
 * @param [in] section  段名字符串指针
 * @param [in] param    参数名字符串指针
 * @param [in] value    键值字符串指针
 * @return int          返回值为0设置成功，-1设置失败
 * @remarks
 */
int ini_append(handle_t ini, const char *section, const char *param, const char *value);

/*********************************************************
 * @brief               移除指定键
 * @param [in] pini     INI文件指针
 * @param [in] section  段名字符串指针
 * @param [in] param    参数名字符串指针, 当其值为NULL时，表示将删除整个section
                        所有parameters
 * @return int          返回值为0删除成功，-1删除失败
 * @remarks
 */
int ini_remove(handle_t ini, const char *section, const char *param);

/*********************************************************
 * @brief           合并两个INI文件
 * @param [in,out]  src_old INI文件指针
 * @param [in]      src_new INI文件指针
 * @return          返回值为0合并成功，-1合并失败
 * @remark          合并两个INI文件，如果在src_new存在的section或key,在src_old
                    不存在，在添加到src_old当中，如果已经存在，则将src_new中的值
                    覆盖src_old中的值
 */
int ini_merge(handle_t  old_ini, handle_t new_ini);

__END_DECLS

#endif

