#ifndef _GX_SMARTCARD_PARAMS_H_
#define _GX_SMARTCARD_PARAMS_H_

/* Available ISO7816-3 protocols */
typedef enum GXSMART_Protocol_e {
	GXSMART_T0_PROTOCOL,
	GXSMART_T1_PROTOCOL
} GXSMART_Protocol_t;

typedef enum GXSMART_SCI_e {
	GXSMART_SCI1 = 0,
	GXSMART_SCI2
} GXSMART_SCI_t;

typedef enum GXSMART_VccPol_e {
	GXSMART_VCC_HIGH_LEVEL,
	GXSMART_VCC_LOW_LEVEL
}GXSMART_VccPol_t;

typedef enum GXSMART_StopLen_e {
	GXSMART_STOPLEN_0BIT,
	GXSMART_STOPLEN_1BIT,
	GXSMART_STOPLEN_1D5BIT,
	GXSMART_STOPLEN_2BIT
}GXSMART_StopLen_t;

typedef enum GXSMART_DetectPol_e {
	GXSMART_DETECT_LOW_LEVEL        = 0,
	GXSMART_DETECT_HIGH_LEVEL       = 1
}GXSMART_DetectPol_t;

typedef enum GXSMART_SmartDataConv_e {
	GXSMART_DATA_CONV_DIRECT       = 0,
	GXSMART_DATA_CONV_INVERSE      = 1
}GXSMART_DataConv_t;

typedef enum GXSMART_SmartParityType_e {
	GXSMART_PARITY_ODD             = 0,
	GXSMART_PARITY_EVEN            = 1,
}GXSMART_ParityType_t;

typedef enum GXSMART_CardStatus_e {
	GXSMART_CARD_INIT              = 0,
	GXSMART_CARD_IN                = 1,
	GXSMART_CARD_OUT               = 2
}GXSMART_CardStatus_t;

typedef enum GXSMART_Parity_e {
	GXSMART_DETECT_HARD_PARITY       = 0,
	GXSMART_DETECT_SOFT_PARITY       = 1
}GXSMART_PARITY_t;

typedef struct GXSMART_TimeParams_s {
	unsigned int Egt;             // SCI_EGT
	unsigned int Tgt;             // SCI_TGT
	unsigned int Wdt;             // SCI_WDT
	unsigned int Twdt;            // SCI_TWDT
}GXSMART_TimeParams_t;

typedef struct GXSMART_OpenParams_s {
	GXSMART_TimeParams_t    TimeParams;
	GXSMART_Protocol_t      Protocol;       // GXSMART_T1_PROTOCOL
	unsigned int            BaudRate;       // SCI_CLK
	unsigned int            Etu;            // 371
	GXSMART_StopLen_t       StopLen;        // 0
	GXSMART_DataConv_t      IoConv;         // GXSMART_DATA_CONV_DIRECT                   //I/O convention
	GXSMART_ParityType_t    ParityType;     // GXSMART_PARATY_EVEN        0
	unsigned char           AutoEtu;
	unsigned char           AutoIoConvAndParity;
}GXSMART_OpenParams_t;

typedef struct GXSMART_InitParams_s {
	GXSMART_VccPol_t        VccPole;        // GXSMART_VCC_LOW_LEVEL
	GXSMART_DetectPol_t     DetectPole;     // GXSMART_DETECT_LOW_LEVEL
}GXSMART_InitParams_t;

typedef struct GXSMART_AtrParams_s {
	unsigned int  len;                      // atr len
	void        *priv;                      // buffer addr
}GXSMART_AtrParams_t;

typedef struct GXSMART_ConfigFifoLevel_s {
	unsigned int  tx_fifolevel;              // fifolevel
	unsigned int  rx_fifolevel;
}GXSMART_ConfigFifoLevel_t;

typedef struct GXSMART_ConfigIntPart_s {
	unsigned int	intpart;
}GXSMART_ConfigIntPart_t;

typedef struct GXSMART_ConfigEn_s {
	unsigned char	module_en;
}GXSMART_ConfigEn_t;

typedef struct GXSMART_ConfigAutoRec_s {
	unsigned char	module_auto;
}GXSMART_ConfigAutoRec_t;


typedef struct GXSMART_ConfigDataFifoReset_s {
	unsigned char	datafiforeset;
}GXSMART_ConfigDataFifoReset_t;


typedef struct GXSMART_Configmodulereset_s {
	unsigned char	modulereset;
}GXSMART_Configmodulereset_t;

typedef struct sci_modes {
	int emv2000;
	int dma;
	int man_act;
	int rw_mode;
}
SCI_MODES;

typedef enum GXSMART_Calc_Parity {
	GXSMART_Calc_Parity_ON        = 0,
	GXSMART_Calc_Parity_OFF       = 1
}GXSMART_CalcParity_t;

