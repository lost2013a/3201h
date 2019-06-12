/**
 *
 * @file        app_common_epg.h
 * @brief
 * @version     1.1.0
 * @date        10/19/2012 15:17:49 PM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_EPG__H__
#define __APP_COMMON_EPG__H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gxepg.h"
#include "gxcore.h"
#include "gui_core.h"
#include <time.h>

//Those time define under GMT:+0   UTC Time
#define SEC_TO_MILLISEC (1000)
//#define SYS_DEFAULT_TIME_UTC (978307200)//Time:2001-01-01 00:00
#define SYS_DEFAULT_TIME_UTC (1420070400UL)//Time:2015-01-01 00:00
#define SYS_INIT_TIME_SEC (946684800) //sec of 2000.1.1 0:0
#define SYS_DEAD_TIME_SEC (2145916800) //sec of 2038.1.1 0:0

enum _ymd
{
    TIME_YMD,
    TIME_DMY,
    TIME_YMD_END
};

enum _gmt_local
{
    TIME_GMT,
    TIME_LOCAL,
    TIME_GL_END
};

enum _summer
{
    TIME_SUMMER_OFF,
    TIME_SUMMER_ON,
    TIME_SUMMER_END
};

typedef struct
{
    enum _ymd           ymd;
    enum _gmt_local     gmt_local;
    enum _summer    summer;
    int32_t             zone;
#define TIME_MODE_IGNORE    (0xffff)
}time_cfg;

typedef struct app_time AppTime;
struct app_time
{
    time_cfg    config;
    time_t      seconds;
    event_list* timer;
    void        (*start)(AppTime*);
    void        (*stop)(AppTime*);
    void        (*sync)(AppTime*,time_t); 
    void        (*mode_set)(AppTime*,time_cfg*);
    void        (*time_get)(AppTime*,char*,size_t); // minsize = 20
    time_t      (*utc_get)(AppTime*);       // need add 1900(Year)
    void        (*time_sync_cb)(AppTime*);
    void        (*init)(AppTime*);
#define MIN_SEC_OFFSET  (11)
};

extern AppTime g_AppTime;
bool app_time_range_valid(time_t gmt_sec);
bool app_month_date_valid(uint16_t year, uint8_t mon, uint8_t day);
time_t app_mktime (time_t year, time_t mon, time_t day, time_t hour, time_t min, time_t sec);




typedef struct time_s
{
    unsigned int year    : 12;
    unsigned int month   : 4;
    unsigned int day     : 5;
    unsigned int hour    : 5;
    unsigned int minute  : 6;
} com_time_t;



typedef struct
{
	 uint8_t gApp_epg_enable ;
	 int32_t msg_get_epg_id ;
	 int32_t msg_get_epg_num_id ;
	 uint32_t sEpg_day ;
	 uint32_t cur_event_count ;
	 uint32_t sOffSetSel ;
	 uint32_t sOldOffset ;
	 uint32_t detail_flag;
	 int get_event_count ;
}epg_get_para;

/*
* ���½ӿ��ṩmenu����
*/


/*
* ����epg����
*/
void app_epg_open(void);

/*
* �ر�epg����
*/
void app_epg_close(void);

/*
* ����ϵͳʱ��,
*/
void app_epg_set_local_time(struct tm *pTime,uint32_t timezoneFlag);

/*
* ��ȡ��ǰ��֮��day�����/��/��/���ڵ���Ϣ
*/
void app_epg_get_time_by_day_offset(struct tm *pLocalTime,int day,uint32_t timezoneFlag);

/*
* ��ȡ��ǰʱ����Ϣ
*/
void app_epg_get_local_time(struct tm *pLocalTime,uint32_t timezoneFlag);

/*
* �˳���ʾEPG��Ϣ���� (����Ϣ������Ŀ�б�EPG)
* �Ƚ����е���
*/
void app_epg_free(void);

/*
* ��ȡp/f epg��Ϣ
*/
GxEpgInfo * app_epg_get_pf_event(uint32_t pos);


/*
* ����ѡ�н�Ŀĳ���EPG��Ϣ(���ص�ǰѡ����EPG)
*/
GxEpgInfo * app_epg_update_event_by_day(uint32_t value,int32_t nListSel,uint32_t checkflag);

/*
* ��ȡĳ���Ӧ������EPG��Ϣ
*/
GxEpgInfo *  app_epg_get_event_info_by_sel(uint32_t nListSel);

/*
* ��ȡһ��EPG����
*/
uint32_t app_epg_get_event_count(void);

/*
* ������ѭ�л�
*/
uint32_t app_epg_switch_day_offset(void);

/*
* ��ȡEPG��Ϣ����
*/
epg_get_para* app_epg_get_para(void);

/*
* ����EPGϵͳ����
*/
void app_epg_reset_get_para(void);

/*
* ͬ�����µ�ǰʱ��
*/
void app_epg_sync_time(void);

/*
* epg��Ϣ�л�ȡ��ʼ������ʱ��
*/
void app_epg_get_event_time(GxEpgInfo *epg_info_temp,struct tm *tm_start,struct tm *tm_end);

/*
* mjd����ת�������ո�ʽ
*/
void  app_epg_convert_mjd_to_ymd( uint16_t   mjd, uint16_t   *year, uint8_t  *month, uint8_t  *day, uint8_t  *weekDay );

/*
* ������ת��mjd��ʽ
*/
void  app_epg_convert_ymd_to_mjd( uint16_t   *mjd, uint16_t   year, uint8_t  month, uint8_t  day);

/*
* ����ת��UTC
*/
void app_epg_convert_to_utc( unsigned short wDate, com_time_t* pTimeOut );



#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_EPG__H__*/

