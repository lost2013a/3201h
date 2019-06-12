/**
 *
 * @file        app_common_play.h
 * @brief
 * @version     1.1.0
 * @date        10/19/2012 09:40:49 AM
 * @author      zhouhuaming (zhouhm), zhuohm@nationalchip.com
 *
 */
#ifndef __APP_COMMON_PLAY__H__
#define __APP_COMMON_PLAY__H__
#ifdef __cplusplus
extern "C" {
#endif
#include <gxtype.h>

#include "gxbus.h"
#include "gui_event.h"
#include "gxavdev.h"
#include "service/gxplayer.h"
#include "service/gxsi.h"
#include "app_common_flash.h"
#include "app_common_ad.h"
#include "gxmsg.h"
#include "gxapp_sys_config.h"
#include "gxextra.h"
#include "app_common_prog.h"



#define MAX_MSG_NUM 1000
#define PLAYER0 "player0"
#define PLAYER2 "player2"
#define PLAYER3 "player3"

typedef struct
{
	GxMessage *msg;
	void *param;
}app_msg;


typedef struct player
{
	const char *    player;
	uint8_t    param;
	uint32_t   num;
}player_t;

typedef struct
{
	uint32_t num; /*��ĿƵ����*/
}play_para;

typedef struct
{
	uint8_t startupProgFlag; /*�����Ƿ񲥷�ָ����Ŀ
	                                        startupProgFlag ΪFALSE�����Ŷϵ�����Ŀ*/
	uint8_t  stream_type; /*��������ָ����Ŀ����*/
	uint16_t startupProgNum; /* �������Ź̶���Ŀ��*/
}startup_play_para;

typedef enum MsgPop
{
	MSG_POP_NONE = 0,
	MSG_POP_INVALID_PROG,
	MSG_POP_NO_FAV_PROG,
	MSG_POP_PASSWORD_ERR,
	MSG_POP_NO_PROG,
	MSG_POP_SIGNAL_BAD,
	MSG_POP_PROG_LOCK,
	MSG_POP_PROG_SKIP,
	MSG_POP_PROG_SCRAMBLE,//���Ž�Ŀ
	
#ifdef DVB_CA_TYPE_DIVITONE_FLAG
	MSG_POP_NO_CARD,
	MSG_POP_INVALID_CARD,
#endif
#ifdef DVB_CA_TYPE_DS_CAS50_FLAG
	MSG_POP_PROG_NEED_PAY,
#endif
	MSG_POP_COMMON_END   /*�˶���δ�õ�����־��ͨ��Ϣ������*/
}MsgPop_e;

typedef enum
{
    PLAY_KEY_DUMMY,
    PLAY_KEY_LOCK,
    PLAY_KEY_UNLOCK
}AppPlayKey;



#define MESSAGE_MAX_COUNT (64)



typedef struct play_scramble_para
{
	u_int16_t program_num;
	bool program_type ;
	uint8_t  scramble_type ;
	u_int16_t p_video_pid ;//����
	u_int16_t p_audio_pid ;//����
	u_int16_t p_ecm_pid ;//ecm ���������
	u_int16_t p_ecm_pid_video ;
	u_int16_t p_ecm_pid_audio ;
	u_int16_t p_emm_pid ;//��ǰ��Ŀ����Ƶ��emm-pid
	#if (defined DVB_CA_TYPE_ABV_CAS53_FLAG || defined DVB_CA_TYPE_ABV_CAS38_FLAG)
	u_int16_t pmt_pid;
	#endif
} play_scramble_para_t;


int32_t app_send_msg(uint32_t msg_type,void *param);
app_msg * app_get_msg(uint32_t msg_id);

int32_t app_play_startup_prog(startup_play_para playpara);
int32_t  app_play_switch_tv_radio(void);

uint32_t app_play_recall_prog(void);
uint32_t app_play_by_direction(int32_t direction);
 void app_play_set_cur_prog_track(void);
 void app_play_set_cur_prog_volumn(void);
void app_play_reset_play_timer(uint32_t duration);
void app_play_remove_play_tmer(void);
/*�˳���������Ƶ���Ž��棬����Ƿ���ڵȴ���ʱ���ŵĶ�ʱ��
   ����ڣ��˳���������Ƶ���Ž���ǰ���ȴ�����*/
void app_play_check_play_timer(void);


void app_free_msg(uint32_t msg_type,uint32_t msg_id);



/*
* ���½ӿ�ͬʱ�ṩmenu����
*/
typedef void (*prompt_show_msg_callback)(void);
void app_play_register_show_prompt_msg_callback(prompt_show_msg_callback promptshowmsgcallback);
void app_play_register_password_widget_window(const char* password_widget);
/*
* ��ȡ��ǰ����Ƶ�Ƿ񲥷�״̬
*/
uint8_t app_play_get_play_status(void);

/*
* ��ȡ��ǰ����Ƶ�Ƿ�ɹ�����״̬
*/
uint8_t app_play_get_running_status(void);

/*
* ������ʾ��Ϣˢ�±�־���˵��仯��Ҫ������ʾ
*/
void app_play_set_prompt_reflush_flag(uint32_t flag);

/*
* ��ȡ��ʾ��Ϣˢ�±�־���˵��仯��Ҫ������ʾ
*/
uint32_t app_play_get_prompt_reflush_flag(void);


/*
* ���õ�ǰ����Ƶ�Ƿ�ɹ�����״̬
*/
uint8_t app_play_set_running_status(uint8_t status);


/*
* ֹͣ��/��Ƶ���ţ���Ϊ��Ƶ�б����л���Ŀ��������ͼƬ
*/
void app_play_stop_audio(void);

/*
* ֹͣ����Ƶ���ţ�ͬʱ�ر�PLAYER3��PLAYER0
* �����жϵ�ǰ��Ŀ����
*/
void app_play_stop(void);

/*
* ��������Ƶ
*/
void app_play_video_audio(int32_t pos);
int32_t app_play_playingpos_in_group(void);

/*
* ��ʾ��Ƶ����ͼƬ
*/
void app_play_show_logo_for_tv(void);
void app_play_show_logo(void);
uint32_t app_play_i_frame_logo(int32_t VideoResolution,char* path);
/*
* �رտ�������
*/
uint32_t app_play_close_av_logo(void);

/*
* �ر���Ƶ��
*/
void app_play_hide_video_layer(void);
/*
* ����Ƶ��
*/
void app_play_show_video_layer(void);

/*
* ������Ƶ���Ų�����С
*/
void app_play_set_zoom_para(unsigned int x,unsigned int y,unsigned int w,unsigned int h);

/*
* ��Ƶ��������
*/
void app_play_video_window_zoom(unsigned int x,unsigned int y,unsigned int w,unsigned int h);

/*
* ��Ƶ���ڷŴ�ȫ��
*/
void app_play_video_window_full(void);

/*
* ���Ź��ͼƬ�ӿ�
* ֧�ְ�X��Y����\���в���
*/
status_t app_play_ad_flash_file(ad_play_para *playpara);
status_t app_play_ad_ddram_file(ad_play_para *playpara);
/*
* �رչ��ͼƬ�ӿ�
*/
status_t app_play_stop_ad(ad_play_para playpara);

/*
* ������������ʾ
*/
void app_play_switch_prog_clear_msg(void);

/*
* �������CA�����ʾ
*/
void app_play_clear_ca_msg(void);
/*
* ���ò�����Ϣ����
*/
void app_play_set_msg_pop_type_flag(MsgPop_e type);

/*
* ���ò�����Ϣ����
*/
void app_play_set_msg_pop_type(MsgPop_e type);

/*
* ���õ�ǰ��Ϣ����
*/
void app_play_set_msg_pop_type_record_pos(MsgPop_e type);
/*
* ���ָ�����͵���Ϣ��ʾ
*/
void app_play_clear_msg_pop_type_flag(MsgPop_e type);


/*
* ���ָ�����͵���Ϣ��ʾ
*/
void app_play_clear_msg_pop_type(MsgPop_e type);

/*
* ��ȡָ�����͵���Ϣ��ʾ״̬
*/
uint32_t app_play_get_msg_pop_type_state(MsgPop_e type);

/*
* ������Ƶ��߱�ģʽ
*/
int32_t app_play_set_video_aspect(VideoAspect nAspect);

/*
* ���ÿ�߱�4X3\16X9
*/
int32_t app_play_set_video_display_screen(	Video_Display_Screen_t n4To3_16To9);

int32_t app_play_set_channel_switch(int32_t channel_switch);

/*
* ��������
*/
void app_play_set_audio_track(int audio_track);

/*
* ��������
*/
void app_play_set_volumn(int32_t Volume);

/*
* �����Բ�������Ӧ�ֱ��ʱ仯������flash�ֱ��ʱ���
*/
int32_t app_play_update_flash_video_resolution(VideoOutputMode video_resution);
/*
* ����rca1
*/

int32_t app_play_set_rca1_mode(int32_t VideoResolution);

/*
* ����hdmi��Ƶ�ֱ���
*/
int32_t app_play_set_hdmi_mode(int32_t VideoResolution);
uint8_t app_play_get_mute_flag(void);
/*
* ���á�ȡ������
*/
void app_play_set_mute(int32_t mute);

/*
* AC3 BYPASS��Ƶ�����������
*/
void app_play_set_audio_ac3_bypass_onoff(int32_t onoff);

/*
* ������Ӣ��
*/
void app_play_set_osd_language(char* language);

/*
* ����͸����
*/
void app_play_set_osd_trasn_level(uint32_t nTransLeve);
void app_play_set_videoColor_level(VideoColor color);

/*
* register dolby support
*/
void app_play_register_dolby(void);
uint8_t app_play_get_playing_para(play_scramble_para_t* playPara);
uint8_t app_play_set_playing_para(play_scramble_para_t* playPara);

/*
*  ����ǰ���þ�����·gpio�����������������
*/
uint8_t app_play_set_gpio_mute(void);

/*
*  ������ʼ�����þ�����·gpio�������
*/
uint8_t app_play_set_gpio_unmute(void);

int app_play_get_signal_status(void);
void app_play_set_signal_status(int ri_SignalStatus);

int app_play_get_popmsg_status();
void app_play_set_popmsg_status(int ri_Popmsg_Type);

/*
* ��Ƶ���ö�
*/
void app_play_set_zoom_video_top(void);

#if (DVB_THEME_TYPE == DVB_THEME_HD)

/*
* PAL, PAL-N, PAL-M, NTSC-Mȫ��֧��
*/ 
int app_av_save_rca_standard(VideoOutputMode av_OutputMode); 
int app_av_set_init(void); 


#endif 
#if (DVB_CASCAM_FLAG)
void app_play_cascam_change_program(GxBusPmDataProg prog_data);
#endif
//int app_common_write_esa_buffer(void *fd, char *data, unsigned int len,GxMediaSourceType type);
//int app_common_play_esa_init(AudioCodecType type , int sample_rate,int sample_bits);
int app_common_esa_pause(void);
int app_common_esa_resume(void);
int app_common_esa_stop(void);
int app_common_esa_start(void);
int app_common_esa_close(void);


#ifdef __cplusplus
}
#endif



#endif /*__APP_COMMON_PLAY__H__*/

