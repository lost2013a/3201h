/**
 * @file gxca_nvram.h
 * @author zhangsy
 * @brief CAS系统非易失性存储抽象模块
 * @addtogroup ca_module
 */
 /*@{*/
#ifndef __GXCA_NVRAM_H__
#define __GXCA_NVRAM_H__

#include "gxtype.h"
#include "gxcore.h"
#include "gxcas.h"

__BEGIN_DECLS


/**
* @brier	    open one nvram memory
* @param[in]	name :file name that U want to use
* @param[]	    size :file size, it will be record in control blocks.
* @return       handle == E_INVALID_HANDLE failure;or sucess
* @note		    if u call this function by param "name" first time, it will creat a file, or it just
			    creat a control block and copy file's name(is created in the first call!)to block.
*/
handle_t GxNvram_Open(IN const char* name,size_t size);

/**
* @brief	    read memory
* @param[]	    nvram :handle of nvram, get via GxNvram_Open();
* @param[]	    Offset :offset of memory.
* @param[out]   Buf :buffer to save data.
* @param[]	    BufSize :bytes to read.
* @return      size_t: bytes number that have read.
*/
size_t GxNvram_Read(handle_t nvram,uint32_t  Offset, OUT uint8_t* Buf, size_t BufSize);

/**
* @brief	    write memory
* @param[]	    nvram :handle of nvram, get via GxNvram_Open();
* @param[]	    Offset :offset of memory.
* @param[in]    Data :buffer to save data.
* @param[]	    DataSize :bytes to write.
* @return       size_t: bytes number that have write.
*/
size_t GxNvram_Write(handle_t nvram,uint32_t Offset, const uint8_t* Data, size_t DataSize);


/**
* @brief	clean memory
* @param[]	nvram :handle of nvram, get via GxNvram_Open();
* @param[]	Offset :offset of memory.
* @param[]	Len :bytes to clean.
* @return   int  >= 0, sucess return clean size.<0 failure
* @note		value 0xff
*/
int GxNvram_Clean(handle_t nvram,uint32_t Offset, size_t Len);


/**
* @brief	close one nvram memory
* @param[]	nvram :handle of nvram, get via GxNvram_Open();
* @return   int  >= 0, sucess return clean size.<0 failure
*/
int GxNvram_Close(handle_t nvram);

__END_DECLS

#endif
/*@}*/
