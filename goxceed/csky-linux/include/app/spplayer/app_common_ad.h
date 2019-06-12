#ifndef __APP_AD_H__
#define __APP_AD_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "gxtype.h"
#include "gxavdev.h"
#include "gui_timer.h"

#define SCROLL_STEP (2)
#define SCROLL_DURATION (20)

typedef enum
{
	DVB_AD_TYPE_NONE=0,		
	DVB_AD_TYPE_BY,                   
	/*��չ������CA���Ͷ���*/

	DVB_AD_TYPE_MAX
}dvb_ad_type_t;


typedef struct
{
	char* file_flash_path; /*flashԭʼ����ļ����ƣ�����·��*/
	char* file_ddram_path; /*���Ź���ļ���Ҫ�������ڴ��ļ����ƣ�����·��*/
	GxAvRect rectsrc; 
	GxAvRect rectdest;	
	uint32_t play_mode; /*����ģʽ0: ָ��x,yλ����ʾ 1: �Զ�������ʾ 2: ad picture play with video*/
	uint32_t slice_num; /*gif slice current viewing num*/
	uint32_t slice_count; /*gif slice total num*/
	uint32_t scroll_len; /*have scroll width len*/
	uint32_t times_num; /*have show or scroll times count */
	uint32_t times_count; /*should show or scroll total times */
	uint32_t type; /* 0 - normal pic , 1 -- gif , 2 -- scroll*/
	event_list* ad_timer;
}ad_play_para;

int advertisement_play_init(void);
int advertisement_clear_frame(GxAvRect rect);
int advertisement_play(ad_play_para* playpara, unsigned short position,unsigned short pos2, bool bShow);
int advertisement_scroll_play(ad_play_para* playpara, unsigned short position,unsigned short pos2, bool bShow);
int advertisement_scrolling_by_step(ad_play_para* playPara,uint16_t start_y,uint16_t width,uint16_t height);
void advertisement_spp_layer_close(void);
int advertisement_zoom(int x,int y,int w,int h);
int advertisement_hide(void);

#ifdef __cplusplus
}
#endif
#endif /*__APP_AD_H__*/