/* config type */
#define SCI_SETCONFIG_FIFOLEVEL     (0x100006)
#define SCI_SETCONFIG_INTPART       (0x100007)
#define SCI_SETCONFIG_OPEN          (0x100008)
#define SCI_GETCONFIG_OPEN          (0x100018)
#define SCI_SETCONFIG_CD_POLARITY   (0x100009)
#define SCI_SETCONFIG_EN            (0x10000a)
#define SCI_SETCONFIG_AUTOREC       (0x10000b)
#define SCI_SETCONFIG_DATAFIFORESET (0x10000c)
#define SCI_SETCONFIG_MODULERESET   (0x10000d)
#define SCI_GETCONFIG_INTPART       (0x10000e)
#define SCI_GETCONFIG_CONFIG        (0x10000f)
#define SCI_GETCONFIG__STATUS       (0x100010)
#define SCI_SETCONFIG_NO_PARITY     (0x100011)
#define SCI_SETCONFIG_STOPLEN       (0x100012)
#define SCI_SETCONFIG_AUTOETU       (0x100013)
#define SCI_SETCONFIG_AUTOCONV      (0x100014)


/* IOCTL magic num */
#define SCI_IOW_MAGIC               's'
#define IOCTL_SET_RESET             _IOW(SCI_IOW_MAGIC,  1, unsigned int)
#define IOCTL_SET_MODES             _IOW(SCI_IOW_MAGIC,  2, SCI_MODES)
#define IOCTL_GET_MODES             _IOW(SCI_IOW_MAGIC,  3, SCI_MODES)
#define IOCTL_SET_PARAMETERS        _IOW(SCI_IOW_MAGIC,  4, GXSMART_OpenParams_t)
#define IOCTL_GET_PARAMETERS        _IOW(SCI_IOW_MAGIC,  5, GXSMART_OpenParams_t)
#define IOCTL_SET_CLOCK_START       _IOW(SCI_IOW_MAGIC,  6, unsigned int)
#define IOCTL_SET_CLOCK_STOP        _IOW(SCI_IOW_MAGIC,  7, unsigned int)
#define IOCTL_GET_IS_CARD_PRESENT   _IOW(SCI_IOW_MAGIC,  8, unsigned int)
#define IOCTL_GET_IS_CARD_ACTIVATED _IOW(SCI_IOW_MAGIC,  9, unsigned int)
#define IOCTL_SET_DEACTIVATE        _IOW(SCI_IOW_MAGIC, 10, unsigned int)
#define IOCTL_SET_ATR_READY         _IOW(SCI_IOW_MAGIC, 11, unsigned int)
#define IOCTL_GET_ATR_STATUS        _IOW(SCI_IOW_MAGIC, 12, unsigned int)
#define IOCTL_DUMP_REGS             _IOW(SCI_IOW_MAGIC, 20, unsigned int)
#define IOCTL_SET_SELECT_SCI        _IOW(SCI_IOW_MAGIC, 21, GXSMART_SCI_t)
#define IOCTL_SET_VCCEN_POLARITY    _IOW(SCI_IOW_MAGIC, 22, GXSMART_VccPol_t)
#define IOCTL_SET_CD_POLARITY       _IOW(SCI_IOW_MAGIC, 23, GXSMART_DetectPol_t)
#define IOCTL_SET_STOPLEN           _IOW(SCI_IOW_MAGIC, 24, unsigned char)
#define IOCTL_SET_NOPARITY          _IOW(SCI_IOW_MAGIC, 25, unsigned char)
#define IOCTL_SET_AUTOETU           _IOW(SCI_IOW_MAGIC, 26, unsigned char)
#define IOCTL_SET_AUTOCONV          _IOW(SCI_IOW_MAGIC, 27, unsigned char)
#define IOCTL_SET_ETU               _IOW(SCI_IOW_MAGIC, 28, unsigned int)
#define IOCTL_SET_CWT               _IOW(SCI_IOW_MAGIC, 29, unsigned int)
#define IOCTL_SET_BWT               _IOW(SCI_IOW_MAGIC, 30, unsigned int)
#define IOCTL_SET_EGT               _IOW(SCI_IOW_MAGIC, 31, unsigned int)
#define IOCTL_SET_TGT               _IOW(SCI_IOW_MAGIC, 32, unsigned int)
#define IOCTL_SHOW_REGS             _IOW(SCI_IOW_MAGIC, 33, unsigned int)
#define IOCTL_SET_DEBUG             _IOW(SCI_IOW_MAGIC, 34, unsigned int)

#define IOCTL_SET_FRE               _IOW(SCI_IOW_MAGIC, 35, unsigned int)
#define IOCTL_SET_IOCONV            _IOW(SCI_IOW_MAGIC, 36, GXSMART_DataConv_t)
#define IOCTL_SET_PARITY_TYPE       _IOW(SCI_IOW_MAGIC, 37, GXSMART_ParityType_t)
#define IOCTL_SET_PROTOCOL          _IOW(SCI_IOW_MAGIC, 38, GXSMART_Protocol_t)

#endif /* _GX_SMARTCARD_PARAMS_H_ */
