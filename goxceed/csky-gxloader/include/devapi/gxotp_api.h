#ifndef _GXOTP_API_
#define _GXOTP_API_

int GxOtp_Write(uint32_t start_addr, uint8_t *buf, uint32_t size);
int GxOtp_Read(uint32_t start_addr, uint8_t *buf, uint32_t size);

#endif
