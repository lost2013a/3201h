/*
 * =====================================================================================
 *
 *       Filename:  app_update.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011��09��20�� 14ʱ18��15��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */

#ifndef __APP_UPDATE_H__
#define __APP_UPDATE_H__


#define APP_UPDATE_SERIAL_DEVICE_NAME "/dev/ser0"
#define APP_UPDATE_FLASH_DEVICE_NAME "/dev/flash/0/0"

int32_t  SerialUpdate(void);

#endif

