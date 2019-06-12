#ifndef __GXEEPROM_API_H__
#define __GXEEPROM_API_H__
int GxEeprom_Write(unsigned int busnum, unsigned int eeprom_addr,
					void *buff, unsigned int write_addr, unsigned int count);
int GxEeprom_Read(unsigned int busnum, unsigned int eeprom_addr,
					void *buff, unsigned int read_addr, unsigned int count);
int GxEeprom_GetSize(unsigned int busnum, unsigned int eeprom_addr);
#endif
