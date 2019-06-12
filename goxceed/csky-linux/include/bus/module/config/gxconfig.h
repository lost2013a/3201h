#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "gxcore.h"

__BEGIN_DECLS


#define     GXCONFIG_OK                     (0)                       /** ִ�гɹ�*/
#define     GXCONFIG_FAILURE                (-1)                      /** ִ��ʧ��*/
#define     EINPUT                          (-2)                      /** �����������*/
#define     MAX_CONFIG_VALUE_LEN            (64)                      /** ֵ��󳤶�*/
#define     GXBUS_CONFIG_FILE_NAME          "/home/gx/config.ini"     /** �����ļ���*/
#define     GXBUS_CONFIG_FILE_BACKUP        "/home/gx/config.ini.bak" /** �����ļ�������*/
#define     GXBUS_FILE_PROTECT              "end"                     /** �ļ������Ա����ַ���*/
#define     KEY_SEPARATOR                   '>'                       /** Section��Parameter�ַ��������*/

/**
 * @brief       �����ñ�ָ���Ĭ������
 * @param       void
 * @return      void
 * @see
 * @remarks     �ָ���Ĭ�����ã��൱�ڻָ��ɳ�������
 */
void GxBus_ConfigLoadDefault(void);

/**
 * @brief       �����ñ��л�ȡkey��ʶ�ı�����ֵ
 * @param [in]  key         ������ʶ�ַ���
 * @param [out] buf         �洢���壬������ִ�гɹ�ʱ����ֵΪkey���ַ���ֵ
 * @param [in]  buf_size    �洢����Ĵ�С
 * @param [in]  dvalue      key������Ĭ���ַ���ֵ
 * @return      char*       NULL,�����������
 *                          ����ֵ����ʾִ�гɹ�������bufָ�룬��������ֵ���ʽ
 * @see         ::GxBus_ConfigSet
 * @remarks     ��ȡkey��ʶ�ı�����ֵʱ���������ֿ����������key���������ñ��д�
 *              ��ʱ�������������ñ��е�ֵ��key���������ñ�����ʱ������dvalue,
 *              ���������ñ������ӱ���key������dvalueΪ����key��ֵд�����ñ�
 */
char *GxBus_ConfigGet(const char *key, char *buf, size_t buf_size, const char *dvalue);

/**
 * @brief       �����ñ��л�ȡkey��ʶ�ı�����ֵ
 * @param [in]  key         ������ʶ�ַ���
 * @param [out] buf         �洢���壬������ִ�гɹ�ʱ����ֵΪkey������ֵ
 * @return      int32_t*    NULL,�����������
 *                          ����ֵ����ʾִ�гɹ�������bufָ�룬��������ֵ���ʽ
 * @see         ::GxBus_ConfigSetInt
 * @remarks     ��ȡkey��ʶ�ı�����ֵʱ���������ֿ����������key���������ñ��д�
 *              ��ʱ�������������ñ��е�ֵ��key���������ñ�����ʱ������dvalue,
 *              ���������ñ������ӱ���key������dvalueΪ����key��ֵд�����ñ�
 */
int32_t *GxBus_ConfigGetInt(const char *key, int32_t *buf, int32_t dvalue);

/**
 * @brief       �����ñ��л�ȡkey��ʶ�ı�����ֵ
 * @param [in]  key         ������ʶ�ַ���
 * @param [out] buf         �洢���壬������ִ�гɹ�ʱ����ֵΪkey��˫������ֵ
 * @param [in]  dvalue      key������Ĭ��˫������ֵ
 * @return      double*     NULL,�����������
 *                          ����ֵ����ʾִ�гɹ�������bufָ�룬��������ֵ���ʽ
 * @see         ::GxBus_ConfigSetInt
 * @remarks     ��ȡkey��ʶ�ı�����ֵʱ���������ֿ����������key���������ñ��д�
 *              ��ʱ�������������ñ��е�ֵ��key���������ñ�����ʱ������dvalue,
 *              ���������ñ������ӱ���key������dvalueΪ����key��ֵд�����ñ�
 */
double *GxBus_ConfigGetDouble(const char *key, double *buf, double dvalue);

/**
 * @brief       ����key��ʶ�ı�����ֵ�����ñ�
 * @param [in]  key         ������ʶ�ַ���
 * @param [in]  value       ��Ҫ�洢�������ַ���ֵ
 * @return      int32_t     GXCONFIG_OK,���óɹ�
 *                          EINPUT, �����������
 *                          GXCONFIG_FAILURE,����ʧ��
 * @see         ::GxBus_ConfigSet
 * @remarks     ������õ�key�����ñ��в����ڣ������������ñ����������KEY
 */
