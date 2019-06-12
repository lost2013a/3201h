/**
 *
 * @file        app_common_porting_stb_api.c
 * @brief
 * @version     1.1.0
 * @date        11/30/2012 09:47:49 AM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_PORTING_CA_API_H__
#define __APP_COMMON_PORTING_CA_API_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "app_common_table_pmt.h"
#include "app_common_play.h"
/*wufei add for CDCA*/
#ifndef LANGUAGE_CHINESE
#define LANGUAGE_CHINESE ("Chinese")
#endif
#ifndef LANGUAGE_ENGLISH
#define LANGUAGE_ENGLISH ("English")
#endif

/*
* ��ͷ�ļ������ṩ��������õ�CA�����ӿ�
* �����ӿ�ͳһ���壬���������޸Ľӿڶ��塣
* ��Ӧ����������app\ca\api xxx.cʵ�֣���ͬCA����ʵ�����ʵ�ֶ�Ӧ���ܡ�
*/

#define CAS_NAME                  ("cas")
#define CAS_PRINT_OPEN				1
#define ADS_PRINT_OPEN				1





typedef enum
{
	DVB_CA_TYPE_NONE=0,		/*��CA*/
	DVB_CA_TYPE_BY,                   /*��ԶCA*/
	DVB_CA_TYPE_CDCAS30 ,			/*TF 3.0 �汾CA*/
	DVB_CA_TYPE_KN ,
	DVB_CA_TYPE_XINSHIMAO ,			/*XINSHIMAO*/
	DVB_CA_TYPE_DIVITONE ,
	DVB_CA_TYPE_DSCAS50 ,
	DVB_CA_TYPE_DVT, /*sumavision ca*/
	DVB_CA_TYPE_QILIAN,
	DVB_CA_TYPE_MG, /*san zhou*/
	DVB_CA_TYPE_QZ,/*ȫ��*/
	DVB_CA_TYPE_GOS,                /*��ͨCA*/
	DVB_CA_TYPE_GY,
	DVB_CA_TYPE_WF,/*�ɶ���*/
	DVB_CA_TYPE_ABV53,

	DVB_CA_TYPE_TR,/*����CA*/
	DVB_CA_TYPE_CTI,/*��ͨca*/
	DVB_CA_TYPE_MG312, /*san zhou V3.1.2*/
	
	DVB_CA_TYPE_ABV38,/* ABV 3.8-version */
	
    DVB_CA_TYPE_KP,/*���CA,�޿�CA,���������������CA֮��*/
	DVB_CA_TYPE_SC, /*�״�CA*/ 
	DVB_CA_TYPE_CDCASHS ,			/*TF �߰� �汾CA*/
	DVB_CA_TYPE_DVT_HS20, /*sumavision ca*/
	 DVB_CA_TYPE_XG,//xinguang cas
	 DVB_CA_TYPE_HTT, /*����ͨ�޿�CA*/
	DVB_CA_TYPE_UTI, /* ����̫�͸߰�CA */ 
	/*��չ������CA���Ͷ���*/
	DVB_CA_TYPE_MAX
}dvb_ca_type_t;

