/**
 * @file gx_smartcard.h
 * @author lixb
 * @brief CASϵͳ���ܿ�����ģ��
 * @asstogroup ca_module
 */
/*@{*/
#ifndef __GXCA_SMARTCARD_H__
#define __GXCA_SMARTCARD_H__

#include "gxtype.h"
#include "gxcore.h"
#include "gxcas.h"

__BEGIN_DECLS


/*ѡ��ڼ�·sci������,��ЩоƬ֧��2·sci*/
typedef enum {
	__GXSMART_SCI1 = 0,
	__GXSMART_SCI2
} GxSmcSelect;


/**���ܿ�ͨѶ�ط�Э��*/
typedef enum {
	/*У�����ʱ�ط�һ���ֽ�,����ÿ�ν�������෢һ��Ӧ��λ(T0)*/
	ENABLE_REPEAT_WHEN_ERR,
	/*У�����ʱҲ���ط�,һ�㽨��ʹ�ô�ģʽ(T1)*/
	DISABLE_REPEAT_WHEN_ERR
} GxSmcRepeat_t;

/**���ܿ�VCC��ƽ*/
typedef enum {
	GXSMC_VCC_HIGH_LEVEL,
	GXSMC_VCC_LOW_LEVEL
}GxSmcVccPol;

/* ��λʱ�Ƿ�ʹ��Ӳ��ʶ��ETU�����ǣ���λ����Ҫ����Ӧ���õ�ETUֵ
 * �ٽ�������*/
typedef enum {
	GXSMC_RESET_VIA_SET_ETU,
	GXSMC_RESET_VIA_AUTO_ETU,
}GxSmcAutoEtu_t;

/**���ܿ�ͨѶֹͣλ*/
typedef enum {
	GXSMC_STOPLEN_0BIT,
	GXSMC_STOPLEN_1BIT,
	GXSMC_STOPLEN_1D5BIT,
	GXSMC_STOPLEN_2BIT
}GxSmcStopLen;

/**���ܿ�������ƽ*/
typedef enum {
	GXSMC_DETECT_LOW_LEVEL       = 0,
	GXSMC_DETECT_HIGH_LEVEL      = 1
}GxSmcDetectPol;

/**���ܿ�ͨѶ���ݷ�ת*/
typedef enum {
	GXSMC_DATA_CONV_DIRECT       = 0,
	GXSMC_DATA_CONV_INVERSE      = 1
}GxSmcDataConv;

/**���ܿ�ͨѶУ��*/
typedef enum {
	GXSMC_PARITY_ODD             = 0,
	GXSMC_PARITY_EVEN            = 1
}GxSmcParityType;

/**���ܿ�״̬*/
typedef enum {
	GXSMC_CARD_INIT              = 0,
	GXSMC_CARD_IN                = 1,
	GXSMC_CARD_OUT               = 2
}GxSmcCardStatus;

/**���ܿ��ӿ�ͨѶʱ�����*/
typedef enum {
	SMCT_NONE,
	SMCT_FRE   = 0X00000001,
	SMCT_ETU   = 0X00000002,
	SMCT_EGT   = 0X00000004,
	SMCT_TGT   = 0X00000008,
	SMCT_WDT   = 0X00000010,
	SMCT_TWDT  = 0X00000020,
	SMCT_ALL   = 0X0000003F
}GxSmcTimeConfigFlags;

typedef struct {
	GxSmcTimeConfigFlags    flags;
	uint32_t                baud_rate;  /*���ܿ�����Ƶ��,����9600*372*/
	uint32_t                etu;
	uint32_t                egt;
	uint32_t                tgt;
	uint32_t                wdt;
	uint32_t                twdt;
}GxSmcTimeParams;

typedef enum {
	SMCC_NONE,
	SMCC_PROTOCOL                 = 0X00000001,
	SMCC_STOPLEN                  = 0X00000002,
	SMCC_DATACONV                 = 0X00000004,
	SMCC_PARITYTYPE               = 0X00000008,
	SMCC_TIME                     = 0X00000010,
	SMCC_AUTO_ENABLE              = 0X00000100,
	SMCC_AUTO_ETU_ENABLE          = 0X00000200,
	SMCC_AUTO_CONV_PARITY_ENABLE  = 0X00000400,
	SMCC_AUTO_DISABLE             = 0X00001000,
	SMCC_AUTO_ETU_DISABLE         = 0X00002000,
	SMCC_AUTO_CONV_PARITY_DISABLE = 0X00004000,
	SMCC_ALL                      = 0X0000001F

}GxSmcConfigFlags;

