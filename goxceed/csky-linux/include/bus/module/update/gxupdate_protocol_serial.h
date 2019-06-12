#ifndef __GXUPDATE_SERIAL_H__
#define __GXUPDATE_SERIAL_H__

#include "gxupdate_stream.h"
#include "gxcore.h"

__BEGIN_DECLS

#define SERIAL_DEVICE_NAME                          "/dev/ser0"

#define GXUPDATE_MAX_NUM_SERIAL_OPEN                (1)
#define CHIP_GX3001                                 (3001)
#define CHIP_GX6102                                 (6102)
#define CHIP_GX6105                                 (6105)
#define CHIP_GX6001                                 (6001)
#define CHIP_GX6002                                 (6002)
#define CHIP_GX3002                                 (3002)
#define CHIP_GX3101                                 (3101)
#define CHIP_GX6103                                 (6103)
#define CHIP_GX6107                                 (6103)
#define CHIP_GX6108                                 (6108)
#define CHIP_GX3101_DVN                             (31011)
#define CHIP_GX6169                                 (6169)
#define CHIP_GX6105_ENGLE                           (61051)
#define CHIP_GX6201                                 (6201)
#define CHIP_GX6202                                 (6202)
#define CHIP_GX3102                                 (3102)
#define CHIP_GX3110                                 (3110)
#define CHIP_GX3113                                 (3113)

#define GXUPDATE_CHIP_TYPE                          CHIP_GX6201

/***/
#define GXUPDATE_SERIAL_SELECT_TERMINAL_TYPE        (0)
#define GXUPDATE_SET_SERIAL_INFO                    (1)
#define GXUPDATE_SET_CONFIG_PLATFORM                (2)

#define GXUPDATE_PROTOCOL_SERIAL            "gxupdate protocol serial"

typedef enum {
	SERIAL_BAUD_50 = 1,
	SERIAL_BAUD_75,
	SERIAL_BAUD_110,
	SERIAL_BAUD_134_5,
	SERIAL_BAUD_150,
	SERIAL_BAUD_200,
	SERIAL_BAUD_300,
	SERIAL_BAUD_600,
	SERIAL_BAUD_1200,
	SERIAL_BAUD_1800,
	SERIAL_BAUD_2400,
	SERIAL_BAUD_3600,
	SERIAL_BAUD_4800,
	SERIAL_BAUD_7200,
	SERIAL_BAUD_9600,
	SERIAL_BAUD_14400,
	SERIAL_BAUD_19200,
	SERIAL_BAUD_38400,
	SERIAL_BAUD_57600,
	SERIAL_BAUD_115200,
	SERIAL_BAUD_230400,
	SERIAL_BAUD_460800,
	SERIAL_BAUD_921600
} GxUpdate_SerialBaudRate;

typedef enum {
	SERIAL_STOP_1 = 1,
	SERIAL_STOP_1_5,
	SERIAL_STOP_2
} GxUpdate_SerialStopBits;

typedef enum {
	SERIAL_PARITY_NONE = 0,
	SERIAL_PARITY_EVEN,
	SERIAL_PARITY_ODD,
	SERIAL_PARITY_MARK,
	SERIAL_PARITY_SPACE
} GxUpdate_SerialParity;

typedef enum {
	SERIAL_WORD_LENGTH_5 = 5,
	SERIAL_WORD_LENGTH_6,
	SERIAL_WORD_LENGTH_7,
	SERIAL_WORD_LENGTH_8
} GxUpdate_SerialWordLength;

typedef struct {
	GxUpdate_SerialBaudRate     baud;           /**波特率*/
	GxUpdate_SerialStopBits     stop;           /**停止位*/
	GxUpdate_SerialParity       parity;         /**奇偶校验位*/
	GxUpdate_SerialWordLength   word_length;    /**字宽*/
	uint32_t                    flags;          /**流控*/
} GxUpdate_SerialInfo;

typedef struct {
	GxUpdate_Terminal           type;
} GxUpdate_ConfigSerialTerminalType;

