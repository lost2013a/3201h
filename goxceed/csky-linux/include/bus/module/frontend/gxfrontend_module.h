#ifndef __GX_FRONTEND_MODULE_H__
#define  __GX_FRONTEND_MODULE_H__

#include "gxcore.h"
#include "gxtype.h"

#ifdef LINUX_OS
#include <linux/dvb/frontend.h>
#else
#include "frontend/frontend.h"
#endif

__BEGIN_DECLS

#define GXBUS_FRONTEND_UNICABLE "frontend>unicable"///
#define GXBUS_FRONTEND_UNICABLE_YES 1///
#define GXBUS_FRONTEND_UNICABLE_NO  0///
#define FRONTEND_MAX        (2)

#define FRONTEND_CONFIG_NUM        "frontend>num"    ///< 该方案有几个tuner
#define FRONTEND_CONFIG_TUNER0     "frontend>tuner0" ///< 第一个tuner的类型
#define FRONTEND_CONFIG_TUNER1     "frontend>tuner1" ///< 第二个tuner的类型
#define FRONTEND_CONFIG_WATCH_TIME "frontend>watch"  ///< 监控的间隔时间
#define FRONTEND_CONFIG_WATCH_COUNT "frontend>watch_count"  ///< 监控的次数，当监控次数》=配置值，监控检测到的状态才有效
#define FRONTEND_DISEQC_MAX_CMD	   (6)

typedef enum {
	FRONTEND_DVB_C,
	FRONTEND_DVB_S,
	FRONTEND_DVB_S2,
	FRONTEND_DIRECTV,
	FRONTEND_DVB_T,
	FRONTEND_DTMB,
	FRONTEND_DVB_T2,
	FRONTEND_ATSC_T,
	FRONTEND_ATSC_C,
} GxFrontendType;

typedef struct {
	int32_t  dev;
	handle_t demux;

	int32_t   tuner;
	int32_t   fre;
	int32_t   sat22k;
	int32_t   symb;
	fe_modulation_t  qam;
	fe_sec_voltage_t polar;
	fe_bandwidth_t   bandwidth;
	GxFrontendType   type;
	int32_t    type_1501; // 1501 有两种工作模式，dtmb或者
	uint8_t    data_plp_id;
	uint8_t    common_plp_exist;
	uint8_t    common_plp_id;
	uint8_t       if_channel_index;
	uint16_t    lnb_index;
	uint16_t    centre_fre;
	int32_t   	 if_fre;
}GxFrontend;

typedef struct {
	uint32_t snr;
	uint32_t error_rate;
} GxFrontendSignalQuality;

typedef enum {
	DiSEQC10 =0,
	DiSEQC11,
	DiSEQC12
} GxFrontendDiseqcType;

typedef struct {
	uint32_t  b22k;
	uint32_t chDiseqc;
	fe_sec_voltage_t bPolar;
} GxFrontendDiseqc10;

typedef struct {
	uint32_t b22k;
	uint32_t chCom;
	uint32_t chUncom;
	fe_sec_voltage_t bPolar;
} GxFrontendDiseqc11;

typedef enum {
	DISEQC_LIMIT_WEST   = 0,
	DISEQC_DRIVE_WEST   = 1,
	DISEQC_LIMIT_EAST   = 2,
	DISEQC_DRIVE_EAST   = 3,
	DISEQC_STOP         = 4,
	DISEQC_LIMIT_OFF    = 5,
	DISEQC_STORE_NN     = 6,
	DISEQC_GOTO_NN      = 7,
	DISEQC_GOTO_XX      = 8,
	DISEQC_SET_POSNS    = 9
} GxFrontendDiseqc12Ctr;

typedef struct {
	uint8_t m_chParam0; // sat postion or fisrt param of goto x.x
	uint8_t m_chParam1; // second param of goto x.x
	int8_t  m_chParam2; // sit longitude
	int8_t  m_chParam3; // sit latitude
} GxFrontendDiseqc12Param;

typedef struct {
	uint8_t CmdCount;
	GxFrontendDiseqc12Ctr DiseqcControl[FRONTEND_DISEQC_MAX_CMD];
	GxFrontendDiseqc12Param DiSEqC12Params[FRONTEND_DISEQC_MAX_CMD];
} GxFrontendDiseqc12;