typedef enum
{
	DVB_CA_BASE_INFO=0,		       /*������Ϣ*/
	DVB_CA_OPERATOR_INFO,		/*��Ӫ����Ϣ*/
	DVB_CA_EMAIL_INFO,			/*�ʼ�*/
	DVB_CA_ENTITLE_INFO ,			/*��Ȩ*/
	DVB_CA_DETITLE_INFO,                 /*����Ȩ*/
	DVB_CA_EMERGENCY_INFO,           /*Ӧ���㲥*/
	DVB_CA_ROLLING_INFO,                /*OSD������Ϣ*/
	DVB_CA_FINGER_INFO,                  /*ָ��*/
	DVB_CA_CARD_UPDATE_INFO,        /*������*/
	DVB_CA_FETURE_INFO,                   /*����ֵ*/
	DVB_CA_IPPV_POP_INFO,                /*IPPV�������Ϣ*/
	DVB_CA_IPPT_POP_INFO,                /*IPPT�������Ϣ*/
	DVB_CA_IPPV_PROG_INFO,             /*IPPV�ѹ����Ŀ�б���Ϣ*/
	DVB_CA_IPPV_SLOT_INFO,             /*IPPVǮ���б���Ϣ*/
//	DVB_CA_CHILD_CARD_INFO,             /*�ӿ���Ϣ*/
	DVB_CA_MOTHER_CARD_INFO,             /*ĸ����Ϣ*/
	DVB_CA_CHANGE_PIN_INFO,             /*�޸�������Ϣ*/
	DVB_CA_PROGRESS_INFO,             /*���ܿ�����������Ϣ*/
	DVB_CA_RATING_INFO,                 /*���˼�����Ϣ*/
	DVB_CA_WORK_TIME_INFO,           /*����ʱ����Ϣ*/
	DVB_CA_CURTAIN_INFO,           /*������Ϣ*/
	DVB_CA_PAIRED_INFO,           /*�����Ϣ*/
	
	DVB_CA_PRE_AUTH_INFO, 		  /*Ԥ��Ȩ��Ϣ*/
	/*��չ��CA������������*/
	DVB_CA_OTA, /*ota����*/
	DVB_CA_NIT, /*NIT virsion change*/
	#ifdef DVB_CA_TYPE_DS_CAS50_FLAG
	DVB_CA_CONDITION_SEARCH,/*����CA ��������*/
	#endif /*DVB_CA_TYPE_DS_CAS50_FLAG*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	DVB_CA_CONSUME_HISTORY,			/*��ʷ��ֵ/���Ѽ�¼*/
	#endif
	/*
	* ad
	*/
	DVB_AD_BMP,
	DVB_AD_GIF,
	DVB_AD_SCROLL_BMP,
	DVB_CA_MAX_INFO
}dvb_ca_data_type_t;

typedef enum
{
	DVB_CA_EMAIL_FLAG_HIDE=0,		       /*hide email flag */
	DVB_CA_EMAIL_NEW,		/*new email flag show*/
	DVB_CA_EMAIL_EXHAUST			/*email space exhaust*/
}dvb_ca_email_flag_type_t;

typedef enum
{
	DVB_CA_EMAIL_PROMTP_NONE=0,
	DVB_CA_EMAIL_PROMTP_HIDE,
	DVB_CA_EMAIL_PROMTP_SHOW,
	DVB_CA_EMAIL_PROMTP_TRANS_HIDE,
	DVB_CA_EMAIL_PROMTP_MAX
}dvb_ca_email_prompt_type_t;

typedef enum
{
	DVB_CA_ROLLING_FLAG_NONE=0,
	DVB_CA_ROLLING_FLAG_HIDE,
	DVB_CA_ROLLING_FLAG_SHOW,
	DVB_CA_ROLLING_FLAG_RESET,
	#ifdef DVB_CA_TYPE_DS_CAS50_FLAG
	DVB_CA_ROLLING_FLAG_TRANS_HIDE,
	#endif /*DVB_CA_TYPE_DS_CAS50_FLAG*/
	DVB_CA_ROLLING_FLAG_CLEAR,
	DVB_CA_ROLLING_FLAG_MAX
}dvb_ca_rolling_message_flag_type_t;

typedef enum
{
	DVB_CA_FINGER_FLAG_NONE=0,
	DVB_CA_FINGER_FLAG_HIDE,
	DVB_CA_FINGER_FLAG_SHOW,
	DVB_CA_FINGER_FLAG_TRANS_HIDE,
	DVB_CA_FINGER_FLAG_MAX
}dvb_ca_finger_flag_type_t;

typedef enum
{
	DVB_CA_FEED_FLAG_NONE=0,
	DVB_CA_FEED_FLAG_HIDE,
	DVB_CA_FEED_FLAG_SHOW,
	DVB_CA_FEED_FLAG_MAX
}dvb_ca_feed_flag_type_t;




/*
* ��ʼ��
*/
typedef uint8_t (*app_cas_update_dvb_ca_flag_callback)(void);
uint8_t app_cas_update_dvb_ca_flag(void);

typedef uint8_t (*app_cas_init_callback)(void);
uint8_t app_cas_init(void);

/*
* �ر�
*/
typedef uint8_t (*app_cas_close_callback)(void);
uint8_t app_cas_close(void);

/*
* ���ܿ����룬����CA�贫��Ӧ�����ݡ�����
*/
typedef uint8_t (*app_cas_api_card_in_callback)(char* ,uint8_t );
uint8_t app_cas_api_card_in(char* atr,uint8_t len);