typedef struct {
	GxSmcConfigFlags flags;
	GxSmcRepeat_t    protocol;
	GxSmcStopLen     stop_len;
	GxSmcDataConv    io_conv;
	GxSmcParityType  parity;
	GxSmcTimeParams  time;
}GxSmcConfigs;


typedef struct {
#define O_BDBG  (1)   /* ��bus�ĵ�����Ϣ */
#define O_CDBG  (1<<1)  /* �������ĵ�����Ϣ */
	GxSmcRepeat_t      protocol;
	GxSmcStopLen       stop_len;
	GxSmcDataConv      io_conv;
	GxSmcParityType    parity;
	GxSmcVccPol        vcc_pole;
	GxSmcDetectPol     detect_pole;
	GxSmcSelect        sci_sel;
	GxSmcAutoEtu_t     auto_etu;//1,auto
	uint32_t           auto_parity;//1,auto
	uint32_t           default_etu;/* Ĭ��etuֵ */
	uint32_t           debug_info;
}GxSmcParams;

/**
 * @brief       ���ܿ��򿪺���
 * @param [in]  name                    ���ܿ��豸��
 * @param [in]  sc_notify               ���ܿ�״̬֪ͨ����ָ��
 * @return      handle_t ���ܿ����E_INVALID_HANDLE ִ��ʧ��
 */
handle_t GxSmc_Open(const char *name, IN GxSmcParams *param);


/**
 * @brief       ���ܿ���λ����
 *
 * @param [in]   handle    ���ܿ����
 * @param [out]  AtrBuf    ATR ����,��������С���鲻С��33�ֽ�
 * @param [in]   BufSize   ATR �����С
 * @param [out]  RetLen    ʵ�ʻ�ȡ��atr����
 *
 * @return      int >=0 ִ�гɹ�;<0 ִ��ʧ��
 */
int GxSmc_Reset(handle_t handle,OUT uint8_t* AtrBuf,size_t BufSize,OUT size_t *RetLen);


/**
 * @brief       ���ܿ�ʱ���������
 * @param [in]  handle  ���ܿ����
 * @param [in]  time    ���ܿ�ʱ�����
 * @return      int >=0 ִ�гɹ�;<0 ִ��ʧ��
 */
int GxSmc_Config(handle_t handle, IN const GxSmcTimeParams* time);

/**
 * @brief       ���ܿ����������½ӿڣ�����ʹ�ô˽ӿڴ���GxSmc_Config
 * @param [in]  handle    ���ܿ����
 * @param [in]  config    ���ܿ�����
 * @return      int >=0 ִ�гɹ�;<0 ִ��ʧ��
 */
int GxSmc_ConfigAll(handle_t handle, IN const GxSmcConfigs *config);

/**
 * @brief       ���ܿ����������
 * @param [in]  handle    ���ܿ����
 * @param [in]  Cmd       ���ܿ�����ָ��
 * @param [in]  CmdLen    ���ܿ������
 * @param [out]  SendLen  ���͸����ܿ���ʵ�ʳ���
 * @return      int ���͵��ֽ�����<0����ʧ��
 */
int GxSmc_SendCmd(handle_t handle, IN const uint8_t *Cmd, size_t CmdLen);

/**
 * * @brief       ���ܿ����������
 * * @param [in]  handle  ���ܿ����
 * * @param [in]  Cmd     ���ܿ�����ָ��
 * * @param [in]  CmdLen  ���ܿ������
 * * @param [in]  timeout ��ʱʱ��
 * * @return      int ���ط��ͳɹ����ֽ�����<0������ʧ��
 * */
int GxSmc_SendCmd_Extend(handle_t handle, IN const uint8_t* Cmd,size_t CmdLen,size_t timeout);

/**
 * @brief       ��ȡ���ܿ���Ӧ
 * @param [in]  handle    ���ܿ����
 * @param [out] ReplyBuf  ���ܿ���Ӧ����
 * @param [out] BufSize   ���ܿ���Ӧ���Ȼ���
 * @param [out] RetLen    ���ܿ���Ӧ��ʵ�ʳ���
 * @return      int ���ػ�ȡ�����ֽ����� <0���ȡʧ��
 */
