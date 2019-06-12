#ifndef __COM_TTX_H
#define __COM_TTX_H

#include "gxtype.h"
#include "gxcore.h"

#include "module/ttx/ttx_import.h"
#include "module/ttx/ttx_sub.h"
#include "module/ttx/ttx_vbi.h"

__BEGIN_DECLS

//extern gx_handle_t ThreadHandelTtx;

//extern Handle_t HandleDummySemSubtDisable;
//extern Handle_t HandleDummySemSubtShow;

#define MAX_TTX_DESC      10
#define MAX_SUBT_LANGUAGE 255
#define MAX_TTX_LANGUAGE  25
typedef struct TeletextPageInfo_s
{
	uint32_t m_nTtxLanguage;
	uint8_t m_wTtxType;
	uint8_t m_wTtxMagNum;
	uint8_t m_wTtxPageNum;
}TeletextPageInfo_t;

// for pre-process
#define TTX_PRE_DECODE
#define TTX_PRE_KEEP_DATA
typedef struct TeletextPreProcessConfig_s
{
	uint16_t TtxPid;
}TeletextPreProcessConfig_t;

typedef struct TeletextConfig_s
{
	uint8_t MagazineCacheNum;// 1~8, default data for TTX is DEFAULT_MAGAZINE_NUM_CACHE
	uint8_t TeletextPreProcessEnable;// 1: enable pre mode; 0:disable the pre mode
}TeletextConfig_t;


enum {
	VBI_TTX_ENABLE=0,
	OSD_TTX_ENABLE,
};

/* Exported Constants ----------------------------------------------------- */
#define UpKey                     21  // 1
#define DownKey                   22  // 2
#define LeftKey                   23  // 3
#define RightKey                  24  // 4
#define RedKey                    11
#define GreenKey                  12
#define YellowKey                 13
#define BlueKey                   14
#define OkKey                     25
#define ExitKey                   16
#define NumKey0                   0
#define NumKey1                   1
#define NumKey2                   2
#define NumKey3                   3
#define NumKey4                   4
#define NumKey5                   5
#define NumKey6                   6
#define NumKey7                   7
#define NumKey8                   8
#define NumKey9                   9
#define HoldKey                   26
#define MixKey                    27
#define SubPageKey                28
#define CancelKey                 30

/* Exported Functions ----------------------------------------------------- */
extern void GxTtx_Init(void);
extern int8_t GxTtx_Enable(void);
extern uint8_t GxTtx_IsnotEnable(void);
extern void GxTtx_SetPid(uint16_t nTtxPid,uint8_t chMagNum,uint8_t chPageNum);
extern void GxTtx_SetKey(uint8_t chTtxKey);
extern void GxTtx_SubtDisable(void);
extern void GxTtx_QuickSearchEnable(void);
extern uint8_t GxTtx_ExitFlag(void);
extern void GxTtx_VbiStart(uint16_t wTtxPid);
extern void GxTtx_VbiStop(void);
extern void GxTtx_TtxStart(uint16_t wTtxPid);
extern void GxTtx_TtxStop(void);
extern void GxTtx_SubtEnable(uint16_t wPid,uint16_t wMagazineNum,uint16_t wPageNum);
extern uint8_t GxTtx_IsnotWorking(void);
extern uint8_t GxTtx_CcIsnotEnable(void);
extern void GxTtx_SetResolution(uint32_t resolution);
extern void GxTtx_SetLang(uint32_t lang);

// for pre-process and the max magazine cache control
extern void GxTtx_TtxPreProcessEnable(void);
extern void GxTtx_TtxPreProcessDisable(void);
extern int32_t GxTtx_TtxPreStart(TeletextPreProcessConfig_t configs);
extern int32_t GxTtx_TtxPreStop(void);
//the function using the following, you must call it before all the AAA function
extern void GxTtx_TtxConfigs(TeletextConfig_t configs);



void ttx_parse_task(void);
void ttx_demux_task(void);
void ttx_subt_get_show_flag(uint8_t *pFlag);
void ttx_subt_get_cur_pid(uint16_t *pPID,uint16_t *pPage,uint16_t *pAcillary);
void ttx_set_cc_page_num(uint8_t chMagNum, uint16_t wPageNum);

__END_DECLS

#endif//#ifndef __COM_TTX_H

