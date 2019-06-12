#ifndef __GX_EPG_H__
#define __GX_EPG_H__

#include <stdint.h>
#include <time.h>
#include "module/epg/gxepg_manage.h"

#define EPG_TXT_UTF8 (0x5a5a)
#define EPG_TXT_ORIGINAL (0)
#define EPG_TXT_PRIVATE (1)

///<�Ƿ񱣳�ȫ�ٹ��ˣ�Ĭ��Ϊdefault
//
//������
//
//GxBus_ConfigSetInt(EPG_SERVICE_FILTER_MODE,EPG_MANAGER_FILTER_MODE_MAX);


#define EPG_SERVICE_FILTER_MODE	"epg_service>filter_mode"
#define EPG_SERVICE_FILTER_MODE_DEFAULT (0)//�����eit������������Ĭ�Ϲ�������������ת��
#define EPG_SERVICE_FILTER_MODE_MAX (1)//�κ�ʱ�򶼲�ת��ƥ������,�����ٶ���졣�����������epg�ܶ࣬����һ��ϵͳ����


/*��txt_formatΪEPG_TXT_PRIVATE �� ttx_privat�����ã����ص�ָ��������malloc�ģ���epg����
 * �������ͷš�*/
typedef uint8_t * (*gx_epg_ttx_private)(uint8_t *src, uint32_t len);
/**
 * ����epgʱ����Ҫ���õ���Ϣ
 */
typedef struct {
	uint16_t  ts_src;               ///< epg�������Ե�TSͨ· TS1-0 TS2-1 TS3-2
	uint16_t  dmx_id;

	uint16_t  service_count;        ///< ��Ҫͬʱ�洢epg��service����
	uint16_t  event_count;          ///< �ܹ���洢��event����

	uint16_t  event_size;           ///< �洢һ��service�µ�event���ܿռ�(bytes)���������ֺ���ϸ����
	uint16_t  epg_day;              ///< ��Ҫ�洢�����epg

	uint8_t   language[3];          ///< ��Ҫ����epg�����Ը�ʽ
	uint8_t   cur_tp_only;          ///< 1 - �����˵�ǰƵ���EPG��Ϣ   0 - ��������epg����
	uint16_t  txt_format;
	gx_epg_ttx_private  ttx_private;
} GxMsgProperty_EpgCreate;

// service count that can exsit in one time
// total event count
// event size include name & content description (bytes)
// need epg days  (exp. 7-get epg in the follow 7days)



/**
 * �洢ĳһ��epg�¼�������ݵĽṹ
 */
typedef struct {
	time_t start_time;             ///< event�Ŀ�ʼʱ��
	time_t duration;               ///< event�ĳ���ʱ��

	uint16_t event_id;             ///< event idֵ
	uint16_t reserved;             ///< ����

	uint16_t event_name_len;
	uint16_t event_detail_len;

	uint16_t reference_event_id;
	uint16_t reference_service_id;
	uint8_t *event_name;           ///< ָ��event name�洢�ռ��ָ��
	uint8_t *event_detail;         ///< ָ����ϸ�����洢�ռ��ָ��
} GxEpgInfo;

/**
 * epg�������ṩ�ģ���ȡĳ��service id��epg�����ݽṹ
 */
typedef struct {
	uint16_t ts_id;            ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;       ///< ��ǰepg������service id
	uint16_t get_event_pos;    ///< �ӵڼ���event��ʼ��ȡevent��Ϣ��ǰ����Ϊ
	//��ǰ������Ϣ��������Ϊschedule��Ϣ
	uint16_t get_event_count;  ///< ��get_event_pos��ʼ��epg_info�ռ��������ɵ�event����,�����������epg���񷵻�ʱ����
	                           ///< ���Ը����û���ʵ��ȡ�˼��� event�����û���
	//��Ϣ��ʱ���ǲ���Ҫ�����������
	uint16_t want_event_count; ///< ��Ҫһ�λ�ȡ��event����
	uint32_t epg_info_size;    ///< �����洢epg���ܿռ��С
	GxEpgInfo *epg_info;       ///< ����һ�����ϲ����Ŀռ�
} GxMsgProperty_EpgGet;

/**
 * ��ȡĳ��service�µ�epg����
 */
typedef struct {
	uint16_t ts_id;                          ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;                     ///< ��ǰepg������service id
	uint16_t real_event_count;               ///< ʵ�ʴ��ڵ�event����
	float time_zone;                         ///< ʱ��-12 ~ 0 ~ 12, ֧�ְ�ʱ����Exp.+8.5
	uint16_t event_per_day[8];               ///< �ӽ��쿪ʼ��7���ڣ�ÿ������event����Ŀ��
	//0-PF��Ϣ 1 - �����event ��Ŀ 2-�����event��Ŀ...
} GxMsgProperty_EpgNumGet;

/* parental rating */
typedef struct {
	uint16_t ts_id;                          ///< transport stream id
	uint16_t orig_network_id;
	uint16_t service_id;                     ///< ��ǰepg������service id
	uint16_t parental_rating_num;
	GxBusEpgParentalRating *parental_rating;
} GxMsgProperty_EpgParentalInfo;

typedef GxEpgInfo GxNvodInfo;

/**
 * epg�������ṩ�ģ���ȡĳ��service id��nvod�����ݽṹ
 */
typedef struct {
	uint16_t ts_id;           ///< transport stream id
	uint16_t service_id;      ///< ��ǰepg������service id

	uint16_t orig_network_id;
	uint16_t get_nvod_count;

	uint32_t nvod_info_size;  ///< �����洢nvod���ܿռ��С

	GxNvodInfo *nvod_info;    ///< ����һ�����ϲ����Ŀռ�
} GxMsgProperty_EpgNvodGet;

typedef enum {
	STOP_FILTER = 0,
	START_FILTER ,
	MATCH_SERV_ID_FILTER,
	MATCH_FULL_FILTER,
	UNMATCH_FILTER
} filterStatus;

typedef struct {
	uint32_t tid;
	filterStatus status;
} GxEpgFilterInfo;

/**
 * epg�������ṩ�ģ���ȡepg��ǰfilter��״̬
 */
typedef struct {
	uint32_t num;                   ///< ��Ҫ��ȡ��filter����
	uint16_t real_num;              ///< ʵ�ʻ�ȡ��filter����

	GxEpgFilterInfo *filter_status; ///< ����һ�����ϲ����Ŀռ�
} GxMsgProperty_EpgFilterInfo;

typedef struct {
	uint32_t tid;
	uint32_t service_id;
	uint32_t version;

	filterStatus status;
} GxEpgFilterModify;

/**
 * epg�������ṩ�ģ��޸�epg��ǰfilter��״̬
 */
typedef struct {
	uint32_t num;              ///< ��Ҫ�޸ĵ�filter����
	GxEpgFilterModify *status; ///< ����һ�����ϲ����Ŀռ�
} GxMsgProperty_EpgFilterModify;

#endif