/*
* ���ܿ��γ�
*/
typedef uint8_t (*app_cas_api_card_out_callback)(void);
uint8_t app_cas_api_card_out(void);

/*
* ecm,emm filter
*/
/*
* �ͷ�ecm filter , ��̨��ֹͣ���š��ָ��������õ�����µ���
*/
typedef uint8_t (*app_cas_api_release_ecm_filter_callback)(void);
uint8_t	app_cas_api_release_ecm_filter(void);
/*
* ����ecm filter , ��̨���ã���ЩCA������Ҫ�󶨽���ͨ��
* ���ݲ�ͬCAʵ��ʵ�֡�
*/
typedef uint8_t (*app_cas_api_start_ecm_filter_callback)(play_scramble_para_t *);
uint8_t app_cas_api_start_ecm_filter(play_scramble_para_t *playPara);
/*
* �ͷ�emm filter, �л�Ƶ�㡢�ָ��������õ�����µ���
*/
typedef uint8_t (*app_cas_api_release_emm_filter_callback)(void);
uint8_t	app_cas_api_release_emm_filter(void);
/*
* ����emm filter, ��̨���˵�CAT�����
*/
typedef uint8_t (*app_cas_api_start_emm_filter_callback)(uint16_t);
uint8_t app_cas_api_start_emm_filter(uint16_t emm_pid);


/*
* �ж��Ƿ��ӦCAϵͳ������
* ����TURE -- ��ӦCAϵͳCA������
* ����FALSE -- �Ƕ�ӦCAϵͳCA������
*/
typedef bool (*app_cas_api_check_cat_ca_descriptor_valid_callback)(uint8_t *,uint32_t );
bool app_cas_api_check_cat_ca_descriptor_valid(uint8_t *sectionData,uint32_t CA_system_id);
/*
* �ж��Ƿ��ӦCAϵͳ������
* ����TURE -- ��ӦCAϵͳCA������
* ����FALSE -- �Ƕ�ӦCAϵͳCA������
*/
typedef bool (*app_cas_api_check_pmt_ca_descriptor_valid_callback)(uint8_t *,uint32_t );
bool app_cas_api_check_pmt_ca_descriptor_valid(uint8_t *sectionData,uint32_t CA_system_id);


uint32_t app_cas_api_check_bus_pmt_ca_valid(uint16_t ca_system_id,uint16_t ele_pid,uint16_t ecm_pid);
/*��ʾ��Ϣ�������򡢹�����Ϣ��*/
/*
* �ж��Ƿ�CA��ʾ��Ϣ
*/
typedef uint8_t (*app_cas_api_is_ca_pop_msg_type_callback)(uint8_t);
uint8_t app_cas_api_is_ca_pop_msg_type(uint8_t type);

/*
* ��ʾ����������Ȩ����ʾ
*/
typedef int32_t (*app_cas_api_pop_msg_exec_callback)(uint8_t);
int32_t app_cas_api_pop_msg_exec(uint8_t type);
/*
* ������ʾCA�����Ϣ����OSD������Ϣ���ʼ����ѣ�ָ�Ƶ�
*/
typedef int32_t (*app_cas_api_osd_exec_callback)(void);
int32_t app_cas_api_osd_exec(void);
/*
* ʵ��CA�������ܣ���IPPV/IPPT����򣬳��������OSD������Ϣ���µ�
*/
typedef int32_t (*app_cas_api_gxmsg_ca_on_event_exec_callback)(GxMessage *);
int32_t app_cas_api_gxmsg_ca_on_event_exec(GxMessage * msg);


/*
* ���½ӿ��ṩCA�˵�����
*/
typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	uint32_t pos ;                             /*���*/
	uint32_t ID;                                /*��Ӧ������Ϣö��,��ͬCAö�ٶ�����ڲ��컯.����ö�ٶ���
	                                                    ��app/xxxcas/include*/
	/******��չ*/															/******��չ*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	uint32_t number;					/*��Ŀ��Ӧ�̵����*/
	uint32_t type;						/*��������eg. FREE PPC PPV*/
	#endif
	#if defined (DVB_CA_TYPE_UTI_CAS_FLAG)
	uint32_t type;						/*��������eg. FREE PPC PPV*/
	#endif
}ca_get_date_t;

typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	uint32_t pos ;                             /*���*/
	uint32_t totalnum;                     /* ����*/
	uint32_t newnum;                      /*δ������*/
	uint32_t emptynum;                    /*empty num*/
	/******��չ*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	uint32_t type;						/*��������eg. FREE PPC PPV*/
	#endif
	#if defined (DVB_CA_TYPE_UTI_CAS_FLAG)
	uint32_t type;						/*��������eg. FREE PPC PPV*/
	#endif
}ca_get_count_t;

typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	uint32_t pos ;                             /*���*/
	/******��չ*/
}ca_delete_data_t;

typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	char* pin;                           /*����*/
	uint8_t  buystate;                      /*�Ƿ���:0-- ������1-- ����*/
	void* buydata;                           /*��������ָ�룬��ͬCA���ڲ���*/
	/******��չ*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	uint32_t serial_number;					/*��Ŀ����ŵ�ǰ���Ǻ���*/
	uint32_t pay_type;						/*��������eg. per min or per view*/	
	uint8_t reset_num;				/*������ظ�����*/
	uint32_t pos;                    /*����Ľ�Ŀ���*/
	uint16_t period;				/*��������*/
	#endif
}ca_buy_ipp_t;

typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	uint32_t pos ;
	uint32_t  state; /*0: init 1: read feed data 2: write feed data */
	/******��չ*/
}ca_mother_child_card_t;

typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	char* oldpin;                           /*������*/
	char* newpin;                           /*������*/
	char* newconfirmpin;                           /*ȷ��������*/
	int32_t errorCode;  /*wufei add for error verify 0:success 1:fail*/
	/******��չ*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	uint8_t reset_num;				/*������ظ�����*/
	#endif
}ca_pin_t;


typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	char* pin;                           /*����*/
	uint8_t rate;                           /*�³��˼���*/

	/******��չ*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	uint8_t reset_num;				/*������ظ�����*/
	#endif
}ca_rating_t;

typedef struct
{
	dvb_ca_data_type_t date_type;  /*CA��������*/
	char* pin;                           /*����*/
	char* starttime;
	char* endtime;
//	uint8_t starthour;                           /*��ʼСʱ*/
//	uint8_t startmin;                           /*��ʼ����*/
//	uint8_t startsec;                           /*��ʼ��*/

//	uint8_t endhour;                           /*����Сʱ*/
//	uint8_t endmin;                           /*��������*/
//	uint8_t endsec;                           /*������*/

	/******��չ*/
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	uint8_t reset_num;				/*������ظ�����*/
	#endif

}ca_work_time_t;

/*
*  ��ȡ��Ӧ����֮ǰ����ʼ�����ݹ���
(һ�㴴����Ӧ����֮ǰ��create�е���)��
* ���ʼ���ʼ�����Ȩ��
*/
typedef int32_t (*app_cas_api_init_data_callback)(dvb_ca_data_type_t);
int32_t app_cas_api_init_data(dvb_ca_data_type_t date_type);


/*
* ��ȡ��ӦCA��Ϣ
* date_type -- CA��Ϣ����
* pos -- ���
* ID -- ��Ӧ������Ϣö��
* (�����ӿ�ͳһ�����ַ�������ֵ�ɲ�ͬCA����ת��)
*/
typedef char* (*app_cas_api_get_data_callback)(ca_get_date_t*);
char * app_cas_api_get_data(ca_get_date_t *data);

/*
* ��ȡCA��Ϣ����(��̬)
*/
typedef uint8_t (*app_cas_api_get_count_callback)(ca_get_count_t*);
uint8_t app_cas_api_get_count(ca_get_count_t *data);

/*
* ɾ������ѡ������
* date_type -- CA��Ϣ����
* pos -- ���
*/
typedef bool (*app_cas_api_delete_callback)(ca_delete_data_t *);
bool app_cas_api_delete(ca_delete_data_t *data);

/*
* ɾ����������
* date_type -- CA��Ϣ����
*/
typedef bool (*app_cas_api_delete_all_callback)(ca_delete_data_t *);
bool app_cas_api_delete_all(ca_delete_data_t *data);

/*
* ������IPPV/IPPT��
*/
typedef uint8_t (*app_cas_api_buy_ipp_callback)(ca_buy_ipp_t *);
uint8_t app_cas_api_buy_ipp(ca_buy_ipp_t *data);


