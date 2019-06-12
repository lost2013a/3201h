/**
 * @file gxca_descrambler.h
 * @author lixb
 * @brief CASϵͳ���ӳ���ģ��
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
 * @brief       �򿪽�����
 * @param [in]  DemuxID        Demux�豸��
 * @return      handle_t                ���������
 * @see ::GxCA_DescramblerClose
 */
handle_t    GxCA_DescramblerOpen            (uint32_t       DemuxID);
/**
 * @brief       �رս�����
 * @param [in]  Descrambler    ���������
 * @return      bool �رճɹ�����TRUE, �ر�ʧ�ܷ���FALSE
 * @see ::GxCA_DescramblerOpen
 */
bool        GxCA_DescramblerClose           (handle_t Descrambler);
/**
 * @brief       ���ý�������PID
 * @param [in]  Descrambler    ���������
 * @param [in]  PID            ����������PID
 * @return      bool ���óɹ�����TRUE, ����ʧ�ܷ���FALSE
 * @see
 */
bool        GxCA_DescramblerSetStreamPID(handle_t Descrambler, uint16_t PID);
int16_t     GxCA_DescramblerGetStreamPid(handle_t Descrambler);
bool        GxCA_DescramblerSetEcmPID   (handle_t Descrambler, uint16_t  EcmPID);
int16_t     GxCA_DescramblerGetEcmPid   (handle_t Descrambler);

/*not support*/
#if 1
/**
 * @brief       ��������Կ��������
 * @param [in]  Descrambler    ���������
 * @param [in]  OddKey         ����Կ
 * @param [in]  KeyLen           ��Կ����
 * @return      bool ���óɹ�����TRUE,����ʧ�ܷ���FALSE
 * @see
 */
bool        GxCA_DescramblerSetOddKey(handle_t Descrambler, uint8_t *OddKey, size_t KeyLen);
/**
 * @brief       ����ż��Կ��������
 * @param [in]  Descrambler    ���������
 * @param [in]  EvenKey        ż��Կ
 * @param [in]  KeyLen           ��Կ����
 * @return      bool ���óɹ�����TRUE,����ʧ�ܷ���FALSE
 * @see
 */
bool        GxCA_DescramblerSetEvenKey(handle_t Descrambler, uint8_t *EvenKey, size_t KeyLen);
#endif

/**
 * @brief       ������Կ
 * @param [in]  DemuxID         Demux�豸��
 * @param [in]  StreamPID       ����������PID
 * @param [in]  OddKey          ����Կ
 * @param [in]  EvenKey         ż��Կ
 * @param [in]  KeyLen           ��Կ����
 * @remark      GxCA_DescramblerSetCW������������ͬ,���������,������ʽ����
 �򿪽���������,�ɱ������ڲ���ɽ������Ĺ�����.
 * @return
 * @see ::GxCA_DescramblerGetByPid
 */
void        GxCA_DescramblerSetCW(handle_t Descrambler,
		const uint8_t*  OddKey,
		const uint8_t*  EvenKey,
		size_t          KeyLen);
/**
 * @brief       ����ecw
 * @param [in]  DemuxID         Demux�豸��
 * @param [in]  EcwEven        ����������even ecw
 * @param [in]  EcwEvenLen       even Ecw�ĳ���
 * @param [in]  EcwOdd        ����������odd ecw
 * @param [in]  EcwOddLen       odd Ecw�ĳ���
 * @param [in]  Eck          �����ܵ�ck
 * @param [in]  EcwLen         Ecw�ĳ���
 * @param [in]  EckLen          Eck�ĳ���
 * @param [in]  arith_type      ��������
 * @param [in]  arith_mode       ����ģʽ
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
 * @brief       ����ecw
 * @param [in]  DemuxID         Demux�豸��
 * @param [in]  EcwOdd        ����������odd ecw
 * @param [in]  EcwOddLen       odd Ecw�ĳ���
 * @param [in]  Eck          �����ܵ�ck
 * @param [in]  EcwLen         Ecw�ĳ���
 * @param [in]  EckLen          Eck�ĳ���
 * @param [in]  arith_type      ��������
 * @param [in]  arith_mode       ����ģʽ
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
 * @brief       ����even ecw
 * @param [in]  DemuxID         Demux�豸��
 * @param [in]  EcwEven       ����������even ecw
 * @param [in]  EcwOddLen       even Ecw�ĳ���
 * @param [in]  Eck          �����ܵ�ck
 * @param [in]  EcwLen         Ecw�ĳ���
 * @param [in]  EckLen          Eck�ĳ���
 * @param [in]  arith_type      ��������
 * @param [in]  arith_mode       ����ģʽ
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
 * @brief       ͨ��PID��ȡ���������
 * @param [in]  DemuxID        Demux�豸��
 * @param [in]  StreamPID      ����������PID
 * @return
 * @see ::GxCA_DescramblerSetCW
 */
handle_t    GxCA_DescramblerGetByStreamPid(uint16_t StreamPID);

int         GxCA_DescramblerGetByEcmPid(uint16_t EcmPID, handle_t *Buf, size_t num);

__END_DECLS

#endif
/*@}*/
