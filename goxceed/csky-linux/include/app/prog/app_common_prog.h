/**
 *
 * @file        app_common_prog.h
 * @brief
 * @version     1.1.0
 * @date        10/19/2012 15:53:49 PM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_PROG__H__
#define __APP_COMMON_PROG__H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gxprogram_manage_berkeley.h"
#include "gxapp_sys_config.h"

typedef struct userlist
{
	uint32_t* id_arry;
	uint32_t count;
}userlist_t;

typedef enum prog_sort_type
{
	PROG_SORT_DEFAULT,
	PROG_SORT_SERVICE_ID,
	PROG_SORT_PROG_NAME,
	PROG_SORT_FREE_CA,
}prog_sort_type_e;

typedef enum prog_sort_order
{
	PROG_SORT_POSITIVE,
	PROG_SORT_REVERSE
}prog_sort_order_e;

typedef struct
{
	GxBusPmViewInfo SysInfo;
	uint32_t id;
}play_prog;

typedef enum prog_edit_type
{
	PROG_EDIT_LOCK,
	PROG_EDIT_DEL,
	PROG_EDIT_FAV,
	PROG_EDIT_SKIP,
	PROG_EDIT_MOVE
}prog_edit_type_e;

typedef struct {
	uint8_t change_flag;
	uint32_t prog_id;
	uint32_t prog_pos;
	uint32_t lock_flag;
	uint32_t fav_flag;
	uint32_t mov_flag;
	uint32_t skip_flag;
	uint32_t del_flag;
	char prog_name[MAX_PROG_NAME];
} App_proedit_arr; 

#if MEDIA_SUBTITLE_SUPPORT
#define AUDIO_MAX_NUM    10
#define MAX_LANG_NAME_LEN    32
typedef struct _AudioList_ 
{
	uint32_t audiotype; 
	uint16_t id; 
	char name[MAX_LANG_NAME_LEN]; 
} AudioList_t; 
typedef struct _AudioLang_
{
	uint32_t audioLangCnt; 
	AudioList_t audioLangList[AUDIO_MAX_NUM];  
} AudioLang_t; 
#endif 

void app_prog_userlist_resume(void);
void app_prog_userlist_save(uint32_t* id_arry,uint32_t num);
void app_prog_get_playing_record(play_prog** pprecord);
void app_prog_get_old_play_prog(play_prog** ppold); 
int32_t app_prog_get_pos_in_group_by_id(uint32_t prog_id,uint32_t *ppos);
void app_prog_play_para_lock(void);
void app_prog_play_para_unlock(void);
void app_prog_mutex_lock(void);
void app_prog_mutex_unlock(void);

/*
* ���½ӿ��ṩmenu����
*/

/*
* ��ʼ�����Ž�Ŀ����
*/
void app_prog_init_playing(void);

/*
* ��Ŀ��������
*/
uint32_t app_prog_set_sort_mode(prog_sort_type_e SortType, prog_sort_order_e SortOrder);

/*
* ˽������ȹ����ʼ��
*/
void app_prog_userlist_init(void);

/*
* ˽�����ݹ���ɾ��
*/
void app_prog_userlist_del(void);

/*
* ˽�����ݹ���ɾ����Ŀ
*/
void app_prog_userlist_del_program(uint32_t* id_buf, uint32_t num);

/*
* ��ָ����Ŀ����Ϊ��ǰ���ڲ��žͽ�Ŀ(ϵͳ����)
*/
int32_t app_prog_save_playing_pos_in_group(uint32_t pos);

int32_t app_prog_find_by_id(uint32_t prog_id,int32_t *ppos,uint8_t *group_mode,uint8_t *stream_type,uint8_t *fav_id);


/*
* ��¼��ǰ���ڲ��Ž�Ŀ
*/
void app_prog_record_playing_pos(uint32_t pos_in_group);

/*
* ���½�Ŀ����
*/
void app_prog_update_num_in_group(void);

/*
* ��ȡ��Ŀ����(��ģʽ�����͵ȱ仯����app_update_num_in_group)
*/
uint32_t app_prog_get_num_in_group(void);

/*
* ��ȡ��ǰ���Ž�Ŀ����
*/
int32_t app_prog_get_playing_pos_in_group(uint32_t *ppos);

void app_prog_set_view_info_enable(void);


/*
* ��ȡ��ǰ��Ŀ����TV/RADIO
*/
uint8_t app_prog_get_stream_type(void);

/*
* �л��group_mode��stream_type��fav_id���Ͷ�ȡ��Ŀ����,�ӿڷ���֮ǰ�ָ��顢���Ͳ���
* ����˵�ǰ���ã�������ʾ"�޵��ӽ�Ŀ��"
* group_modeΪGROUP_MODE_FAV��fav_id������Ч
*/
uint32_t app_prog_check_group_num(uint8_t group_mode,uint8_t stream_type,uint8_t fav_id);


uint8_t app_prog_get_group_mode(void);
/*
* ���л���Ŀ���� ��
* ���ı䵱ǰgroup_mode��ϲ������
*/
uint32_t app_prog_change_stream_type(uint8_t stream_type);

/*
* �л���Ŀ���顢��Ŀ���͡�ϲ�������
* group_modeΪGROUP_MODE_FAV��fav_id������Ч
*/
uint32_t app_prog_change_group(uint8_t group_mode,uint8_t stream_type,uint8_t fav_id);

/*
* ��ȡÿ��ÿ�����������ӿ�
*/
uint32_t app_prog_get_cur_prog_audio_track();

/*
* ÿ����Ŀ�������������ӿ�
*/
uint32_t app_prog_save_cur_prog_audio_track(uint32_t audiotrack);

/*
* ��ȡÿ����Ŀ���������ӿ�
*/
uint32_t app_prog_get_cur_prog_audio_volumn();

/*
* ÿ����Ŀ�������������ӿ�
*/
uint32_t app_prog_save_cur_prog_audio_volumn(uint32_t audiovolumn);
/*
* �ָ���������
*/
void app_prog_delete_all_prog(void);

void app_prog_set_default(void);


uint32_t app_prog_edit_init_attr(void);
App_proedit_arr* app_prog_edit_get_attr(uint32_t sel);
uint32_t app_prog_edit_rename_attr(char * widget_listview,char* prog_name);
uint32_t app_prog_edit_set_attr(char * widget_listview,uint32_t type);
uint32_t app_prog_edit_move_attr(char * widget_listview,int32_t direction);
uint32_t app_prog_edit_get_attr_change_flag();
void app_prog_eidt_save_attr(char * widget_listview);
int app_prog_edit_play_skip_all(int32_t ppos, uint8_t stream_type);
uint32_t app_prog_save_cur_prog_audio_switch(uint16_t audio_pid,GxBusPmDataProgAudioType audio_type); 

#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_PROG__H__*/

