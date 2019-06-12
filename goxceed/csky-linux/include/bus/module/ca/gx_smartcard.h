/**
 * @file gx_smartcard.h
 * @author lixb
 * @brief CAS系统智能卡抽象模块
 * @asstogroup ca_module
 */
/*@{*/
#ifndef __GXCA_SMARTCARD_H__
#define __GXCA_SMARTCARD_H__

#include "gxtype.h"
#include "gxcore.h"
#include "gxcas.h"

__BEGIN_DECLS


/*选择第几路sci控制器,有些芯片支持2路sci*/
typedef enum {
	__GXSMART_SCI1 = 0,
	__GXSMART_SCI2
} GxSmcSelect;


/**智能卡通讯重发协议*/
typedef enum {
	/*校验错误时重发一个字节,这样每次交互都会多发一个应答位(T0)*/
	ENABLE_REPEAT_WHEN_ERR,
	/*校验错误时也不重发,一般建议使用此模式(T1)*/
	DISABLE_REPEAT_WHEN_ERR
} GxSmcRepeat_t;

/**智能卡VCC电平*/
typedef enum {
	GXSMC_VCC_HIGH_LEVEL,
	GXSMC_VCC_LOW_LEVEL
}GxSmcVccPol;

/* 复位时是否使用硬件识别ETU，若是，复位后需要根据应答拿到ETU值
 * 再进行配置*/
typedef enum {
	GXSMC_RESET_VIA_SET_ETU,
	GXSMC_RESET_VIA_AUTO_ETU,
}GxSmcAutoEtu_t;

/**智能卡通讯停止位*/
typedef enum {
	GXSMC_STOPLEN_0BIT,
	GXSMC_STOPLEN_1BIT,
	GXSMC_STOPLEN_1D5BIT,
	GXSMC_STOPLEN_2BIT
}GxSmcStopLen;

/**智能卡触发电平*/
typedef enum {
	GXSMC_DETECT_LOW_LEVEL       = 0,
	GXSMC_DETECT_HIGH_LEVEL      = 1
}GxSmcDetectPol;

/**智能卡通讯数据反转*/
typedef enum {
	GXSMC_DATA_CONV_DIRECT       = 0,
	GXSMC_DATA_CONV_INVERSE      = 1
}GxSmcDataConv;

/**智能卡通讯校验*/
typedef enum {
	GXSMC_PARITY_ODD             = 0,
	GXSMC_PARITY_EVEN            = 1
}GxSmcParityType;

/**智能卡状态*/
typedef enum {
	GXSMC_CARD_INIT              = 0,
	GXSMC_CARD_IN                = 1,
	GXSMC_CARD_OUT               = 2
}GxSmcCardStatus;

/**智能卡接口通讯时间参数*/
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
	uint32_t                baud_rate;  /*智能卡工作频率,比如9600*372*/
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
#define O_BDBG  (1)   /* 打开bus的调试信息 */
#define O_CDBG  (1<<1)  /* 打开驱动的调试信息 */
	GxSmcRepeat_t      protocol;
	GxSmcStopLen       stop_len;
	GxSmcDataConv      io_conv;
	GxSmcParityType    parity;
	GxSmcVccPol        vcc_pole;
	GxSmcDetectPol     detect_pole;
	GxSmcSelect        sci_sel;
	GxSmcAutoEtu_t     auto_etu;//1,auto
	uint32_t           auto_parity;//1,auto
	uint32_t           default_etu;/* 默认etu值 */
	uint32_t           debug_info;
}GxSmcParams;

/**
 * @brief       智能卡打开函数
 * @param [in]  name                    智能卡设备名
 * @param [in]  sc_notify               智能卡状态通知函数指针
 * @return      handle_t 智能卡句柄E_INVALID_HANDLE 执行失败
 */
handle_t GxSmc_Open(const char *name, IN GxSmcParams *param);


/**
 * @brief       智能卡复位函数
 *
 * @param [in]   handle    智能卡句柄
 * @param [out]  AtrBuf    ATR 缓冲,缓冲区大小建议不小于33字节
 * @param [in]   BufSize   ATR 缓冲大小
 * @param [out]  RetLen    实际获取的atr长度
 *
 * @return      int >=0 执行成功;<0 执行失败
 */
int GxSmc_Reset(handle_t handle,OUT uint8_t* AtrBuf,size_t BufSize,OUT size_t *RetLen);


/**
 * @brief       智能卡时序参数配置
 * @param [in]  handle  智能卡句柄
 * @param [in]  time    智能卡时序参数
 * @return      int >=0 执行成功;<0 执行失败
 */
int GxSmc_Config(handle_t handle, IN const GxSmcTimeParams* time);

/**
 * @brief       智能卡参数配置新接口，尽量使用此接口代替GxSmc_Config
 * @param [in]  handle    智能卡句柄
 * @param [in]  config    智能卡参数
 * @return      int >=0 执行成功;<0 执行失败
 */
