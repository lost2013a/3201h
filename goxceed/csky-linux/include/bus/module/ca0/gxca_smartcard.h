/*@{*/
#ifndef __GXCA_SMARTCARD_H__
#define __GXCA_SMARTCARD_H__

#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS


/**智能卡通讯协议*/
typedef enum {
	GXCA_SMART_T0_PROTOCOL,
	GXCA_SMART_T1_PROTOCOL
} GxCA_SmartProtocol;

/**智能卡VCC电平*/
typedef enum {
	GXCA_SMART_VCC_HIGH_LEVEL,
	GXCA_SMART_VCC_LOW_LEVEL
} GxCA_SmartVccPol;

/**智能卡通讯停止位*/
typedef enum {
	GXCA_SMART_STOPLEN_0BIT,
	GXCA_SMART_STOPLEN_1BIT,
	GXCA_SMART_STOPLEN_1D5BIT,
	GXCA_SMART_STOPLEN_2BIT
} GxCA_SmartStopLen;

/**智能卡触发电平*/
typedef enum {
	GXCA_SMART_DETECT_LOW_LEVEL       = 0,
	GXCA_SMART_DETECT_HIGH_LEVEL      = 1
} GxCA_SmartDetectPol;

/**智能卡通讯数据反转*/
typedef enum {
	GXCA_SMART_DATA_CONV_DIRECT       = 0,
	GXCA_SMART_DATA_CONV_INVERSE      = 1
} GxCA_SmartDataConv;

/**智能卡通讯校验*/
typedef enum {
	GXCA_SMART_PARITY_EVEN            = 0,
	GXCA_SMART_PARITY_ODD             = 1
} GxCA_SmartParityType;

/**智能卡状态*/
typedef enum {
	GXCA_SMART_CARD_INIT              = 0,
	GXCA_SMART_CARD_IN                = 1,
	GXCA_SMART_CARD_OUT               = 2
} GxCA_SmartCardStatus;

/**智能卡接口通讯时间参数*/
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
 * @brief       智能卡初始化函数
 * @param [in]  name                    智能卡设备名
 * @param [in]  sc_notify               智能卡状态通知函数指针
 * @return      handle_t 智能卡句柄
 */
handle_t GxCA_SmartcardOpen      (const char *name, GxCA_SmartParams *param);
int      GxCA_SmartcardGetStatus (handle_t   handle);


/**
 * @brief       智能卡复位函数
 * @param [in]   handle     智能卡句柄
 * @param [out]  AtrBuf    ATR缓冲
 * @param [out]  BufSize     ATR缓冲大小
 * @return  int  ATR获取成功,返回ATR长度
 */
int GxCA_SmartcardReset(handle_t handle, uint8_t *AtrBuf, size_t BufSize);

/**
 * @brief       智能卡时序参数配置
 * @param [in]   handle     智能卡句柄
 * @param [in]  time    智能卡时序参数
 * @return  int ATR获取成功,返回0,其它值失败
 */
int GxCA_SmartcardConfig(handle_t handle, const GxCA_SmartTimeParams *time);

/**
 * @brief       智能卡发送命令函数
 * @param [in]  handle     智能卡句柄
 * @param [in]  Cmd  智能卡命令指针
 * @param [in]  CmdLen       智能卡命令长度
 * @return  int 命令发送成功,返回发送字节数
 */
int GxCA_SmartcardSendCmd(handle_t handle, const uint8_t *Cmd, size_t CmdLen);

/**
 * @brief       获取智能卡响应
 * @param [in]  handle      智能卡句柄
 * @param [out] Reply       智能卡响应缓冲
 * @param [out] ReplyLen    智能卡响应长度缓冲
 * @return bool 响应获取成功返回TRUE,失败返回FALSE
 */
int GxCA_SmartcardGetReply(handle_t handle, uint8_t *ReplyBuf, size_t BufSize);

/**
 * @brief       关闭智能卡
 * @param [in]  handle     智能卡句柄
 * @return  bool 关闭成功返回TRUE,失败返回FALSE
 */
bool GxCA_SmartcardClose(handle_t handle);

__END_DECLS

#endif
/*@}*/
