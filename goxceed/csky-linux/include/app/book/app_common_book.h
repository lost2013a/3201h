#ifndef __APP_COMMON_BOOK_H__
#define __APP_COMMON_BOOK_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "gxtype.h"
#include "gxbook.h"
#include "gxepg.h"
#include "service/gxepg.h"
#include "gxprogram_manage_berkeley.h"
#include "app_common_search.h"

typedef enum
{
	BOOK_STATUS_OK=0,		/*OK*/
	BOOK_STATUS_EXIST ,			/*��ͬԤԼ�Ѵ���*/
	BOOK_STATUS_CONFILCT ,			/*��ͬʱ���Ѵ�������ԤԼ*/
	BOOK_STATUS_OVERDUE ,			/*ԤԼʱ����Ч*/
	BOOK_STATUS_FULL,			/*ԤԼ����*/
	BOOK_STATUS_PARA_ERROR /*��������*/
}book_add_error_t;

typedef struct
{
	uint32_t prog_id;//ԤԼ�Ľ�Ŀ��
	uint32_t prog_id_recall;
	uint32_t event_id;
	time_t  start_time;
	time_t  end_time;
	uint8_t  event_name[36];//�¼�
}book_play;

/*
* ����ԤԼʧ�ܻص���ʾ������ԤԼ��ͻ��ԤԼ������
*/
typedef int (*book_add_event_popmsg_callback)(int ret, uint32_t prog_id,uint32_t start_time,GxBookGet* pEpgBookGet,GxBook* pbooktmp);

typedef struct
{
	GxBookType book_type; /*ԤԼ����*/
	uint32_t prog_id; /*����ԤԼ���Ͳ�������*/
	uint32_t event_id; /*����ԤԼ���Ͳ�������*/
	time_t start_time; /*��ʼʱ��*/
	time_t end_time; /*����ʱ�䣬�������Ϊ��������־�Զ�����ʱ��*/
	uint8_t* event_name; /*����ԤԼ���Ͳ�������*/
	GxBookGet* pEpgBookGet;//ԤԼ��Ϣ
}event_book_para;

/*
* �Ƿ��л�ѡ���ص�����
*/
typedef int (*book_play_popmsg_callback)(book_play book, GxBusPmDataProg   prog);
typedef int (*book_record_popmsg_callback)(book_play book, GxBusPmDataProg   prog);

void* app_book_starttime_check_exist(GxBookType book_type,uint32_t prog_id,uint32_t start_time,GxBookGet* pEpgBookGet);
int8_t app_book_create(GxBookType type,uint32_t prog_id,
	                                   uint32_t event_id,
	                                   time_t start_time,
	                                   time_t end_time,
	                                   uint8_t *event_name);
int8_t app_book_modify(GxBook* pbook);
int32_t app_book_check_trig_ing(void);
/*
* ɾ����Ӧ��Ŀ������ԤԼ(ɾ����Ŀʱ����)
*/
void app_book_delete_prog(uint32_t prog_id);

/*
* ɾ����ӦTP������ԤԼ(ɾ��tp ʱ����)
*/
void app_book_delete_tp(search_fre_list searchlist);



/*
* ���½ӿ��ṩ����˵������е���
*/

void app_book_register_add_event_popmsg_callback(book_add_event_popmsg_callback bookaddeventcallback);
void app_book_register_play_popmsg_callback(book_play_popmsg_callback bookplaycallback);
void app_book_register_record_popmsg_callback(book_record_popmsg_callback bookrecordcallback);


/*
* ��ʼ��ԤԼ����
*/
int8_t app_book_init(void);

/*
* ��ѯԤԼ����(������)
*/
int8_t app_book_query_play(void);

/*
* ����ԤԼ
*/
int32_t app_book_add_event(event_book_para eventbookpara);

/*
* ͬ������ԤԼ������ȹ���
*/
int8_t app_book_sync(GxBookGet* pEpgBookGet,GxBookType type);

/*
* �ж϶�Ӧ��Ŀ��ʱ���Ƿ�ԤԼ����
*/
void* app_book_channel_check_exist(GxBookType book_type,uint32_t prog_id,uint32_t start_time,GxBookGet* pEpgBookGet);

/*
* ɾ��ԤԼ
*/
int8_t app_book_delete(GxBook* pbook);

/*
*��ʼ ����ԤԼ(�յ�gxbus��GXMSG_BOOK_TRIGGER��Ϣ)
*/
void app_book_trigger_start(GxBook* pbook);

/*
* ��������ԤԼ(�յ�gxbus��GXMSG_BOOK_FINISH��Ϣ)
*/
void app_book_trigger_end(GxBook* pbook);

/*
* �������ԤԼ����
*/
int8_t app_book_clear_all(void);

/*
* ��⵱ǰԤԼ��Ŀ�Ƿ����
*/
int8_t app_book_check_exist(GxBookGet* pEpgBookGet,GxBookType type,int32_t book_id, int *ri_Sel);
#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_BOOK_H__*/

