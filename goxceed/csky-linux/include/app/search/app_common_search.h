/**
 *
 * @file        app_common_search.h
 * @brief
 * @version     1.1.0
 * @date        10/18/2012 09:40:49 AM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_SEARCH__H__
#define __APP_COMMON_SEARCH__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <gxtype.h>

#include "service/gxsearch.h"
#include "app_common_play.h"
//#include "app_common_book.h"
//#include "gxbook.h"
#include "gxapp_sys_config.h"

/*
* ����������Ŀͬʱ������չ��������
*/
#define SEARCH_EXTEND_MAX (2)


typedef struct
{
	  uint8_t app_buf_tv[400];
	  uint8_t app_buf_radio[400];
	  uint16_t  app_tv_num ;
	  uint16_t  app_radio_num ;
	  uint16_t tp_num; /*ʵ������TP�������������TP��������£�
	                                tp_numС�����õĸ���*/
	  uint16_t tp_cur; /*��ǰ����TP����*/
	  uint32_t app_tpid[TP_MAX_NUM]; /*ʵ������TP��ӦID���������TP��������£�
	                                ����С�����õĸ���*/
	 uint32_t app_tv_num_perTP[TP_MAX_NUM]; /*ÿ��TP��Ӧ�������ĵ��ӽ�Ŀ��*/
	 uint32_t app_radio_num_perTP[TP_MAX_NUM]; /*ÿ��TP��Ӧ�������Ĺ㲥��Ŀ��*/
	 
}search_result;
  
typedef struct
{
	uint32_t app_fre_array[TP_MAX_NUM];
	uint16_t app_qam_array[TP_MAX_NUM];
	uint16_t app_symb_array[TP_MAX_NUM];
	uint16_t app_fre_tsid[TP_MAX_NUM];
	uint16_t num;
	uint8_t nit_flag;
}search_fre_list;


typedef struct
{
	uint32_t fre_low;
	uint32_t fre_high;
	uint8_t nit_flag; /*�Ƿ񿪻��Զ�NIT������1: NIT������0: ȫƵ������ ������չ֧��*/ 
}startup_search_para;

/*
* �Ƿ��л�ѡ���ص�����
*/
typedef int (*search_ok_popmsg)(void);
typedef int32_t (*search_prog_order)(const void *p1, const void *p2);
typedef	int32_t (*search_prog_check)(GxBusPmDataProg* prog, GxBusPmProgSort* list);//����Ŀ�Ƿ����Ҫ��Ļص�����������Ҫ���Ŀ��Ҫ����������ĳ�Ա��������listָ�벢�ҷ���0��������Ҫ�󷵻�-1����ʹ�øù����������NULL

typedef struct
{
	uint8_t taxis_mode; /* ����ʽ*/
	uint8_t save_flag; /*�Ƿ񱣴��־*/ 
	uint8_t play_flag; /*�Ƿ񲥷ű�־����Ҫ���صĴ���*/  
	                                       // ���ܴ�������������Ҫ�󷵻ص����������Ҫ��
	uint32_t play_pos; /*����ָ����Ŀ*/ 
										   
	const char* widget_search_bar; /*�����������ؼ�����������������Ϊ100
	                                                    ���޽�����������ΪNULL*/
	const char* widget_search_bar_value; /*�������������ʣ�������������ʾΪ100%
	                                                    ���޽��������ʣ�����ΪNULL*/
	search_ok_popmsg app_search_ok_pomsg; 
    search_prog_order app_prog_order;  
    search_prog_check app_prog_check;
}search_ok_msg;


typedef struct
{
	const char * widget_name_strength_bar;  /*�ź�ǿ�Ȱٷ���*/
	const char * widget_name_strength_bar_value;  /*�ź�ǿ��ֵ*/
	const char* widget_name_strength_bar_value_format; /* �ź�ǿ��ֵ��ʽ��db , % */
	char        lock_status; /*1������0ʧ��*/
	char        lock_status_invaild; /*0 in vaild , 1 vaild*/	
	char        unit; /*0 dB , 1 %*/
	                                                                                          
}strength_xml;


typedef struct
{
	const char * widget_name_signal_bar;  /*�ź������ٷ���*/
	const char * widget_name_signal_bar_value; /*�ź�ǿ�Ȱٷ�ֵ��ʾdb*/
	const char * widget_name_error_rate_bar; /*�����ʰٷ���*/
	const char * widget_name_error_rate; /*������ֵ��ʾ
	                                                                 ��ʽ"%d.%02dE-%02d"*/
	char       lock_status;
	char       lock_status_invaild; /*0  vaild , 1 invaild*/	
	char	   unit; /*0 dBuV mode, 1 % mode*/

}signal_xml;


typedef struct
{
	GxMsgProperty_NewProgGet* params;  
	const char * widget_tv_list_name; /*��ʾ������ǰTP�������ƿؼ����粻���ڣ�����ΪNULL*/
	const char * widget_tv_num; /*��ʾ�������������Ƹ����ؼ����粻���ڣ�����ΪNULL*/
	const char * widget_radio_list_name;  /*��ʾ������ǰTP�㲥���ƿؼ����粻���ڣ�����ΪNULL*/
	const char * widget_radio_num;  /*��ʾ������ǰTP�㲥�����ؼ����粻���ڣ�����ΪNULL*/
	uint32_t max_line_num; /*��ʾ�������*/
}search_new_prog_get_msg;