int GxSmc_GetReply(handle_t handle, IN uint8_t*  ReplyBuf,size_t BufSize);
/**
 * @brief       ��ȡ���ܿ���Ӧ
 *
 * @param [in]  handle      ���ܿ����
 * @param [out] ReplyBuf    ���ܿ���Ӧ����
 * @param [out] BufSize     ���ܿ���Ӧ���Ȼ���
 * @param [in]  timeout     ��ʱʱ��
 *
 * @return      int ���ػ�ȡ�����ֽ�����<0���ȡʧ��
 */
int GxSmc_GetReply_Extend(handle_t handle, IN uint8_t* ReplyBuf, size_t BufSize,size_t timeout);

/**
 * @brief       �������ܿ�����
 *
 * @param [in]  handle    ���ܿ����
 * @param [in]  CmdLen    ����������
 * @param [in]  pCmd      ��Ҫ���������ָ��
 * @param [out] pResponse �������Ӧ����
 * @param [out] RespLen   ������ɺ󷵻ص���Ӧ����
 * @param [out] pSW1      ������ɺ󷵻ص�״̬��1
 * @param [out] pSW2      ������ɺ󷵻ص�״̬��2
 *
 * @return      int >=0 ִ�гɹ�;<0 ִ��ʧ��
 *
 * @note  �˺�������˼򵥵�apdu���ִ���,����0x61, sw1 == INS,�ȴ�
 *        �ȵ�.�൱��GxSmc_SendCmd,GxCA_SmcGetReply���������ٴ����,
 *        ʹ��ʱ�����cas���������ѡ��.
 */
int GxSmc_SendReceiveData(handle_t handle,
		size_t CmdLen,
		IN const uint8_t* pCmd,
		OUT uint8_t *pResponse,
		OUT size_t *RespLen,
		OUT uint8_t *pSW1,
		OUT uint8_t *pSW2);

/**
 * @brief       ��ȡ���ܿ�״̬
 * @param [in]  handle     ���ܿ����
 * @param [out]  state     ���ܿ�״̬
 * @return      int >=0 ִ�гɹ�;<0 ִ��ʧ��
 * @note ģ��ʹ���߱��뼰ʱ���ô˺����Ի�ȡ���ܿ�״̬
 *       �������صĲ���.��Ӧ��ʵʱ����ʹ���ߵ��ô˺���
 *       ��ʵʱ�Ծ���.
 */
int GxSmc_GetStatus (handle_t   handle,OUT GxSmcCardStatus *state);

/**
 * @brief       �������ܿ��ĸ�λӦ��
 * @param [in]  Atr_p       Ӧ������ָ��
 * @param []    AtrLength Ӧ�����ݵĳ���
 * @param [out]    etu �����Ӧ��ֵ
 * @param [out]    egt �����Ӧ��ֵ
 * @param [out]    tgt �����Ӧ��ֵ
 * @param [out]    wdt �����Ӧ��ֵ
 * @param [out]    twdt �����Ӧ��ֵ
 * @param [out]    t01 �����Ӧ��ֵ,0 = T0,1 = T1
 *
 * @return   int >=0 ִ�гɹ�;<0 ִ��ʧ��
 * @note       -1 : SMART_PARSE_TS_ERROR     : TS�ַ���Ϊ0x3B����0x3F
 *             -2 : SMART_PARSE_LENGTH_ERROR : AtrLength���Ϸ�
 *             -3 : SMART_PARSE_TCK_ERROR    : У���ַ�Tck����ȷ
 *             -4 : SMART_PARSE_TA1_ERROR    : TA(1)�ַ��к���δʹ�õı���
 */

int GxSmc_ParseAtr(IN const uint8_t *Atr_p,
		uint32_t AtrLength,
		OUT uint32_t *etu,
		OUT uint32_t *egt,
		OUT uint32_t *tgt,
		OUT uint32_t *wdt,
		OUT uint32_t *twdt,
		OUT uint32_t *t01);

/**
 * @brief       �ر����ܿ�
 * @param [in]  handle     ���ܿ����
 * @return      int >=0 ִ�гɹ�;<0 ִ��ʧ��
 */
int GxSmc_Close(handle_t handle);

__END_DECLS

#endif
/*@}*/
