#ifndef __GX_LIBINI_H__
#define __GX_LIBINI_H__

#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

#define EINVALID_HANDLE             (0)

/*********************************************************
 * @brief           ���ڴ��У���һ��INI�ļ���ʽ��INI���
 * @param [in]      memory ָ��һ��洢INI�ļ���ʽ���ڴ�
 * @param [in]      size memory�ڴ��С
 * @return handle_t �ɹ�����ֵINI�����ʧ�ܷ���EINVALID_HANDLE
 * @remarks
 */
handle_t ini_loadmemory(const char *memory, int size);


/** ******************************************************
 * @brief           ��һ��INI�ļ�
 * @param [in]      fname INI�ļ���
 * @return handle_t �ɹ�����ֵINI�����ʧ�ܷ���EINVALID_HANDLE
 * @remarks
 */
handle_t ini_open(const char*   fname);

/*********************************************************
 * @brief               ����һ���µ�INI�ļ�
 * @param [in]          fname Ҫ������INI�ļ���
 * @return handle_t     �ɹ�����ֵINI�����ʧ�ܷ���EINVALID_HANDLE
 * @remarks             ��fname�ļ���ΪNULLʱ����������һ�����ڴ��е�����
                        INI�ļ���������INI�ļ�ini_save�������������κθı䣬
                        ini_close�����ͷ�����INI�ļ������Դ
 */
handle_t ini_create(const char* fname);

/*********************************************************
 * @brief           ���������е�INI�ļ����ݱ��浽�ļ�
 * @param [in]      piniҪ�����INI�ļ�ָ��
 * @return int      ����ֵΪ�洢�ļ���ָ�뱣��ɹ�������NULLʧ��
 * @remarks
 */
char* ini_save(handle_t           ini);

/*********************************************************
 * @brief           ���������е�INI�ļ����ݣ���INI�ı���ʽ���浽�ڴ�
 * @param [in]      iniҪ�����INI�ļ����
 * @param [in]      mem�����Ŀ���ڴ�
 * @param [in]      sizeĿ���ڴ��mem��С
 * @return int      ����ֵΪmemʵ�ʴ洢�ֽڴ�С���������0��ʾ����
 * @remarks
 */
size_t ini_savememory(handle_t ini, char* mem, size_t size);

/*********************************************************
 * @brief           �ͷ�INI�ļ�ռ�õ��ڴ���Դ
 * @param [in] pini Ҫ�ͷŵ�INI�ļ�ָ��
 * @return void     �޷���ֵ
 * @remarks
 */
void ini_close(handle_t           ini);

/*********************************************************
 * @brief               ȡ��ָ�����ļ�ֵ
 * @param [in] pini     INI�ļ�ָ��
 * @param [in] section  �����ַ���ָ��
 * @param [in] param    �������ַ���ָ��
 * @return char*        ����value����ֵ���ַ���ָ�룬����NULL��ȡʧ��
 * @remarks
 */
char *ini_get(handle_t           ini,
              const char*   section,
              const char*   param);

/*********************************************************
 * @brief               ����ָ�����ļ�ֵ
 * @param [in] pini     INI�ļ�ָ��
 * @param [in] param    �����ַ���ָ��
 * @value [in]          ���ڱ���Ҫ���õ�ֵ���ַ���ָ��
 * @return int          ����ֵΪ0���óɹ���-1����ʧ��
 * @remarks
*/
int ini_set(handle_t ini, const char *section, const char *param, const char *value);

/*********************************************************
 * @brief               ����¼�
 * @param [in] pini     INI�ļ�ָ��
 * @param [in] section  �����ַ���ָ��
 * @param [in] param    �������ַ���ָ��
 * @param [in] value    ��ֵ�ַ���ָ��
 * @return int          ����ֵΪ0���óɹ���-1����ʧ��
 * @remarks
 */
int ini_append(handle_t ini, const char *section, const char *param, const char *value);

/*********************************************************
 * @brief               �Ƴ�ָ����
 * @param [in] pini     INI�ļ�ָ��
 * @param [in] section  �����ַ���ָ��
 * @param [in] param    �������ַ���ָ��, ����ֵΪNULLʱ����ʾ��ɾ������section
                        ����parameters
 * @return int          ����ֵΪ0ɾ���ɹ���-1ɾ��ʧ��
 * @remarks
 */
int ini_remove(handle_t ini, const char *section, const char *param);

/*********************************************************
 * @brief           �ϲ�����INI�ļ�
 * @param [in,out]  src_old INI�ļ�ָ��
 * @param [in]      src_new INI�ļ�ָ��
 * @return          ����ֵΪ0�ϲ��ɹ���-1�ϲ�ʧ��
 * @remark          �ϲ�����INI�ļ��������src_new���ڵ�section��key,��src_old
                    �����ڣ�����ӵ�src_old���У�����Ѿ����ڣ���src_new�е�ֵ
                    ����src_old�е�ֵ
 */
int ini_merge(handle_t  old_ini, handle_t new_ini);

__END_DECLS

#endif