typedef struct
{
	GxMsgProperty_SatTpReply* params;  
	const char * widget_search_progress_bar;  /*�����ٷֱȹ�����*/ 
	const char * widget_search_progress_bar_value; /*�����ٷֱ�ֵ*/ 
	const char * widget_fre_name; /*��ʾ��ǰTPƵ��ֵ�ؼ�����*/ 
	const char * widget_tv_list_name; /*��ʾ������ǰTP�������ƿؼ���
	                                                          ������TP���ؼ���ʾ������粻���ڣ�����ΪNULL*/
	const char * widget_radio_list_name; /*��ʾ������ǰTP�㲥���ƿؼ���
	                                                          ������TP���ؼ���ʾ������粻���ڣ�����ΪNULL*/
}search_sat_tp_reply_msg;

typedef struct
{
	GxSearchExtend searchExtend[SEARCH_EXTEND_MAX];
	uint32_t extendnum;
}search_extend;

typedef struct 
{
	uint32_t fre;
	uint32_t symbol_rate;
	uint32_t qam;
	uint8_t  flag;//�����Ƶ�������־
	

}search_dvbc_param;

typedef int (*search_add_extend_table)(search_extend* searchExtendList);	
void app_search_register_add_extend_table_callback(search_add_extend_table search_extend_call_back);

/*
* ���½ӿ��ṩmenu����
*/

/*
* �����źż��
*/
uint8_t app_demodu_monitor_start(void);

/*
* �ر��źż��
*/
uint8_t app_demodu_monitor_stop(void);

/*
* �ر����к�̨����filter��Դ 
*/
uint8_t app_stop_all_monitor_filter(void);
/*
* ������̨����filter
*/
uint8_t app_start_all_monitor_filter(void);


/*
* ���������н��ܵ��˳����������˳���Ϣ��GXBUSֹͣ����
*/
uint8_t app_search_scan_stop(void);


/*
* �ֶ�����
*/
void app_search_scan_manual_mode(uint32_t fre,uint32_t symbol_rate,uint32_t qam);

/*
* NIT����
*/
void app_search_scan_nit_mode(void);

/*
* ȫƵ������
*/
uint32_t app_search_scan_all_mode(uint32_t begin_fre,uint32_t end_fre,uint32_t symbol_rate,uint32_t qam);

/*
* �ض�Ƶ������
*/
uint32_t app_search_scan_mode(uint32_t *fre,uint16_t size,uint32_t symbol_rate,uint32_t qam);

/*ָ��Ƶ�ʱ�����*/
uint32_t app_search_enum_enum_mode(search_fre_list t_searchFreList);

#ifdef DVB_CA_TYPE_MG312_FLAG
#include "mg312def.h"
#ifdef MG_CAS_VER_3_1_1
int app_win_fengyang_search(void);
int app_win_wudian_search(void);
int app_win_feng_wu_search(void);
#endif
#endif
/*
* ��ȡ�ź�ǿ��
*/
uint32_t app_search_get_pcm_play_signaldb(void);
/*
* �޽�Ŀ�Զ�����
*/
void app_search_startup_auto_scan(startup_search_para startuppara);

/*
* ��Ƶ
*/
status_t app_search_lock_tp(uint32_t fre, uint32_t symb, fe_spectral_inversion_t inversion, fe_modulation_t modulation,uint32_t delayms);


/*
* ��ʾ����������Ŀ��Ϣ(�յ�GXMSG_SEARCH_NEW_PROG_GET��Ϣ)
*/
void app_search_new_prog_get_msg(search_new_prog_get_msg new_prog_get_msg);

/*
* ��ʾ��TP��Ϣ(�յ�GXMSG_SEARCH_SAT_TP_REPLY��Ϣ)
*/
 void app_search_sat_tp_reply_msg(search_sat_tp_reply_msg  sat_tp_reply_msg);

/*
* ������������(�յ�GXMSG_SEARCH_STOP_OK��Ϣ)
*/
 void app_search_stop_ok_msg( search_ok_msg ok_msg);

/*
*NIT��������������(�յ�GXMSG_SI_SUBTABLE_OK ��GXMSG_SI_SUBTABLE_TIME_OUT ��Ϣ)
*/
void app_search_si_subtable_msg(GxMessage * msg);

/*
* �����ӿ�
*/
void app_search_scan_cable_start(search_fre_list searchlist);

/*
*�ź�ǿ����ʾ
*/
void app_search_set_strength_progbar(strength_xml strengthxml);

/*
* �ź�������ʾ 
*/
void app_search_set_signal_progbar(signal_xml singalxml);

/*
* ��ȡ���������Ϣ
*/
search_result* app_search_get_result_para(void);

uint16_t app_enum_search_fre_list_init(void);
search_fre_list* app_enum_search_get_fre_list(void);

uint8_t app_search_get_auto_flag(void);

void app_search_set_auto_flag(uint8_t flag);
float app_float_edit_str_to_value(const char *str);
uint32_t app_search_get_cur_searching_tp_fre(void);
#if (LANGUAGE_UTF8 == LANGUAGE_TYPE)
void app_str_gb2312_convert_utf8(unsigned char* name, unsigned int len );
#endif

#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_SEARCH__H__*/

