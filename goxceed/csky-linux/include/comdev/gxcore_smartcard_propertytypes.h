/*****************************************************************************
* 						   CONFIDENTIAL								
*        Hangzhou GuoXin Science and Technology Co., Ltd.             
*                      (C)2006, All right reserved
******************************************************************************

******************************************************************************
* File Name :	gxav_audiodec_propertytypes.h
* Author    : 	Yqj
* Project   :	GoXceed
* Type      :	Driver
******************************************************************************
* Purpose   :	
******************************************************************************
* Release History:
  VERSION	Date			  AUTHOR         Description
   0.0  	2009.11.18	      Yqj.	         creation
*****************************************************************************/

#ifndef __GXCORE_SMARTCARD_PROPERTYTYPES_H__
#define __GXCORE_SMARTCARD_PROPERTYTYPES_H__

/* Includes --------------------------------------------------------------- */

/* Exported Macros -------------------------------------------------------- */

/* Exported Types --------------------------------------------------------- */
#if 0
typedef enum {
    EXAMPLE1       = 0,
		EXAMPLE2       = 1,
} GxCoreSmartCardProperty;

typedef struct {
    unsigned int            	 a;
    unsigned int            	 b;
} GxCoreSmartCardProperty_Example1;

typedef struct {
    unsigned int            	 c;
    unsigned int            	 d;
} GxCoreSmartCardProperty_Example2;
#endif
/* Available ISO7816-3 protocols */
typedef enum GXSMART_Protocol_e
{
    GXSMART_T0_PROTOCOL,
    GXSMART_T1_PROTOCOL
} GXSMART_Protocol_t;

typedef enum GXSMART_VccPol_e
{
    GXSMART_VCC_HIGH_LEVEL,
    GXSMART_VCC_LOW_LEVEL
}GXSMART_VccPol_t;

typedef enum GXSMART_StopLen_e
{
    GXSMART_STOPLEN_0BIT,
    GXSMART_STOPLEN_1BIT,
    GXSMART_STOPLEN_1D5BIT,
    GXSMART_STOPLEN_2BIT
}GXSMART_StopLen_t;

typedef enum GXSMART_DetectPol_e
{
    GXSMART_DETECT_HIGH_LEVEL      = 0,
    GXSMART_DETECT_LOW_LEVEL       = 1
}GXSMART_DetectPol_t;

typedef enum GXSMART_SmartDataConv_e
{
    GXSMART_DATA_CONV_DIRECT       = 0,
    GXSMART_DATA_CONV_INVERSE      = 1
}GXSMART_DataConv_t;

typedef enum GXSMART_SmartParityType_e
{
    GXSMART_PARITY_EVEN            = 0,
    GXSMART_PARITY_ODD             = 1
}GXSMART_ParityType_t;

typedef enum GXSMART_CardStatus_e
{
    GXSMART_CARD_INIT              = 0,
    GXSMART_CARD_IN                = 1,
    GXSMART_CARD_OUT               = 2
}GXSMART_CardStatus_t;

typedef struct GXSMART_TimeParams_s
{
    unsigned int Egt;             //SCI_EGT
    unsigned int Tgt;             //SCI_TGT
    unsigned int Wdt;             //SCI_WDT
    unsigned int Twdt;            //SCI_TWDT
}GXSMART_TimeParams_t;

typedef struct GXSMART_OpenParams_s
{
    GXSMART_TimeParams_t    TimeParams;
    GXSMART_Protocol_t      Protocol;       //GXSMART_T1_PROTOCOL
    unsigned int              BaudRate;       //SCI_CLK
    unsigned int              Etu;            //371
    GXSMART_StopLen_t       StopLen;        //0
    GXSMART_DataConv_t      IoConv;         //GXSMART_DATA_CONV_DIRECT                   //I/O convention
    GXSMART_ParityType_t    ParityType;     //GXSMART_PARATY_EVEN        0
}GXSMART_OpenParams_t;

typedef struct GXSMART_InitParams_s
{
    GXSMART_VccPol_t        VccPole;        //GXSMART_VCC_LOW_LEVEL
    GXSMART_DetectPol_t     DetectPole;     //GXSMART_DETECT_LOW_LEVEL
}GXSMART_InitParams_t;

typedef struct GXSMART_AtrParams_s
{
    unsigned int  len;                            //atr len
    void        *priv;                          //buffer addr
}GXSMART_AtrParams_t;

/* SCI_COMS */
#define SET_OPEN_PARAMS (0)
#define SET_INIT_PARAMS (1)
#define CARD_DEACT      (2)
#define CARD_COLD_RESET (3)
#define CARD_HOT_RESET  (4)
#define GET_CARD_STATUS (5)

/* Functions ---------------------------------------------------------- */

#endif /* __GXCORE_SMARTCARD_PROPERTYTYPES_H__ */

