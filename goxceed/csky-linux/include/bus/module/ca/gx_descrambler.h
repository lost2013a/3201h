/**
 * @file gxca_descrambler.h
 * @author lixb
 * @brief CAS系统解挠抽象模块
 * @addtogroup ca_module
 */
 /*@{*/
#ifndef __GX_CA_DESCRAMBLER_H__
#define __GX_CA_DESCRAMBLER_H__


#include <gxtype.h>
#include "gxcore.h"
#include "gxcas.h"

__BEGIN_DECLS

/**
* @brief    open a descrambler and return the handle
* @param []	DemuxID :demux id .0~1 is valid
* @return   handle == E_INVALID_HANDLE failure;or sucess
*/
handle_t GxDescrmb_Open(uint32_t  DemuxID);

/**
* @brief    close a descrambler release resourse
* @param []	Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @return   int  >= 0, sucess.<0 failure
*/
int32_t GxDescrmb_Close(handle_t Descrambler);

/**
* @brief    tell descrambler that which pid channel need to bind. the pid will used to find the
		    id of slot,then descrambler can descramble the stream.
* @param []	Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param []	StreamPID :The pid of stream;
* @return   int  >= 0, sucess.<0 failure
*/
int32_t GxDescrmb_SetStreamPID(handle_t Descrambler, uint16_t  StreamPID);

/**
* @brief        Send odd key to descrambler.
* @param []	    Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param [in]   OddKey :buffer of odd key
* @param []     KeyLen :length of key
 * @return      int  >= 0, sucess.<0 failure
*/
int32_t GxDescrmb_SetOddKey(  handle_t Descrambler, IN const uint8_t* OddKey, size_t KeyLen );

/**
* @brief        Send even key to descrambler.
* @param []	    Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param [in]   EvenKey :buffer of even key
* @param []     KeyLen :length of key
 * @return      int  >= 0, sucess.<0 failure
*/
int32_t GxDescrmb_SetEvenKey( handle_t Descrambler, IN const uint8_t*  EvenKey, size_t KeyLen );


/**
* @brief        Send cw (odd key & even key) to descrambler.
* @param []	    Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param [in]   OddKey :buffer of odd key
* @param [in]   EvenKey :buffer of even key
* @param []     KeyLen :length of key
* @return       int  >= 0, sucess.<0 failure
* @note		we sugest to use this interface, user can save even key or odd key ,and send them to
			descrambler together.
*/
int32_t GxDescrmb_SetCW(handle_t Descrambler,
                                const uint8_t* OddKey,
                                const uint8_t* EvenKey,
                                size_t KeyLen );

int32_t GxDescrmb_GetCW(handle_t Descrambler,
                                uint8_t* OddKey,
                                uint8_t* EvenKey);
/**
* @brief        Send cw (odd key & even key) to descrambler.It is provide to mtc high level encryption system specially.
* @param []	    Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param [in]   EcwEven :buffer of even key
* @param [in]   EcwOdd :buffer of odd key
* @param [in]   Eck :buffer of eck
* @param []     EcwEvenLen :length of key
* @param []     EcwOddLen :length of key
* @param []     EckLen :length of key
* @param []     arith_mode :mode
* @param []     arith_type :type
* @return       int  >= 0, sucess.<0 failure
* @note		    we sugest to use this interface, user can save even key or odd key ,and send them to
			    descrambler together.
*/
int32_t GxDescrmb_SetECW(handle_t Descrambler,
								uint16_t pid,
                                IN const uint8_t* EcwEven,
                                size_t EcwEvenLen,
                                IN const uint8_t* EcwOdd,
                                size_t EcwOddLen,
                                IN const uint8_t* Eck,
                                size_t EckLen,
                                enum mtc_arith_type arith_type,
                                enum mtc_arith_mode arith_mode);

/**
* @brief        Send  even key to descrambler.It is provide to mtc high level encryption system specially.
* @param []	    Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param [in]   EcwEven :buffer of even key
* @param [in]   Eck :buffer of eck
* @param []     EcwEvenLen :length of key
* @param []     EckLen :length of key
* @param []     arith_mode :mode
* @param []     arith_type :type
* @return       int  >= 0, sucess.<0 failure
*/
int32_t GxDescrmb_SetEvenECW(handle_t Descrambler,
                                IN const uint8_t* EcwEven,
                                size_t EcwEvenLen,
                                IN const uint8_t* Eck,
                                size_t EckLen,
                                enum mtc_arith_type arith_type,
                                enum mtc_arith_mode arith_mode);

/**
* @brief        Send  even key to descrambler.It is provide to mtc high level encryption system specially.
* @param []	    Descrambler :handle of descrambler,get via GxDescrmb_Open();
* @param [in]   EcwEven :buffer of odd key
* @param [in]   Eck :buffer of eck
* @param []     EcwEvenLen :length of key
* @param []     EckLen :length of key
* @param []     arith_mode :mode
* @param []     arith_type :type
* @return       int  >= 0, sucess.<0 failure
*/
int32_t GxDescrmb_SetOddECW(handle_t Descrambler,
                                const uint8_t* EcwOdd,
                                size_t EcwOddLen,
                                const uint8_t* Eck,
                                size_t EckLen,
                                enum mtc_arith_type arith_type,
                                enum mtc_arith_mode arith_mode);


/** 以下接口用于统一设置多个解扰器为同一个CW，基于上述接口实现
 *  主要用于博尚方案。以下接口另成一套，不建议于上述基本接口同时使用*/
int32_t GxDescrmb_AddPid(uint16_t pid);

int32_t GxDescrmb_DelPid(uint16_t pid);

int32_t GxDescrmb_SetAllPidECW( IN const uint8_t* EcwEven,
                                size_t EcwEvenLen,
                                IN const uint8_t* EcwOdd,
                                size_t EcwOddLen,
                                IN const uint8_t* Eck,
                                size_t EckLen,
                                enum mtc_arith_type arith_type,
                                enum mtc_arith_mode arith_mode);

int32_t GxDescrmb_Handle2Id(handle_t des);

__END_DECLS

#endif
/*@}*/