typedef enum {
	GXFLASH_AM29LV008DT = 0,        /* ----PPL FLASH----*/
	GXFLASH_AM29LV160DT,
	GXFLASH_AM29LV320DT,
	GXFLASH_EN29LV800AB,
	GXFLASH_EN29LV160AB,
	GXFLASH_EN29LV320AB,
	GXFLASH_EN29LV640HUL,
	GXFLASH_MX29LV800BTC,
	GXFLASH_MX29LV160BTC,
	GXFLASH_MX29LV320BTC,
	GXFLASH_MX29LV640BTC,
	GXFLASH_S29AL004D,
	GXFLASH_S29AL008D,
	GXFLASH_S29AL016D,
	GXFLASH_S29AL032D,
	GXFLASH_S29GL016A,
	GXFLASH_S29GL032A,
	GXFLASH_S29GL064A,
	GXFLASH_KH29LV800CBTC,
	GXFLASH_KH29LV160CBTC,
	GXFLASH_KH29LV320CBTC,
	GXFLASH_W19B320AB,
	GXFLASH_W19B160AB,
	GXFLASH_HY29F400,
	GXFLASH_MBM29LV400BC,
	GXFLASH_AT49F040A,
	GXFLASH_EN25B16 = 0x80,           /* ----SPI FLASH----*/
	GXFLASH_EN25B32,
	GXFLASH_EN25B40,
	GXFLASH_EN25P40,
	GXFLASH_AT26DF161,
	GXFLASH_AT26DF321,
	GXFLASH_SST25VF016B,
	GXFLASH_SST25VF032B,
	GXFLASH_W25X16,         /* SPI FLASH带多倍数操作,能进行Fast Read*/
	GXFLASH_W25X32,         /* SPI FLASH带多倍数操作,能进行Fast Read*/
	GXFLASH_W25X10,
	GXFLASH_W25X20,
	GXFLASH_W25X40,
	GXFLASH_W25X80,
	GXFLASH_W25Q80,         /* SPI FLASH带多倍数操作,能进行Fast Read/Fast Program*/
	GXFLASH_W25Q16,         /* SPI FLASH带多倍数操作,能进行Fast Read/Fast Program*/
	GXFLASH_W25Q32,         /* SPI FLASH带多倍数操作,能进行Fast Read/Fast Program*/
	GXFLASH_PRV_MX25L3205   /* 私有flash定义*/

} GXFLASH_DeviceType_t;

typedef struct {
	uint32_t nWork_Mode       : 8;   /** 0 : download*/
	uint32_t nChip_Type       : 8;   /** 0 : gx3001; 1 : gx3002; 0x20 : gx3113*/
	uint32_t nXtal            : 16;  /** 单位: KHz ,4000,8000...27000*/

	uint32_t nFlash_Interface : 8;   /** 0 : Parallel Flash; 1: SPI Flash*/
	uint32_t nDRAM_Type       : 8;   /** 0 : SDRAM; 1: DDRAM*/
	uint32_t nDRAM_Size       : 8;   /** 0 : 64Mbit; 1: 128Mbit; 2: 256Mbit; 3: 512Mbit*/
	uint32_t nMix_Type        : 8;   /** pflash的管脚复用类型*/

	uint32_t nSection_Start;
	uint32_t nSection_Len;

	uint32_t nFlash_Model     : 8;   /** FLASH类型 GXFLASH_DeviceType_t*/
	uint32_t nSdramModel      : 8;   /** SDRAM模式 full-page;burst*/
	uint32_t  bFastModel      : 8;   /** 写flash快速模式，接收的数据必须是非压缩文件，不校验flash中原数据是什么，假定他都是0xFF,直接写flash */
	uint32_t nReserver0       : 8;

	uint32_t nReserver1;
	uint32_t nReserver2;
} GxUpdate_SerialPlatform;

extern GxUpdate_ProtocolOps gxupdate_protocol_serial;

__END_DECLS

#endif

