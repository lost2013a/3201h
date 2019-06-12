#ifndef __GXAV_ICAM_PROPERTYTYPES_H__
#define __GXAV_ICAM_PROPERTYTYPES_H__

#define  TYPE_ICAM28_VCC_3V                (0x00)
#define  TYPE_ICAM28_VCC_5V                (0x01)

#define  TYPE_ICAM28_VCC_ON                (0x00)
#define  TYPE_ICAM28_VCC_OFF               (0x01)


typedef enum {
	TYPE_ICAM28_BAUD_RATE_9600     = 0,
	TYPE_ICAM28_BAUD_RATE_19200    = 1,
	TYPE_ICAM28_BAUD_RATE_38400    = 2,
	TYPE_ICAM28_BAUD_RATE_76800    = 3,
	TYPE_ICAM28_BAUD_RATE_153600   = 4,
	TYPE_ICAM28_BAUD_RATE_178560   = 5,
	TYPE_ICAM28_BAUD_RATE_223200   = 6
} TYPE_ICAM28_BaudRate_e;

typedef enum {
	EVENT_CARD_REMOVE         = 0,
	EVENT_CARD_INSERT         = 1,
	EVENT_CARD_ERROR          = 2,
	EVENT_DATA_TRANSFER_OK    = 3,
	EVENT_DATA_RECEIVE_OK     = 4,
	EVENT_DATA_OVER_FLOW      = 5,
	EVENT_DATA_BAD_PARITY     = 6
} EVENT_FLAG_e;

typedef struct {
	unsigned int m_TxReady           : 1;
	unsigned int m_RxReady           : 1;
	unsigned int m_TxError           : 1;
	unsigned int m_OverFlow          : 1;
	unsigned int m_RxError           : 1;
	unsigned int m_ConventionDirect  : 1;        // 1:direct 0:inverse
	unsigned int m_InterruptPending  : 1;
	unsigned int m_CardInsert        : 1;
} TYPE_ICAM28_UartStatus_t;

typedef struct {
	unsigned int m_IO_VIA_C7 : 1;
	unsigned int m_IO_VIA_C4 : 1;
	unsigned int m_IO_VIA_C8 : 1;
	unsigned int m_C7_ON     : 1;
	unsigned int m_C4_ON     : 1;
	unsigned int m_C8_ON     : 1;
} TYPE_ICAM28_UartCommand_t;

typedef struct {
	unsigned int m_clockdivisor;
} GxIcamProperty_ClockDivisor ;

typedef struct {
	unsigned char m_vcclevel;
} GxIcamProperty_VccLevel;

typedef struct {
#define  TYPE_ICAM28_CONVENTION_INVERSE    (0x00)
#define  TYPE_ICAM28_CONVENTION_DIRECT     (0x01)
	unsigned char m_convention;
} GxIcamProperty_Convention;

typedef struct {
	unsigned char m_uartbaudrate;
	unsigned int  m_icam_frequence; // gxloader set
} GxIcamProperty_UartBaudRate;

typedef struct {
	unsigned char m_vccswitch;
} GxIcamProperty_VccSwitch;

typedef struct {
	unsigned char m_guardtime;
} GxIcamProperty_GuardTime;

typedef struct {
	unsigned char m_resetswitch;
} GxIcamProperty_ResetCard;

typedef struct {
	TYPE_ICAM28_UartCommand_t m_pinmask;
} GxIcamProperty_UartCommand;

typedef struct {
	TYPE_ICAM28_UartStatus_t m_uartstatus;
} GxIcamProperty_UartStatus;

typedef struct {
	unsigned char m_interrupt_event;
} GxIcamProperty_InterruptEvent;

typedef struct {
	unsigned char m_insert_or_remove;
} GxIcamProperty_InsertRemove;

typedef struct {
	unsigned char *m_p_send;
	unsigned char  m_n_send;
	unsigned char  m_null_filter;
	unsigned char  m_flow_control;
	unsigned char *m_p_rece;
	unsigned char  m_n_rece;
} GxIcamProperty_SendAndReceive;

typedef struct {
	unsigned char  m_null_filter;
	unsigned char  m_flow_control;
	unsigned char *m_p_rece;
	unsigned char  m_n_rece;
} GxIcamProperty_Receive;

typedef struct {
	unsigned int   m_chip_id[2];
	unsigned int   m_icam_version;
	unsigned char  m_hash_key[16];
} GxIcamProperty_ChipProperties;

typedef struct {
	unsigned char  m_user_enable;
	unsigned char  m_user_buff[16];
	unsigned char  m_default_time;
	unsigned char  m_nonce[16];
	unsigned char  m_responce[16];
} GxIcamProperty_ResponseToChallenge;

typedef struct {
	unsigned char  m_default_time;
	unsigned char  m_nonce[16];
	unsigned char  m_responce[16];
} GxIcamProperty_EncryptData;

typedef struct {
	unsigned int  m_offset;
	unsigned int  m_read_write_data;
} GxIcamProperty_Read_Write_Register;

typedef struct{
	unsigned int  m_cw_time;
	unsigned int  m_desc_id;

#define TYPE_ICAM28_POLARITY_ODD    (1)
#define TYPE_ICAM28_POLARITY_EVEN   (2)
	unsigned int  m_even_odd;

	unsigned int  m_command_value;
	unsigned char m_cw_data[16];
} GxIcamProperty_ControlWord;

typedef struct {
	unsigned int  m_reset_card_time;
	unsigned int  m_icam_frequency;
	unsigned int  m_sc_clock_frequency;
	unsigned int  m_icam_buard_rate_reg_value ;
	unsigned int  m_buard_rate_factor  ;//h 24~31 , buard_rate_index, l factor
} GxIcamProperty_ConfigInfo;

typedef struct {
	unsigned int  m_addr;
	unsigned int  m_num ;
	unsigned char m_data[16];
} GxIcamProperty_Read_Write_OTP;

#endif

