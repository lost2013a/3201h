/**
 * @file gxca_descrambler.h
 * @author lixb
 * @brief CAS系统解挠抽象模块
 * @addtogroup ca_module
 */
/*@{*/
#ifndef __GX_CA_DESCRAMBLER_H__
#define __GX_CA_DESCRAMBLER_H__


#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

#define MAX_DESCRAMBLER_NUM                 (8)

/**
 * @brief       打开解挠器
 * @param [in]  DemuxID        Demux设备号
 * @return      handle_t                解挠器句柄
 * @see ::GxCA_DescramblerClose
 */
handle_t    GxCA_DescramblerOpen            (uint32_t       DemuxID);
/**
 * @brief       关闭解挠器
 * @param [in]  Descrambler    解挠器句柄
 * @return      bool 关闭成功返回TRUE, 关闭失败返回FALSE
 * @see ::GxCA_DescramblerOpen
 */
bool        GxCA_DescramblerClose           (handle_t Descrambler);
/**
 * @brief       设置解挠器的PID
 * @param [in]  Descrambler    解挠器句柄
 * @param [in]  PID            被加挠流的PID
 * @return      bool 设置成功返回TRUE, 设置失败返回FALSE
 * @see
 */
bool        GxCA_DescramblerSetStreamPID(handle_t Descrambler, uint16_t PID);
int16_t     GxCA_DescramblerGetStreamPid(handle_t Descrambler);
bool        GxCA_DescramblerSetEcmPID   (handle_t Descrambler, uint16_t  EcmPID);
int16_t     GxCA_DescramblerGetEcmPid   (handle_t Descrambler);

/*not support*/
#if 1
/**
 * @brief       设置奇密钥到解挠器
 * @param [in]  Descrambler    解挠器句柄
 * @param [in]  OddKey         奇密钥
 * @param [in]  KeyLen           密钥长度
 * @return      bool 设置成功返回TRUE,设置失败返回FALSE
 * @see
 */
bool        GxCA_DescramblerSetOddKey(handle_t Descrambler, uint8_t *OddKey, size_t KeyLen);
/**
 * @brief       设置偶密钥到解挠器
 * @param [in]  Descrambler    解挠器句柄
 * @param [in]  EvenKey        偶密钥
 * @param [in]  KeyLen           密钥长度
 * @return      bool 设置成功返回TRUE,设置失败返回FALSE
 * @see
 */
bool        GxCA_DescramblerSetEvenKey(handle_t Descrambler, uint8_t *EvenKey, size_t KeyLen);
#endif

/**
 * @brief       设置密钥
 * @param [in]  DemuxID         Demux设备号
 * @param [in]  StreamPID       被加密流的PID
 * @param [in]  OddKey          奇密钥
 * @param [in]  EvenKey         偶密钥
 * @param [in]  KeyLen           密钥长度
 * @remark      GxCA_DescramblerSetCW与其它函数不同,在这个函数,并不显式调用
 打开解挠器函数,由本函数内部完成解挠器的管理工作.
 * @return
 * @see ::GxCA_DescramblerGetByPid
 */
void        GxCA_DescramblerSetCW(handle_t Descrambler,
		const uint8_t*  OddKey,
		const uint8_t*  EvenKey,
		size_t          KeyLen);
/**
 * @brief       设置ecw
 * @param [in]  DemuxID         Demux设备号
 * @param [in]  EcwEven        被加密流的even ecw
 * @param [in]  EcwEvenLen       even Ecw的长度
 * @param [in]  EcwOdd        被加密流的odd ecw
 * @param [in]  EcwOddLen       odd Ecw的长度
 * @param [in]  Eck          被加密的ck
 * @param [in]  EcwLen         Ecw的长度
 * @param [in]  EckLen          Eck的长度
 * @param [in]  arith_type      加密类型
 * @param [in]  arith_mode       加密模式
 * @remark
 * @return
 * @see
 */
void GxCA_DescramblerSetECW(handle_t Descrambler,
		const uint8_t* EcwEven,
		size_t EcwEvenLen,
		const uint8_t* EcwOdd,
		size_t EcwOddLen,
		const uint8_t* Eck,
		size_t EckLen,
		enum mtc_arith_type arith_type,
		enum mtc_arith_mode arith_mode);


/**
 * @brief       设置ecw
 * @param [in]  DemuxID         Demux设备号
 * @param [in]  EcwOdd        被加密流的odd ecw
 * @param [in]  EcwOddLen       odd Ecw的长度
 * @param [in]  Eck          被加密的ck
 * @param [in]  EcwLen         Ecw的长度
 * @param [in]  EckLen          Eck的长度
 * @param [in]  arith_type      加密类型
 * @param [in]  arith_mode       加密模式
 * @remark
 * @return
 * @see
 */
void GxCA_DescramblerSetOddECW(handle_t Descrambler,
		const uint8_t* EcwOdd,
		size_t EcwOddLen,
		const uint8_t* Eck,
		size_t EckLen,
		enum mtc_arith_type arith_type,
		enum mtc_arith_mode arith_mode);
/**
 * @brief       设置even ecw
 * @param [in]  DemuxID         Demux设备号
 * @param [in]  EcwEven       被加密流的even ecw
 * @param [in]  EcwOddLen       even Ecw的长度
 * @param [in]  Eck          被加密的ck
 * @param [in]  EcwLen         Ecw的长度
 * @param [in]  EckLen          Eck的长度
 * @param [in]  arith_type      加密类型
 * @param [in]  arith_mode       加密模式
 * @remark
 * @return
 * @see
 */
void GxCA_DescramblerSetOddECW(handle_t Descrambler,
		const uint8_t* EcwEven,
		size_t EcwEvenLen,
		const uint8_t* Eck,
		size_t EckLen,
		enum mtc_arith_type arith_type,
		enum mtc_arith_mode arith_mode);
/**
 * @brief       通过PID获取解挠器句柄
 * @param [in]  DemuxID        Demux设备号
 * @param [in]  StreamPID      被加密流的PID
 * @return
 * @see ::GxCA_DescramblerSetCW
 */
handle_t    GxCA_DescramblerGetByStreamPid(uint16_t StreamPID);

int         GxCA_DescramblerGetByEcmPid(uint16_t EcmPID, handle_t *Buf, size_t num);

__END_DECLS

#endif
/*@}*/