/*
* ��ȡӦ���㲥״̬
*/
typedef uint8_t (*app_cas_api_get_lock_status_callback)();
uint8_t app_cas_api_get_lock_status();

/*
* �ӿ�д��ι������
*/
typedef char* (*app_cas_api_feed_mother_child_card_callback)(ca_mother_child_card_t *);
char* app_cas_api_feed_mother_child_card(ca_mother_child_card_t *data);

/*
* �޸�����
*/
typedef char* (*app_cas_api_change_pin_callback)(ca_pin_t*);
char* app_cas_api_change_pin(ca_pin_t* data);


typedef char* (*app_cas_api_verify_pin_callback)(ca_pin_t*);
char* app_cas_api_verify_pin(ca_pin_t* data);



/*
* �޸ĳ��˼���
*/
typedef char* (*app_cas_api_change_rating_callback)(ca_rating_t*);
char* app_cas_api_change_rating(ca_rating_t* data);

/*
* �޸Ĺ���ʱ��
*/
typedef char* (*app_cas_api_change_worktime_callback)(ca_work_time_t*);
char* app_cas_api_change_worktime(ca_work_time_t* data);
#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
/*
*�ۿ����˼���Ŀ
*/
typedef char* (*app_cas_api_watch_maturity_callback)(ca_rating_t*);
char* app_cas_api_watch_maturity(ca_rating_t* data);

/*
* ��ȡ�ʼ�״̬
*/
typedef uint8_t (*app_cas_api_get_email_status_callback)();
uint8_t app_cas_api_get_email_status();

/*
* ��ȡOSD����״̬
*/
typedef uint8_t (*app_cas_api_get_osdrolling_status_callback)();
uint8_t app_cas_api_get_osdrolling_status();
#endif

#ifdef DVB_CA_TYPE_UTI_CAS_FLAG
typedef char* (*app_cas_api_watch_maturity_callback)(ca_rating_t*);
char* app_cas_api_watch_maturity(ca_rating_t* data);
#endif 

typedef struct {
	char*   name;
	int     key;
	void*   buf;
	size_t  size;
} GxMsgProperty0_OnEvent;


int app_cas_api_on_event(int key, const char* name, void* buf, size_t size);

typedef struct APP_CAS_API_ControlBlock_s
{
	app_cas_init_callback m_cas_init_callback;//caģ���ʼ��
 	app_cas_close_callback m_cas_close_callback;
	app_cas_api_card_in_callback m_cas_api_card_in_callback;//���ܿ�����ص�
	app_cas_api_card_out_callback m_cas_api_card_out_callback;//���ܿ��Ƴ��ص�
	app_cas_api_release_ecm_filter_callback m_cas_api_release_ecm_filter_callback;
	app_cas_api_start_ecm_filter_callback m_cas_api_start_ecm_filter_callback;//���˵�Pmt������
	app_cas_api_release_emm_filter_callback m_cas_api_release_emm_filter_callback;
	app_cas_api_start_emm_filter_callback m_cas_api_start_emm_filter_callback;//���˵�CAT������
	app_cas_api_check_cat_ca_descriptor_valid_callback m_cas_api_check_cat_ca_descriptor_valid_callback;
	app_cas_api_check_pmt_ca_descriptor_valid_callback m_cas_api_check_pmt_ca_descriptor_valid_callback;
	app_cas_api_is_ca_pop_msg_type_callback m_cas_api_is_ca_pop_msg_type_callback;//ca��Ϣ�ж�
	app_cas_api_pop_msg_exec_callback m_cas_api_pop_msg_exec_callback;//����ca��Ϣ��
	app_cas_api_osd_exec_callback m_cas_api_osd_exec_callback;//ca ��Ϣ(��ʱ������)
	app_cas_api_gxmsg_ca_on_event_exec_callback m_cas_api_gxmsg_ca_on_event_exec_callback;//ca�¼�
	app_cas_api_init_data_callback m_cas_api_init_data_callback;
	app_cas_api_get_data_callback m_cas_api_get_data_callback;//��ȡ�˵�����
	app_cas_api_get_count_callback m_cas_api_get_count_callback;
	app_cas_api_delete_callback m_cas_api_delete_callback;
	app_cas_api_delete_all_callback m_cas_api_delete_all_callback;
	app_cas_api_buy_ipp_callback m_cas_api_buy_ipp_callback;
	app_cas_api_get_lock_status_callback m_cas_api_get_lock_status_callback;
	app_cas_api_feed_mother_child_card_callback m_cas_api_feed_mother_child_card_callback;
	app_cas_api_change_pin_callback m_cas_api_change_pin_callback ;
	app_cas_api_verify_pin_callback m_cas_api_verify_pin_callback ;
	app_cas_api_change_rating_callback m_cas_api_change_rating_callback;
	app_cas_api_change_worktime_callback m_cas_api_change_worktime_callback;
	
	#if (defined DVB_CA_TYPE_ABV_CAS38_FLAG || defined DVB_CA_TYPE_ABV_CAS53_FLAG)
	app_cas_api_watch_maturity_callback m_cas_api_watch_maturity_callback;
	app_cas_api_get_email_status_callback m_cas_api_get_email_status_callback;
	app_cas_api_get_osdrolling_status_callback m_cas_api_get_osdrolling_status_callback;
	#endif
	#ifdef DVB_CA_TYPE_UTI_CAS_FLAG
	app_cas_api_watch_maturity_callback m_cas_api_watch_maturity_callback;
	#endif
}APP_CAS_API_ControlBlock_t;

