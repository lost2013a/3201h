/**
 *
 * @file        app_common_porting_ca_flash.h
 * @brief
 * @version     1.1.0
 * @date        11/30/2012 09:30:49 AM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_PORTING_CA_FLASH_H__
#define __APP_COMMON_PORTING_CA_FLASH_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <gxtype.h>

/*
* ��ʼ��ca flash, �����С
* type --CA���ͣ����ݶ�CAϵͳ
*/
void app_porting_ca_flash_init(uint32_t size);

/*
* ��FLASH�ж�ȡCA ����
* type --CA���ͣ����ݶ�CAϵͳ
*/
uint8_t app_porting_ca_flash_read_data(uint32_t Offset,uint8_t *pbyData,uint32_t *pdwLen);

/*
* CA����д��FLASH
*/
uint8_t app_porting_ca_flash_write_data(uint32_t Offset,uint8_t *pbyData,uint32_t dwLen);

/*
* ����FLASH
*/
uint8_t app_porting_ca_flash_erase(uint32_t Offset,uint32_t dwLen);

/*
* ɾ��CA��ֲ�ļ�
*/
uint8_t app_porting_ca_flash_file_delete(int32_t dvb_ca_flag);


void app_porting_ca_flash_sem_create(void);

void app_porting_ca_flash_sem_wait(void);

void app_porting_ca_flash_sem_post(void);

#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_PORTING_CA_FLASH_H__*/