int GxSmc_ConfigAll(handle_t handle, IN const GxSmcConfigs *config);

/**
 * @brief       智能卡发送命令函数
 * @param [in]  handle    智能卡句柄
 * @param [in]  Cmd       智能卡命令指针
 * @param [in]  CmdLen    智能卡命令长度
 * @param [out]  SendLen  发送给智能卡的实际长度
 * @return      int 发送到字节数，<0则发送失败
 */
int GxSmc_SendCmd(handle_t handle, IN const uint8_t *Cmd, size_t CmdLen);

/**
 * * @brief       智能卡发送命令函数
 * * @param [in]  handle  智能卡句柄
 * * @param [in]  Cmd     智能卡命令指针
 * * @param [in]  CmdLen  智能卡命令长度
 * * @param [in]  timeout 超时时间
 * * @return      int 返回发送成功到字节数，<0，则发送失败
 * */
int GxSmc_SendCmd_Extend(handle_t handle, IN const uint8_t* Cmd,size_t CmdLen,size_t timeout);

/**
 * @brief       获取智能卡响应
 * @param [in]  handle    智能卡句柄
 * @param [out] ReplyBuf  智能卡响应缓冲
 * @param [out] BufSize   智能卡响应长度缓冲
 * @param [out] RetLen    智能卡响应的实际长度
 * @return      int 返回获取到的字节数， <0则获取失败
 */
int GxSmc_GetReply(handle_t handle, IN uint8_t*  ReplyBuf,size_t BufSize);
/**
 * @brief       获取智能卡响应
 *
 * @param [in]  handle      智能卡句柄
 * @param [out] ReplyBuf    智能卡响应缓冲
 * @param [out] BufSize     智能卡响应长度缓冲
 * @param [in]  timeout     超时时间
 *
 * @return      int 返回获取到的字节数，<0则获取失败
 */
int GxSmc_GetReply_Extend(handle_t handle, IN uint8_t* ReplyBuf, size_t BufSize,size_t timeout);

/**
 * @brief       处理智能卡命令
 *
 * @param [in]  handle    智能卡句柄
 * @param [in]  CmdLen    处理的命令长度
 * @param [in]  pCmd      需要处理的命令指针
 * @param [out] pResponse 输出的响应缓存
 * @param [out] RespLen   处理完成后返回的响应长度
 * @param [out] pSW1      处理完成后返回的状态字1
 * @param [out] pSW2      处理完成后返回的状态字2
 *
 * @return      int >=0 执行成功;<0 执行失败
 *
 * @note  此函数完成了简单的apdu部分处理,比如0x61, sw1 == INS,等待
 *        等等.相当于GxSmc_SendCmd,GxCA_SmcGetReply两函数的再次组合,
 *        使用时请根据cas的情况作出选择.
 */
int GxSmc_SendReceiveData(handle_t handle,
		size_t CmdLen,
		IN const uint8_t* pCmd,
		OUT uint8_t *pResponse,
		OUT size_t *RespLen,
		OUT uint8_t *pSW1,
		OUT uint8_t *pSW2);

/**
 * @brief       获取智能卡状态
 * @param [in]  handle     智能卡句柄
 * @param [out]  state     智能卡状态
 * @return      int >=0 执行成功;<0 执行失败
 * @note 模块使用者必须及时调用此函数以获取智能卡状态
 *       并完成相关的操作.响应的实时性由使用者调用此函数
 *       的实时性决定.
 */
int GxSmc_GetStatus (handle_t   handle,OUT GxSmcCardStatus *state);

/**
 * @brief       解析智能卡的复位应答串
 * @param [in]  Atr_p       应答内容指针
 * @param []    AtrLength 应答内容的长度
 * @param [out]    etu 输出相应的值
 * @param [out]    egt 输出相应的值
 * @param [out]    tgt 输出相应的值
 * @param [out]    wdt 输出相应的值
 * @param [out]    twdt 输出相应的值
 * @param [out]    t01 输出相应的值,0 = T0,1 = T1
 *
 * @return   int >=0 执行成功;<0 执行失败
 * @note       -1 : SMART_PARSE_TS_ERROR     : TS字符不为0x3B或者0x3F
 *             -2 : SMART_PARSE_LENGTH_ERROR : AtrLength不合法
 *             -3 : SMART_PARSE_TCK_ERROR    : 校检字符Tck不正确
 *             -4 : SMART_PARSE_TA1_ERROR    : TA(1)字符中含有未使用的编码
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
 * @brief       关闭智能卡
 * @param [in]  handle     智能卡句柄
 * @return      int >=0 执行成功;<0 执行失败
 */
int GxSmc_Close(handle_t handle);

__END_DECLS

#endif
/*@}*/