#if CAS_PRINT_OPEN

#define CAS_Dbg(...)                          do {                                            \
                                                    printf("[cas]\t");                        \
                                                    printf(__VA_ARGS__);                        \
                                                } while(0)
#define CAS_DUMP(str, ptr, size)                                                                    \
                    do {                                                                        \
                        int i;                                                                  \
                            printf("\t\%s  len=%d\n\t", (str), (size));     \
                        if (size != 0) {                                                        \
                            for (i = 0; i < (size); i++) {                                      \
                                printf("0x%02x,", (ptr)[i]);                                      \
                            }                                                                   \
                            printf("\n\t\n");                               \
                        }                                                                       \
                    } while (0)
#define CA_FAIL(...) do {                                            \
                                                    printf("[cas] CA_FAIL %s %d\t",__FILE__,__LINE__);                        \
                                                    printf(__VA_ARGS__);                        \
                                                } while(0)
#define CA_ERROR(...) do {                                            \
                                                    printf("[cas] CA_ERROR %s %d\t",__FILE__,__LINE__);                        \
                                                    printf(__VA_ARGS__);                        \
                                                } while(0)
#else
#define CAS_Dbg(...)                          do {                                            \
                                                } while(0)
#define CAS_DUMP(str, ptr, size)                                                                    \
                    do {                                                                        \
                    } while (0)
#define CA_FAIL(...) do {                                            \
                                                } while(0)
#define CA_ERROR(...) do {                                            \
                                                } while(0)

#endif
#if ADS_PRINT_OPEN
#define ADS_Dbg(...)                          do {                                            \
													printf("[ads]\t");						  \
													printf(__VA_ARGS__);						\
                                                } while(0)
#define ADS_DUMP(str, ptr, size)                                                                    \
                    do {                                                                        \
                        int i;                                                                  \
                            printf("\t\%s  len=%d\n\t", (str), (size));     \
                        if (size != 0) {                                                        \
                            for (i = 0; i < (size); i++) {                                      \
                                printf("0x%02x,", (ptr)[i]);                                      \
                            }                                                                   \
                            printf("\n\t\n");                               \
                        }                                                                       \
                    } while (0)
#define ADS_FAIL(...)		 do {                                            \
                                                    printf("[ADS] AD_FAIL %s %d\t",__FILE__,__LINE__);                        \
                                                    printf(__VA_ARGS__);                        \
                                                } while(0)
#define ADS_ERROR(...) 		do {                                            \
                                                    printf("[ADS] AD_ERROR %s %d\t",__FILE__,__LINE__);                        \
                                                    printf(__VA_ARGS__);                        \
                                                } while(0)
#else
#define ADS_Dbg(...)                          do {                                            \
                                                } while(0)
#define ADS_DUMP(str, ptr, size)                                                                    \
                    do {                                                                        \
                    } while (0)
#define ADS_FAIL(...) 		do {                                            \
                                                } while(0)
#define ADS_ERROR(...)		 do {                                            \
                                                } while(0)
#endif
#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_PORTING_CA_API_H__*/