int32_t GxBus_ConfigSet(const char *key, const char *value);

/**
 * @brief       ����key��ʶ�ı�����ֵ�����ñ�
 * @param [in]  key         ������ʶ�ַ���
 * @param [in]  value       ��Ҫ�洢����������ֵ
 * @return      int32_t     GXCONFIG_OK,���óɹ�
                            GXCONFIG_FAILURE,����ʧ��
 * @see         ::GxBus_ConfigSet
 * @remarks     ������õ�key�����ñ��в����ڣ������������ñ����������KEY
 */
int32_t GxBus_ConfigSetInt(const char *key, int32_t value);

/**
 * @brief       ����key��ʶ�ı�����ֵ�����ñ�
 * @param [in]  key         ������ʶ�ַ���
 * @param [in]  value       ��Ҫ�洢�����ĸ���ֵ
 * @return      int32_t     GXCONFIG_OK,���óɹ�
 *                          GXCONFIG_FAILURE,����ʧ��
 * @see         ::GxBus_ConfigSet
 * @remarks     ������õ�key�����ñ��в����ڣ������������ñ����������KEY
 */
int32_t GxBus_ConfigSetDouble(const char *key, double value);

/**
 * @brief       �����ñ���
 * @param       void
 * @return      handle_t    ����,����򿪳ɹ�,��������,���ʧ��,����ֵС��0
 * @see         ::GxBus_ConfigGroupClose ::GxBus_ConfigGroupSet
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     ���ñ������������ڣ����û�����ķ�ʽ���� GxBus_ConfigGroupSet()
 *              �ӿ�����ĳ��key������ֵʱ���ӿڲ�û�н���ֵʵ��д�����ñ�����
 *              �ݴ������ֵ��ֻ�е��û����� GxBus_ConfigGroupSave()�ӿ�ʱ���Ż�
 *              ������������������Ƿ񽫻���ı�����ֵд�����ñ�
 *              �û�������ͬһ���������� GxBus_ConfigGroupSet()�ӿ�����һ�����
 *              ��������ֵ���ӿڽ�����ʱ������Щ������ֵ��ֱ���û�����
 *              GxBus_ConfigGroupClose()�ӿ�ʱ�Ż�����Ƿ񽫻������Щ����ֵд��
 *              ���ñ�
 */
handle_t GxBus_ConfigGroupOpen(void);

/**
 * @brief       �ر����ñ���
 * @param [in]  group       ����
 * @return      int32_t     EINPUT,�����������
                            GXCONFIG_OK,ִ�гɹ�
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupSet
                ::GxBus_ConfigGroupIsChanged
 * @remarks     �ر����ñ���ʱ,�����ͷ������Դ;�����������еı���ֵ�������ñ�
                �����ȵ���GxBus_ConfigGroupSave()�ӿ�.���򽫻�����б���ֵ�ĸı�
                ����
 */
int32_t GxBus_ConfigGroupClose(handle_t group);

/**
 * @brief       �洢���ñ����б�����ֵ�����ñ�
 * @param [in]  group       ����
 * @see
 * @remarks     �����������еı���ֵд�����ñ�
 */
int32_t GxBus_ConfigGroupSave(handle_t group);

/**
 * @brief       ��ȡ�������ֵ
 * @param       group           ����
 * @param       key             ������ʶ�ַ���
 * @param       buf             �洢���壬������ִ�гɹ�ʱ����ֵΪkey���ַ���ֵ
 * @param       buf_size        �洢�����С
 * @param       dvalue          key������Ĭ���ַ���ֵ
 * @return      char*           NULL,�����������
 *                              ����ֵ����ʾִ�гɹ�������bufָ�룬��������ֵ���ʽ
 * @see
 * @remarks     ��ȡ�������ֵʱ,���������֮��,�������ֿ���:������������ֵû
 *              �����鷽ʽ���øı��,���ȡ��ֵ�����ñ��е�ֵ,�������������ù�
 *              GxBus_ConfigGroupSet()�ӿڸı��,���ȡ�������л����ֵ
 */
char *GxBus_ConfigGroupGet(handle_t group, const char *key, char *buf, size_t buf_size, const char *dvalue);

