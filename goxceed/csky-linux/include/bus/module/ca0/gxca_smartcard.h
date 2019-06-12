/*@{*/
#ifndef __GXCA_SMARTCARD_H__
#define __GXCA_SMARTCARD_H__

#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS


/**���ܿ�ͨѶЭ��*/
typedef enum {
	GXCA_SMART_T0_PROTOCOL,
	GXCA_SMART_T1_PROTOCOL
} GxCA_SmartProtocol;

/**���ܿ�VCC��ƽ*/
typedef enum {
	GXCA_SMART_VCC_HIGH_LEVEL,
	GXCA_SMART_VCC_LOW_LEVEL
} GxCA_SmartVccPol;

/**���ܿ�ͨѶֹͣλ*/
typedef enum {
	GXCA_SMART_STOPLEN_0BIT,
	GXCA_SMART_STOPLEN_1BIT,
	GXCA_SMART_STOPLEN_1D5BIT,
	GXCA_SMART_STOPLEN_2BIT
} GxCA_SmartStopLen;

/**���ܿ�������ƽ*/
typedef enum {
	GXCA_SMART_DETECT_LOW_LEVEL       = 0,
	GXCA_SMART_DETECT_HIGH_LEVEL      = 1
} GxCA_SmartDetectPol;

/**���ܿ�ͨѶ���ݷ�ת*/
typedef enum {
	GXCA_SMART_DATA_CONV_DIRECT       = 0,
	GXCA_SMART_DATA_CONV_INVERSE      = 1
} GxCA_SmartDataConv;

/**���ܿ�ͨѶУ��*/
typedef enum {
	GXCA_SMART_PARITY_EVEN            = 0,
	GXCA_SMART_PARITY_ODD             = 1
} GxCA_SmartParityType;

/**���ܿ�״̬*/
typedef enum {
	GXCA_SMART_CARD_INIT              = 0,
	GXCA_SMART_CARD_IN                = 1,
	GXCA_SMART_CARD_OUT               = 2
} GxCA_SmartCardStatus;

/**���ܿ��ӿ�ͨѶʱ�����*/
typedef struct {
	uint32_t                baud_rate;
	uint32_t                etu;
	uint32_t                egt;
	uint32_t                tgt;
	uint32_t                wdt;
	uint32_t                twdt;
} GxCA_SmartTimeParams;

typedef void (*GxCA_SmartCardNotify)(handle_t handle, GxCA_SmartCardStatus status);

typedef struct {
	GxCA_SmartProtocol      protocol;
	GxCA_SmartStopLen       stop_len;
	GxCA_SmartDataConv      io_conv;
	GxCA_SmartParityType    parity;
	GxCA_SmartVccPol        vcc_pole;
	GxCA_SmartDetectPol     detect_pole;
	GxCA_SmartCardNotify    notify_callback;
} GxCA_SmartParams;



/**
 * @brief       ���ܿ���ʼ������
 * @param [in]  name                    ���ܿ��豸��
 * @param [in]  sc_notify               ���ܿ�״̬֪ͨ����ָ��
 * @return      handle_t ���ܿ����
 */
handle_t GxCA_SmartcardOpen      (const char *name, GxCA_SmartParams *param);
int      GxCA_SmartcardGetStatus (handle_t   handle);


/**
 * @brief       ���ܿ���λ����
 * @param [in]   handle     ���ܿ����
 * @param [out]  AtrBuf    ATR����
 * @param [out]  BufSize     ATR�����С
 * @return  int  ATR��ȡ�ɹ�,����ATR����
 */
int GxCA_SmartcardReset(handle_t handle, uint8_t *AtrBuf, size_t BufSize);

/**
 * @brief       ���ܿ�ʱ���������
 * @param [in]   handle     ���ܿ����
 * @param [in]  time    ���ܿ�ʱ�����
 * @return  int ATR��ȡ�ɹ�,����0,����ֵʧ��
 */
int GxCA_SmartcardConfig(handle_t handle, const GxCA_SmartTimeParams *time);

/**
 * @brief       ���ܿ����������
 * @param [in]  handle     ���ܿ����
 * @param [in]  Cmd  ���ܿ�����ָ��
 * @param [in]  CmdLen       ���ܿ������
 * @return  int ����ͳɹ�,���ط����ֽ���
 */
int GxCA_SmartcardSendCmd(handle_t handle, const uint8_t *Cmd, size_t CmdLen);

/**
 * @brief       ��ȡ���ܿ���Ӧ
 * @param [in]  handle      ���ܿ����
 * @param [out] Reply       ���ܿ���Ӧ����
 * @param [out] ReplyLen    ���ܿ���Ӧ���Ȼ���
 * @return bool ��Ӧ��ȡ�ɹ�����TRUE,ʧ�ܷ���FALSE
 */
int GxCA_SmartcardGetReply(handle_t handle, uint8_t *ReplyBuf, size_t BufSize);

/**
 * @brief       �ر����ܿ�
 * @param [in]  handle     ���ܿ����
 * @return  bool �رճɹ�����TRUE,ʧ�ܷ���FALSE
 */
bool GxCA_SmartcardClose(handle_t handle);

__END_DECLS

#endif
/*@}*/
