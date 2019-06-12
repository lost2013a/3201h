#ifndef __APP_COMMON_OTP_H__
#define __APP_COMMON_OTP_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <gxtype.h>

int app_otp_read(uint32_t start_addr,uint8_t *buf,uint32_t size);
int app_otp_write(uint32_t start_addr,uint8_t *buf,uint32_t size);
int app_otp_get_chip_id(uint8_t *buf,uint32_t size);
int app_otp_get_licence_id(uint8_t *buf,uint32_t size);

#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_OTP_H__*/

