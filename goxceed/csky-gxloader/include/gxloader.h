/*
 * =====================================================================================
 *
 *       Filename:  gxloader.h
 *
 *    Description:  support gxloader.h as include file only for libgxloader.a, gxloader 
 *			can't use this include file.
 *
 *        Created:  05/24/2011 09:56:10 AM
 *       Compiler:  gcc
 *
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */
#ifndef __BOOTLOADER_GXFLASH_H
#define __BOOTLOADER_GXFLASH_H

/* ATE operation entry function*/
void gxate_entry(void);
int gxate_get_videomem(unsigned int *addr, unsigned int *size);

/* common tools operation function*/
unsigned int crc32(unsigned int crc, const char *buf, unsigned int len);

/* gxflash operation function*/

int  gxflash_readdata(unsigned int addr, unsigned char *data, unsigned int len);
void gxflash_chiperase (void);
void gxflash_erasedata(unsigned int addr, unsigned int len);
int  gxflash_pageprogram(unsigned int addr, unsigned char *data, unsigned int len);
void gxflash_test(int argc, char *argv[]);
void gxflash_calcblockrange(unsigned int addr, unsigned int len,
		unsigned int *pstart, unsigned int *pend);
int  gxflash_badinfo(void);
int  gxflash_pageprogram_yaffs2(unsigned int addr, unsigned char *data,
		unsigned int len);
int  gxflash_readoob(unsigned int addr, unsigned char *data, unsigned int len);
int  gxflash_writeoob(unsigned int addr, unsigned char *data, unsigned int len);
unsigned int  gxflash_getsize(void);
int  gxflash_write_protect_mode(void);
int  gxflash_write_protect_status(void);
int  gxflash_write_protect_lock(unsigned long addr);
int  gxflash_write_protect_unlock(void);

void udelay(unsigned int usec);
void mdelay(unsigned int msec);

/* i2c operation function*/
void *gx_i2c_open(unsigned int id);
int gx_i2c_set(void *dev, unsigned int busid, unsigned int chip_addr, 
		unsigned int address_width, int send_noack, int send_stop);
int gx_i2c_tx(void *dev, unsigned int reg_address, 
		const unsigned char *tx_data, unsigned int count);
int gx_i2c_rx(void *dev, unsigned int reg_address, unsigned char *rx_data,
		unsigned int count);
int gx_i2c_close(void *dev);

/* irr operation function*/
int irr_read(void *buffer, int *len);

/* uart operation function*/
int printf(const char *fmt, ...);
int sprintf(char * buf, const char *fmt, ...)
	__attribute__ ((format (__printf__, 2, 3)));

/* irq */
typedef int (*irq_handler_t) (int irq, void *pdata);
void gx_request_irq(int irq, irq_handler_t handler, void *pdata);

/* ota zlib mode */
struct compress_bin_info;
int get_compress_bin_info(char *buf, unsigned int len, struct compress_bin_info *compress_info);
int uncompress_section(unsigned char* src_buf, unsigned int src_len,
							unsigned char *dst_buf, unsigned int *dst_len);

#define printk	printf

#endif