/**
 * @brief       ��ȡ�������ֵ
 * @param       group           ����
 * @param       key             ������ʶ�ַ���
 * @param       buf             �洢���壬������ִ�гɹ�ʱ����ֵΪkey������ֵ
 * @param       dvalue          key������Ĭ���ַ���ֵ
 * @return      int32_t*        NULL,�����������
 *                              ����ֵ����ʾִ�гɹ�������bufָ�룬��������ֵ���ʽ
 * @see
 * @remarks     ��ȡ�������ֵʱ,���������֮��,�������ֿ���:������������ֵû
 *              �����鷽ʽ���øı��,���ȡ��ֵ�����ñ��е�ֵ,�������������ù�
 *              GxBus_ConfigGroupSet()�ӿڸı��,���ȡ�������л����ֵ
 */
int32_t *GxBus_ConfigGroupGetInt(handle_t group, const char *key, int32_t *buf, int32_t dvalue);

/**
 * @brief       ��ȡ�������ֵ
 * @param       group           ����
 * @param       key             ������ʶ�ַ���
 * @param       buf             �洢���壬������ִ�гɹ�ʱ����ֵΪkey��˫������ֵ
 * @param       dvalue          key������Ĭ���ַ���ֵ
 * @return      double*         NULL,�����������
 *                              ����ֵ����ʾִ�гɹ�������bufָ�룬��������ֵ���ʽ
 * @see
 * @remarks     ��ȡ�������ֵʱ,���������֮��,�������ֿ���:������������ֵû
 *              �����鷽ʽ���øı��,���ȡ��ֵ�����ñ��е�ֵ,�������������ù�
 *              GxBus_ConfigGroupSet()�ӿڸı��,���ȡ�������л����ֵ
 */
double *GxBus_ConfigGroupGetDouble(handle_t group, const char *key, double *buf, double dvalue);

/**
 * @brief       ����ķ�ʽ����key��ʶ�ı���ֵ
 * @param [in]  group       ����
 * @param [in]  key         ������ʶ�ַ���
 * @param [in]  value       key�������ַ���ֵ
 * @return      int32_t     GXCONFIG_OK,���óɹ�
 *                          EINPUT, �����������
 *                          GXCONFIG_FAILURE,����ʧ��
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     ���ñ��ӿ����ñ�����ֵʱ,��û�н�����ֵ���������ñ�,���ǽ�ֵ����
 *              ����,ֻ�е���GxBus_ConfigGroupClose()ʱ�Ż�ʵ�����������ñ�
 */
int32_t GxBus_ConfigGroupSet(handle_t group, const char *key, const char *value);

/**
 * @brief       ����ķ�ʽ����key��ʶ�ı���ֵ
 * @param [in]  group       ����
 * @param [in]  key         ������ʶ�ַ���
 * @param [in]  value       key����������ֵ
 * @return      int32_t     GXCONFIG_OK,���óɹ�
 *                          EINPUT, �����������
 *                          GXCONFIG_FAILURE,����ʧ��
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     ���ñ��ӿ����ñ�����ֵʱ,��û�н�����ֵ���������ñ�,���ǽ�ֵ����
 *              ����,ֻ�е���GxBus_ConfigGroupClose()ʱ�Ż�ʵ�����������ñ�
 */
int32_t GxBus_ConfigGroupSetInt(handle_t group, const char *key, int32_t value);

/**
 * @brief       ����ķ�ʽ����key��ʶ�ı���ֵ
 * @param [in]  group       ����
 * @param [in]  key         ������ʶ�ַ���
 * @param [in]  value       key������˫������ֵ
 * @return      int32_t     GXCONFIG_OK,���óɹ�
 *                          EINPUT, �����������
 *                          GXCONFIG_FAILURE,����ʧ��
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupIsChanged
 * @remarks     ���ñ��ӿ����ñ�����ֵʱ,��û�н�����ֵ���������ñ�,���ǽ�ֵ����
 *              ����,ֻ�е���GxBus_ConfigGroupClose()ʱ�Ż�ʵ�����������ñ�
 */
int32_t GxBus_ConfigGroupSetDouble(handle_t group, const char *key, double value);

/**
 * @brief       ��ѯ���еı���ֵ�Ƿ��иı�
 * @param       group       ����
 * @return      bool        TRUE,���еı���ֵ�Ѿ��ı�
 *                          FALSE,���еı���ֵû�иı�
 * @see         ::GxBus_ConfigGroupOpen ::GxBus_ConfigGroupClose
 *              ::GxBus_ConfigGroupSet
 * @remarks
 */
bool GxBus_ConfigGroupIsChanged(handle_t group);

__END_DECLS

#endif