typedef struct {
	GxFrontendDiseqcType type;
	union {
		GxFrontendDiseqc10 params_10;
		GxFrontendDiseqc11 params_11;
		GxFrontendDiseqc12 params_12;
	} u;
} GxFrontendDiseqcParameters;

typedef struct {
	int32_t                       tuner;//tuner号
	GxFrontendDiseqcParameters    diseqc;
} GxFrontendDiseqc;

typedef enum {
	FRONTEND_CR12,
	FRONTEND_CR23,
	FRONTEND_CR34,
	FRONTEND_CR45,
	FRONTEND_CR56,
	FRONTEND_CR67,
	FRONTEND_CR78,

	FRONTEND_QPSK14,//dvbs2
	FRONTEND_QPSK13,
	FRONTEND_QPSK25,
	FRONTEND_QPSK12,
	FRONTEND_QPSK35,
	FRONTEND_QPSK23,
	FRONTEND_QPSK34,
	FRONTEND_QPSK45,
	FRONTEND_QPSK56,
	FRONTEND_QPSK89,
	FRONTEND_QPSK910,
	FRONTEND_8PSK35,
	FRONTEND_8PSK23,
	FRONTEND_8PSK34,
	FRONTEND_8PSK56,
	FRONTEND_8PSK89,
	FRONTEND_8PSK910
} GxFrontendModulation;

typedef struct {
	GxFrontendType          type;
	GxFrontendModulation    modulation;
} GxFrontendInfo;

typedef struct {
	uint16_t set_tp;
	uint16_t set_unlock_ts;
} fronted_set_status;

typedef struct {
	fe_modulation_t constellation;
	fe_guard_interval_t guard_interval;
	fe_code_rate_t code_rate_HP;
}GxFrontend_FrontendInfo;

extern int32_t GxFrontend_SetTp(GxFrontend *para);

extern void GxFrontend_StopMonitor(int32_t tuner);

extern void GxFrontend_StartMonitor(int32_t tuner);

extern int32_t GxFrontend_QueryFrontendStatus(int32_t tuner);

extern int32_t GxFrontend_QueryStatus(int32_t tuner);

extern uint32_t GxFrontend_GetStrength(int32_t tuner);

extern int32_t GxFrontend_GetQuality(int32_t tuner,GxFrontendSignalQuality* sq);

extern int32_t GxFrontend_CleanRecord(int32_t tuner);

extern int32_t GxFrontend_CleanRecordPara(int32_t tuner);

extern void GxFrontend_SetDiseqc(GxFrontendDiseqc *para);

extern int32_t GxFrontend_GetCurFre(int32_t tuner, GxFrontend* fre);

extern int32_t GxFrontend_GetInfo(int32_t frontend, GxFrontendInfo* info);

extern int32_t GxFrontend_GetFrontendInfo(int32_t tuner, GxFrontend_FrontendInfo* info);

extern handle_t GxFrontend_IdToHandle(int32_t tuner);

extern void GxFrontend_ForceExit(char* flag);

extern void GxFrontend_ForceExitEx(int32_t tuner);

extern void GxFrontend_SetVoltage(int32_t tuner, fe_sec_voltage_t polar);

extern void GxFrontend_Set22K(int32_t tuner, int32_t sat22k);

extern void GxFrontendOccur(int32_t tuner);

extern int GxFrontendGetSemCount(int32_t tuner);

extern void GxFrontendClearErrFreFlag(void);

extern void GxFrontend_SetUnlock(int32_t tuner);

extern bool GxFrontend_UserSet(uint32_t tuner, int32_t status, GxFrontendSignalQuality sq);

extern int32_t GxFrontend_GetEvent(int32_t tuner,struct dvb_frontend_event* event);

extern int32_t GxFrontend_GetDemodInfo(int32_t tuner,struct dvb_frontend_info* info);

extern int32_t  GxFrontend_Disconnect(GxFrontend *para, int force);

extern void GxFrontend_StartMonitorStrenthQuality(void);

extern void GxFrontend_StopMonitorStrenthQuality(void);

extern int32_t GxFrontend_GetUnicableIffFreq(int32_t tuner,unsigned short *tone);

__END_DECLS

#endif

