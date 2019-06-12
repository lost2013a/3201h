/** @defgroup pm_module PM Module*/

/*@{*/
#ifndef __GXPROGRAM_MANAGE_MINIDB_H__
#define __GXPROGRAM_MANAGE_MINIDB_H__

#include "gxtype.h"
#include "gxcore.h"
#ifdef LINUX_OS
#include <linux/dvb/frontend.h>
#else
#include "frontend/frontend.h"
#endif

__BEGIN_DECLS

/**
 * 说明：不同的tp集合可能属于不同的信道 比如卫星的双
 * tuner方案 而多tuner应该是以tp集合为单位管理方便
 * 所以这个结构用于表明tp结合属于哪一个tuner,
 * 这个参数当锁频的时候用于确认操作哪个tuner,1-tuner1 2-tuner2.....
 */
typedef uint32_t GxBusPmDataSatTuner;

/*以下为变量的形式,在初始化数据库的时候传入,
  问题在于如何控制传入的值的合法性???如果用户随便乱传 会出现问题*/
extern uint32_t MAX_SAT_COUNT;
extern uint32_t MAX_TP_COUNT;
extern uint32_t MAX_PROG_COUNT;

//#define MAX_SAT_COUNT   100   ///< 方案最多能容纳的sat数量
//#define MAX_TP_COUNT    4000  ///< 方案最多能容纳的tp数量
//#define MAX_PROG_COUNT  5000  ///< 方案最多能容纳的prog数量
#define MAX_PROG_PER_TP   (300) ///< 方案每个tp最多能容纳的prog数量
/****************************************************************/
#define MAX_SAT_NAME       (16)
#define MAX_PROG_NAME      (32)
#define MAX_FAV_GROUP_NAME (16)
#define MAX_CAS_NAME       (16)
#define MAX_CA_SYSTEM      (16)
#define CAS_ID_FREE        (0x1fff)
#define CAS_ID_UNKNOW      (0x1ffe)
#define MAX_IF_INDEX_NUM       (8)


//#define GXCORE_SUCCESS           (0)
//#define GXCORE_ERROR        (1)

#define GX_PM_DBASE_FULL (0x7fffffff)

#define GX_PM_MAX_PROG_URL_SIZE (256)

#define MAX_CMP_NAME (MAX_PROG_NAME)

/**
 *数据库路经
 */
#define GX_PM_FILE_PATH1                "/home"
#define GX_PM_FILE_PATH2                "/home/gx"
#define GX_PM_FILE_PATH3                "/home/gx/db"


#define GX_PM_SAT_FILE_PATH             "/home/gx/sat.db"
#define GX_PM_TP_FILE_PATH              "/home/gx/tp.db"
#define GX_PM_PROG_FILE_PATH            "/home/gx/prog.db"
#define GX_PM_FAV_FILE_PATH             "/home/gx/fav.db"
#define GX_PM_STREAM_FILE_PATH          "/home/gx/stream.db"
#define GX_PM_VERIFY_FILE_PATH          "/home/gx/verify.db"
#define GX_PM_TV_USER_LIST_FILE_PATH    "/home/gx/tv_user_list.db"
#define GX_PM_RADIO_USER_LIST_FILE_PATH "/home/gx/radio_user_list.db"
#define GX_PM_PROG_EXT_FILE_PATH        "/home/gx/prog_ext.db"

/**
 * 观看模式保存文件路径
 */
#define GX_SYS_INFO_FILE_PATH1          "/home"
#define GX_SYS_INFO_FILE_PATH2          "/home/gx"
#define GX_SYS_INFO_FILE_PATH3          "/home/gx/db"
#define GX_SYS_INFO_FILE_NAME           "/home/gx/view_info_db"

/**
 * 默认数据库文件的路径
 */
#define GX_PM_DEFAULT_PATH              "/default_data.db"
#define GX_PM_DEFAULT_SAT_FILE_PATH     "/sat.db"
#define GX_PM_DEFAULT_TP_FILE_PATH      "/tp.db"
#define GX_PM_DEFAULT_PROG_FILE_PATH    "/prog.db"


/* Exported Types --------------------------------------------------------- */

/**
 * 说明：数据库数据的类型
 * 如需扩展要在这里增加新的类型
 */
typedef enum {
	GXBUS_PM_DATA_SAT = 0, // 卫星信息
	GXBUS_PM_DATA_TP,      // Tp信息
	GXBUS_PM_DATA_PROG,    // 节目信息
} GxBusPmDataQueryType;

/**
 * 说明：要考虑到各种已知方案的共用 所以配合c和t抽象出了
 * 卫星的概念
 */
typedef enum {
	GXBUS_PM_SAT_S = 0,  // s的tp集合，这种类型的tp集合就是一颗卫星
	GXBUS_PM_SAT_C,      // c的tp集合，
	GXBUS_PM_SAT_T,      // t的tp集合
	GXBUS_PM_SAT_DTMB,   // dtmb的tp集合
	GXBUS_PM_SAT_DVBT2,  // dvbt2的tp集合
	GXBUS_PM_SAT_ATSC_C, // atsc_c的tp集合
	GXBUS_PM_SAT_ATSC_T, // atsc_t的tp集合
} GxBusPmDataSatType;

/**
 *卫星经度的描述枚举
 */
typedef enum {
	GXBUS_PM_SAT_LONGITUDE_DIRECT_EAST = 0, // 东经
	GXBUS_PM_SAT_LONGITUDE_DIRECT_WEST,     // 西经
} GxBusPmDataSatLongitudeDirect;

/**
 *卫星lnb power
 */
typedef enum {
	GXBUS_PM_SAT_LNB_POWER_OFF = 0, // 不供电
	GXBUS_PM_SAT_LNB_POWER_ON,      // 供电
	GXBUS_PM_SAT_LNB_POWER_13V,     // 供13v电
	GXBUS_PM_SAT_LNB_POWER_18V,     // 供18v电
} GxBusPmSatLnbPower;

/**
 * LNB 类型
 */
typedef enum {
	GXBUS_PM_SAT_LNB_UNIVERSAL = 0,
	GXBUS_PM_SAT_LNB_OCS,            // 5150/5700
	GXBUS_PM_SAT_LNB_USER,           // "5150","5700","5750","9750","10000","10600","10700","10750","11250","11300"
} GxBusPmSatLnbType;

/**
 *卫星22k开关
 */
typedef enum {
	GXBUS_PM_SAT_22K_OFF = 0, // 22k关
	GXBUS_PM_SAT_22K_ON,      // 22k开
	GXBUS_PM_SAT_22K_AUTO,    // 22k自动
} GxBusPmSat22kSwitch;

/**
 * 卫星12v开关
 */
typedef enum {
	GXBUS_PM_SAT_12V_OFF = 0, // 12v关
	GXBUS_PM_SAT_12V_ON,      // 12v开
} GxBusPmSat12vSwitch;

/**
 * 卫星diseq版本
 */
typedef enum {
	GXBUS_PM_SAT_DISEQC_OFF   = 1,   // 不使用diseqc
	GXBUS_PM_SAT_DISEQC_1_0   = 2,   // diseqc1.0
	GXBUS_PM_SAT_DISEQC_1_1   = 4,   // diseqc1.1
	GXBUS_PM_SAT_DISEQC_1_2   = 8,   // diseqc1.2
	GXBUS_PM_SAT_DISEQC_USALS = 16,  // diseqc USALS
	GXBUS_PM_SAT_DISEQC_2_0   = 32,  // diseqc2.0
} GxBusPmSatDiseqcVersion;

/**
 * 卫星diseq1.0位置
 */
typedef enum {
	GXBUS_PM_SAT_DISEQC1_0_OFF = 0, // 不使用diseqc1.0
	GXBUS_PM_SAT_DISEQC1_0_1,       // diseqc1.0 位置1
	GXBUS_PM_SAT_DISEQC1_0_2,       // diseqc1.0 位置2
	GXBUS_PM_SAT_DISEQC1_0_3,       // diseqc1.0 位置3
	GXBUS_PM_SAT_DISEQC1_0_4,       // diseqc1.0 位置4
	GXBUS_PM_SAT_DISEQC1_0_A,       // diseqc1.0 miniA
	GXBUS_PM_SAT_DISEQC1_0_B,       // diseqc1.0 miniB
} GxBusPmSatDiseqc10;

/**
 * 说明：dtmb芯片1501能够工作在两种模式dtmb和dvb_c
 */
typedef enum {
	GXBUS_PM_SAT_1501_DTMB = 0, // 1501芯片的dtmb工作方式
	GXBUS_PM_SAT_1501_DVB_C,    // 1501芯片的dvb_c工作方式
} GxBusPmDataSat1501WorkType;

/**
*s方案使用的卫星参数
*/
typedef struct {
	/*4*4B */
	uint16_t centre_fre[MAX_IF_INDEX_NUM];  
	
	/*4B */
	uint16_t             	    if_channel;        
	uint8_t                       lnb_fre_index; 
	uint8_t                       sat_pos; 
} GxBusPmSatUnicable_s;

typedef struct {
	/*4B */
	uint16_t                      lnb1;                 // LNB Frequence.低本振
	uint16_t                      lnb2;                 // LNB Frequence. 高本振.如果为单本振,这个值为0

	/*4B */
	uint8_t                       diseqc11;             // deseqc1.1 的位置选择 0-OFF 1 ... 16
	uint8_t                       diseqc12_pos;         // 记录卫星在deseqc设备中的存储位置. 0 代表默认位置. */

	GxBusPmSatDiseqcVersion       diseqc_version : 8;   // diseqc的版本 *Off,DiSEqC1.0, DiSEqC1.1, DiSEqC1.2, USALS, DiSEqC2.0
	GxBusPmSatDiseqc10            diseqc10 : 8;         // diseqc1.0的位置/*OFF , 1, 2, 3, 4, mini A, mini B */

	/*4B */
	GxBusPmSatLnbPower            lnb_power : 4;        // 选择供电的类型
	GxBusPmSat22kSwitch           switch_22K : 2;       // 22K 开关. */
	GxBusPmSat12vSwitch           switch_12V : 1;       // 12v开关
	GxBusPmDataSatLongitudeDirect longitude_direct : 1; // 卫星的经度选择 0-东经 1-西经 */
	uint8_t                       reserved;

	uint16_t                      longitude;            // 具体的经度度数

	/*4*4B */
	uint8_t sat_name[MAX_SAT_NAME];                     // 卫星的名称

	GxBusPmSatUnicable_s		unicable_para;

} GxBusPmSat_s;

/**
 * c方案中卫星的参数,
 * 在这个结构体中的参数应该是
 * 对于所有属于这个tp集合的tp都起作用的参数
 */
typedef struct {
	uint32_t reserved;
} GxBusPmSat_c;

/**
 * t方案中卫星的参数,
 * 在这个结构体中的参数应该是
 * 对于所有属于这个tp集合的tp都起作用的参数
 */
typedef struct {
	uint32_t reserved;
} GxBusPmSat_t;

/**
 * DTMB方案中卫星的参数,
 * 在这个结构体中的参数应该是
 * 对于所有属于这个tp集合的tp都起作用的参数
 */
typedef struct {
	GxBusPmDataSat1501WorkType work_mode;
} GxBusPmSat_dtmb;

/**
 * DVBT2方案中卫星的参数,
 * 在这个结构体中的参数应该是
 * 对于所有属于这个tp集合的tp都起作用的参数
 */
typedef struct {
	uint32_t reserved;
} GxBusPmSat_dvbt2;

/**
 * ATSC-C方案中卫星的参数,
 * 在这个结构体中的参数应该是
 * 对于所有属于这个tp集合的tp都起作用的参数
 */
typedef struct {
	uint32_t reserved;//ATSC wait
} GxBusPmSat_atsc_c;

/**
 * ATSC-T方案中卫星的参数,
 * 在这个结构体中的参数应该是
 * 对于所有属于这个tp集合的tp都起作用的参数
 */
typedef struct {
	uint32_t reserved;//ATSC wait
} GxBusPmSat_atsc_t;

/**
 * 该结构是每个tp集合的属性结构体，
 * 对于卫星方案来说这就是一个卫星node，
 * 在这个结构体中的参数应该是对于所有属于这个tp集合的tp都起作用的参数，
 * 比如卫星中的本振,用户得到的卫星参数就是以下结构体
 */
typedef struct {
	uint32_t id;                    // 该tp集合的id
	uint16_t tsid;
	uint16_t cur_tv;
	uint16_t cur_radio;
	GxBusPmDataSatType type;        // tp集合的类型，指明该集合属于s还是c，或者t
	GxBusPmDataSatTuner tuner;      // 该tp集合属于哪个tuner
	union {
		GxBusPmSat_s sat_s;
		GxBusPmSat_c sat_c;
		GxBusPmSat_t sat_t;
		GxBusPmSat_dtmb sat_dtmb;
		GxBusPmSat_dvbt2 sat_dvbt2;
		GxBusPmSat_atsc_c sat_atsc_c;
		GxBusPmSat_atsc_t sat_atsc_t;
	};
} GxBusPmDataSat;

/**
 * 卫星方案tp 极化方向
 */
typedef enum {
	GXBUS_PM_TP_POLAR_H = 0, // 极化方向h
	GXBUS_PM_TP_POLAR_V,     // 极化方向v
	GXBUS_PM_TP_POLAR_AUTO,  // 极化方向自动
}GxBusPmTpPolar;

/**
 * S 方案中tp的参数
 */
typedef struct {
	uint32_t       symbol_rate;   // 符号率
	GxBusPmTpPolar polar;         // 极化方向
} GxBusPmTp_s;

/**
 * C 方案中tp的参数
 */
typedef struct {
	uint32_t        symbol_rate; // 符号率
	fe_modulation_t modulation;  // 调制方式 参看fe_modulation_t
} GxBusPmTp_c;

/**
 * T 方案中tp的参数
 */
typedef struct {
	fe_bandwidth_t bandwidth;
} GxBusPmTp_t;

/**
 * DTMB 方案中tp的参数
 */
typedef struct {
	uint32_t        symbol_rate; // 符号率,当1501处于dvb_C工作模式时起作用
	fe_modulation_t modulation;  // 调制方式 当1501处于dvb_C工作模式时起作用
	fe_bandwidth_t bandwidth;
} GxBusPmTp_dtmb;

/**
 * DVBT2 方案中TP的参数
 */
typedef struct {
	fe_bandwidth_t bandwidth;
} GxBusPmTp_dvbt2;

/**
 * ATSC_C 方案中TP的参数
 */
typedef struct {
	uint32_t reserved;//等待具体demod参数 ATSC wait
} GxBusPmTp_atsc_c;

/**
 * ATSC_T 方案中TP的参数
 */
typedef struct {
	uint32_t reserved;//等待具体DEMOD参数 ATSC WAIT
} GxBusPmTp_atsc_t;

/**
 * 该结构是每个tp的属性结构体,需要通过sat_id
 * 确认该tp属于的tp集合的属性，而后选择相应的公用体内容
 * 用户得到的tp参数就是以下结构体
 */
typedef struct {
	uint32_t id;        // 该tp的id
	uint32_t sat_id;    // 该tp所属的tp集合的id，如果是卫星方案这个就是卫星的id
	uint32_t frequency; // 频点的频率单位 MHz
	union {
		GxBusPmTp_s tp_s;
		GxBusPmTp_c tp_c;
		GxBusPmTp_t tp_t;
		GxBusPmTp_dtmb tp_dtmb;
		GxBusPmTp_dvbt2 tp_dvbt2;
		GxBusPmTp_atsc_c tp_atsc_c;
		GxBusPmTp_atsc_t tp_atsc_t;
	};
} GxBusPmDataTP;

/**
 * PROG 的声道模式
 */
typedef enum {
	GXBUS_PM_PROG_AUDIO_MODE_LEFT = 0, // 左声道
	GXBUS_PM_PROG_AUDIO_MODE_RIGHT,    // 右声道
	GXBUS_PM_PROG_AUDIO_MODE_STEREO,   // 立体声
	GXBUS_PM_PROG_AUDIO_MODE_MONO,     // MONO
} GxBusPmDataProgAduioTrack;

/**
 * prog的bool型参数,用于skip lock 加密,subt标志 cc标志 ttx标志
 * 等bool型的参数
 */
typedef enum {
	GXBUS_PM_PROG_BOOL_ENABLE = 1,  // 使能
	GXBUS_PM_PROG_BOOL_DISABLE = 0, // 不使能
} GxBusPmDataProgSwitch;

/**
 * prog 的类型 指明该prog是 tv还是radio
 */
typedef enum {
	GXBUS_PM_PROG_TV = 0,     // tv节目
	GXBUS_PM_PROG_RADIO,      // radio节目
	GXBUS_PM_PROG_HD_SERVICE, // 高清节目
	GXBUS_PM_PROG_DATA,       // 数据广播
	GXBUS_PM_PROG_NVOD,       // nvod
	GXBUS_PM_PROG_USER1,      // 保留类型
	GXBUS_PM_PROG_USER2,      // 保留类型
	GXBUS_PM_PROG_USER3,      // 保留类型
	GXBUS_PM_PROG_USER4,      // 保留类型
	GXBUS_PM_PROG_USER5,      // 保留类型
	GXBUS_PM_PROG_USER6,      // 保留类型
	GXBUS_PM_PROG_USER7,      // 保留类型
	GXBUS_PM_PROG_USER8,      // 保留类型
	GXBUS_PM_PROG_USER9,      // 保留类型
	GXBUS_PM_PROG_USER10,     // 保留类型
	GXBUS_PM_PROG_ALL,        // 所有节目
} GxBusPmDataProgType;

/**
 *指明节目时否已经存在
 */
typedef enum {
	GXBUS_PM_PROG_EXIST = 0, // 节目不存在是新搜索到的节目
	GXBUS_PM_PROG_NOT_EXIST, //节目已经存在
} GxBusPmDataProgExistFlag;

/**
 * prog的视频类型 指明该prog的视频是mepg的还是avs的
 */
typedef enum {
	GXBUS_PM_PROG_MPEG = 0, // mepg2编码
	GXBUS_PM_PROG_AVS,      // AVS编码
	GXBUS_PM_PROG_H264,     // h.264编码
	GXBUS_PM_PROG_H265,     // h.265编码
	GXBUS_PM_PROG_MPEG4,    // mpeg4编码
} GxBusPmDataProgVideoType;

/**
 * audio的类型 指明该audio是pcm的还是aac的或者是ac3的
 */
typedef enum {
	GXBUS_PM_AUDIO_MPEG1 = 0,    // mpeg-1
	GXBUS_PM_AUDIO_MPEG2,        // mpeg-2
	GXBUS_PM_AUDIO_AAC_LATM,     // aac??频
	GXBUS_PM_AUDIO_AC3,          // ac3??频
	GXBUS_PM_AUDIO_AAC_ADTS,     // aac??频
	GXBUS_PM_AUDIO_EAC3,         // eac3
	GXBUS_PM_AUDIO_LPCM,
	GXBUS_PM_AUDIO_DTS,
	GXBUS_PM_AUDIO_DOLBY_TRUEHD,
	GXBUS_PM_AUDIO_AC3_PLUS,
	GXBUS_PM_AUDIO_DTS_HD,
	GXBUS_PM_AUDIO_DTS_MA,
	GXBUS_PM_AUDIO_AC3_PLUS_SEC,
	GXBUS_PM_AUDIO_DTS_HD_SEC,
	GXBUS_PM_AUDIO_DRA,
} GxBusPmDataProgAudioType;

/**
 * audio的等级
 */
typedef enum {
	GXBUS_PM_PROG_AUDIO_LECEL_HIG = 0,  // 音量等级高,声音比较大
	GXBUS_PM_PROG_AUDIO_LECEL_MID,      // 音量等级中
	GXBUS_PM_PROG_AUDIO_LECEL_LOW,      // 音量等级低
} GxBusPmDataProgAudioLevel;


typedef enum {
	GXBUS_PM_PROG_SD = 0, // 标清节目
	GXBUS_PM_PROG_HD,     // 高清节目
} GxBusPmDataProgDefinition;

/**
 * 该结构是每个prog的属性结构体,
 * 用户得到的prog参数就是以下结构体
 */
typedef struct {
	/*4B */
	uint16_t id;                                 // 该节目的id
	uint16_t tp_id;                              // 该节目所属tp的id
	/*4B */
	GxBusPmDataProgType service_type:4;          // 表明该节目是tv 或者 radio
	GxBusPmDataProgAduioTrack audio_mode:4;      // 声道模式 left right 或者是stereo
	GxBusPmDataProgAudioLevel audio_level:4;     // 音频的放大等级
	GxBusPmDataProgVideoType video_type:4;       // 表明该节目是mpeg 或者 avs
	uint8_t sdt_version;
	uint8_t pat_version;

	/*4B */
	uint16_t sat_id;                             // 该tp所属的tp集合的id，如果是卫星方案这个就是卫星的id
	uint16_t tuner;                              // 该节目所属的tuner,初始值来自于sat的tuner.

	/*4B */
	uint16_t                  service_id;        // 节目的searvice id
	uint8_t                   audio_volume;      // 音量
	GxBusPmDataProgSwitch     scramble_flag : 1; // 节目加密标志位
	GxBusPmDataProgSwitch     skip_flag     : 1; // 跳过标记
	GxBusPmDataProgSwitch     lock_flag     : 1; // 加锁标志
	GxBusPmDataProgSwitch     ttx_flag      : 1; // ttx是否存在的标志
	GxBusPmDataProgSwitch     subt_flag     : 1; // subt是否存在的标志
	GxBusPmDataProgSwitch     cc_flag       : 1; // cc是否存在的标志
	GxBusPmDataProgSwitch     ac3_flag      : 1; // ac3是否存在的标志
	GxBusPmDataProgDefinition definition    : 1;

	/*4B */
	uint32_t favorite_flag;                      // 喜爱标记，代表该节目属于哪个喜爱组，
	// 每一位代表一个喜爱组 比如 第一位为1 那就标志该节目被添加进了喜爱组1
	/*4B */
	uint16_t pcr_pid;                            // 节目的pcr pid
	uint16_t pmt_pid;                            // 节目的pmt pid

	/*4B */
	uint16_t bouquet_id;                         // 节目的bouquet pid
	uint16_t video_pid;                          // 节目的video pid

	/*4B */
	uint16_t ecm_pid_v;                          // 视频的ecm pid
	uint8_t pmt_version;                         // 当前使用的pmt版本
	uint8_t audio_count;                         // 该节目的音频数量 不包括ac3

	/*4B */
	uint16_t ac3_pid;                            // ac3的pid
	//	uint16_t count;                              // 该参数表明了这个service的观看频率,用于删除epg的时候做判断
	uint16_t cur_audio_pid;                      // 当前这个节目播放的音频的id
	//	uint16_t cur_stream_id;                      // 当前这个节目播放的音频的stream_id

	/*4B*/
	uint16_t cur_audio_ecm_pid;                  // 当前音频的ecm pid
	GxBusPmDataProgAudioType cur_audio_type:8;   // 记录当前audio的type 不需要4B那么大的
	uint8_t logic_valid;//add by leixj

	/*4B*/
	uint16_t ts_id;                              // ts id
	uint16_t original_id;                        // 这个节目的原是网络id

	/*4B */
	uint32_t cas_id;                             // 节目使用的加密系统的id


	/*5*4B */
	uint8_t prog_name[MAX_PROG_NAME];            // 节目的名称节目的名称在atsc标准里面这一项就是short name
	uint32_t nvod_service_id;

	/*4B */
	uint32_t ext_size;///<该节目扩展信息的大小

	/*4B*/ //dvbt2使用的3个id
	uint8_t data_plp_id;
	uint8_t common_plp_exist;
	uint8_t common_plp_id;
	uint8_t reserved2;

	/*用于atsc标准的节目信息*/
	/*4B*/
	uint16_t major_num;
	union {
		uint16_t minor_num;
		uint16_t logicnum;
	}u3;
	/*4B*/
	union {
		uint16_t source_id;
		uint16_t locator_id;
	}u1;

	uint8_t path_select;//cvtc独有
	uint8_t out_of_band;//cvtc独有

	/*5*4B */
	union {
		uint8_t long_name[MAX_PROG_NAME];
		uint8_t service_provider_name[MAX_PROG_NAME];
	}u2;
	/*4B*/
	uint32_t pos;                                // 靠这个东西排序
} GxBusPmDataProg;

typedef enum {
	GXBUS_PM_PROG_MODIFY_SKIP = 0, // 修改节目的skip状态
	GXBUS_PM_PROG_MODIFY_LOCK,     // 修改节目的lock状态
} GxBusPmProgModifyBoolType;

/**
 * 每一个喜爱组都具备这样一个结构
 */
typedef struct {
	uint32_t id;                          // 该喜爱组在数据库中的id
	uint16_t cur_tv;
	uint16_t cur_radio;
	uint8_t fav_name[MAX_FAV_GROUP_NAME]; // 喜爱组的名称
} GxBusPmDataFavItem;

typedef struct {
	uint16_t cas_id_begin;          // 该加密系统的起始id,只要id号在cas_id_begin到cas_id_end的范围内,那么就是同一个加密系统
	uint16_t cas_id_end;            // 该加密系统的结束id,只要id号在cas_id_begin到cas_id_end的范围内,那么就是同一个加密系统
	uint8_t cas_name[MAX_CAS_NAME]; // 该加密系统的名称
} GxBusPmDataCasInfot;

/*stream的结构*/
typedef struct {
	uint32_t prog_id;                    // 该stream所属的节目的id
	GxBusPmDataProgAudioType audio_type; // 0-pcm 1-ac3 2-acc
	uint16_t audio_pid;                  // audio pid
	uint16_t ecm_pid;                    // ecm pid
	uint8_t name[4];                     // 该stream的国家代码
} GxBusPmDataStream;


typedef enum {
	GXBUS_PM_PROG_MOVE_BEFORE = 0, // 移动节目到目标id之前
	GXBUS_PM_PROG_MOVE_AFTER,      // 移动节目到目标id之后
} GxBusPmProgMoveType;

typedef enum {
	GROUP_MODE_ALL = 0,
	GROUP_MODE_SAT = 0x1,
	GROUP_MODE_FAV = 0x2,
	GROUP_MODE_USER = 0x3,
}GxBusPmViewInfoGroupMode;

typedef enum {
	TAXIS_MODE_NON = 0,
	TAXIS_MODE_CAS,
	TAXIS_MODE_LETTER,
	TAXIS_MODE_TP,
	TAXIS_MODE_TUNER,
	TAXIS_MODE_SCRAMBLE,
	TAXIS_MODE_SERVICE_ID,
	TAXIS_MODE_USER,
}GxBusPmViewInfoTaxisMode;

typedef enum {
	VIEW_INFO_ENABLE  = 0x2aa,
	VIEW_INFO_DISABLE = 0x155,
}GxBusPmViewInfoStatus;

typedef enum {
	VIEW_INFO_SKIP_CONTAIN  = 0,///<节目列表包括跳过的节目
	VIEW_INFO_SKIP_VANISH ,///<节目列表不包括跳过的节目
}GxBusPmViewInfoSkipView;

typedef enum {
	VIEW_INFO_ID = 0,
	VIEW_INFO_POS,
}GxBusPmViewInfoCurProgType;

typedef enum {
	VIEW_INFO_ORDER = 0,///<正向排序
	VIEW_INFO_REVERSE,///<逆向排序
}GxBusPmViewInfoOrder;

typedef struct
{
	uint32_t id;//节目的id，必填
	uint32_t params1;//任何整数成员都可以用在这里进行排序
	uint8_t params2[MAX_PROG_NAME];//任何字符串成员都可以用在这里排序，现阶段只有name
}GxBusPmProgSort;

/**
 * 说明：该结构知名了当前系统采用的观看模式对于常用的观看顺序应该如下理解
 * 先选择一个组 可能是选了一个sat（对于卫星方案就是选择了某颗卫星），
 * 也可能是选择了一个喜爱组。还有可能就是all，之后再选择一种排序方式。
 * 例子：当前选择了id为5的tp集合组，采用了字母排序方式 并且选择了a～z。
 * 那么参数值应该是：group_mode = 1，taxis_mode = 2, letter_pos = 0.
 * tp_aggregate_id = 5.看似复杂 但是理清楚关系候能组合出各种观看模式
 */
typedef struct {
	/*4B*/
	uint32_t  tv_prog_cur ;                     // 最后一次播放的tv节目可以记录节目的id也可以是pos,
	// 如果是当作id,那么取节目的时候需要调用GxBus_PmProgGetById,
	// 如果是当作pos使用,那么取节目的时候需要调用GxBus_PmProgGetByPos
	/*4B*/
	uint32_t  radio_prog_cur ;                  // 最后一次播放的radio节目可以记录节目的id也可以是pos
	/*4B*/
	GxBusPmViewInfoGroupMode  group_mode :8;    // 观看的组的模式 卫星组 或者喜爱组:
	//   0 - all
	//   1 - tp集合
	//   2 - 喜爱组
	//   3 - 用户自定义过滤，配合gx_pm_prog_check和gx_pm_prog_order使用

	GxBusPmViewInfoTaxisMode  taxis_mode:8;     // 选择的排序方式
	//   0 - 无排序
	//   1 - cas排序
	//   2 - 字母排序
	//   3 - tp排序
	//   4 - tuner排序
	//   5 - scramble
	//   6 - service_id ………

	GxBusPmDataProgType  stream_type : 4;       // tv 或者是raido 模式 以后需要其他模式可以扩张这个成员
	GxBusPmViewInfoCurProgType type :1;         // 表明tv_prog_cur和radio_prog_cur是代表pos还是id
	GxBusPmViewInfoSkipView skip_view_switch:1; // 是否需要显示跳过的节目:
	//   VIEW_INFO_SKIP_CONTAIN表示跳过节目也需要在列表中
	//   VIEW_INFO_SKIP_VANISH表示跳过的节目不包括在列表中

	uint32_t  fav_id : 6;                       // 安喜爱组排序后选择的喜爱组 当前阶段方案最多支持32个喜爱组所以5位够了
	GxBusPmViewInfoOrder order:1;               // 正向排序还是逆向排序排序，
	uint32_t  reserved1 : 3;
	/*4B*/
	uint32_t  sat_id;                           // 所选择的tp集合的id 对于卫星方案来说就是卫星的id
	/*4B*/
	uint32_t  cas_id;                           // 按cas排序后选择的cas的id
	/*4B*/
	uint32_t  tp_id;                            // 按tp排序后选择的tp的id
	/*4B*/
	uint32_t  tuner_num;                        // 按tuner排序后选择的tuner
	/*4B*/
	GxBusPmViewInfoStatus  status : 10;         // view _info是否有效的标记,如:
	// 首次开机时这个值是VIEW_INFO_DISABLE，使用的人得注意这个值的控制,
	// 比如节目删光的时候就可以吧这个值设置为VIEW_INFO_DISABLE

	uint32_t  pip_switch : 1;                   // pip的开关,用来告诉pm生成什么样的节目列表0-大画面节目列表 1-小画面的节目列表
	uint32_t  pip_main_tp_id : 16;              // 开启小画面时大画面锁定的tp id
	uint32_t  reserved2 : 6;

	uint8_t  letter[MAX_CMP_NAME];              // 按字母排序后选择的字母,现在仅支持4个字符查找:
	//   0000 - a~z
	//   ffff - other 其他字母直接输入字符 ,比如cctv就是查找满足以cctv打头的节目

	int32_t (*gx_pm_prog_check)(GxBusPmDataProg* prog, GxBusPmProgSort* list);//检测节目是否符合要求的回调函数，符合要求节目需要把用于排序的成员填入后面的list指针并且返回0，不符合要求返回-1，不使用该功能请务必填NULL
	int32_t (*gx_pm_prog_order)(const void *p1, const void *p2);//qsort使用的排序函数，传入的参数其实是GxBusPmProgSort,不使用该功能请务必填NULL
} GxBusPmViewInfo;

/**
 *说明：该枚举指明了同步哪一个数据库，需要在操作了对应的数据库后同步一下
 *数据才真正的存储下去
 */
typedef enum
{
	GXBUS_PM_SYNC_SAT = 0,
	GXBUS_PM_SYNC_TP,
	GXBUS_PM_SYNC_PROG,
	GXBUS_PM_SYNC_FAV,
	GXBUS_PM_SYNC_EXT_PROG,
}GxBusPmSyncType;

/* Exported Functions ----------------------------------------------------- */

/**
 * @brief 数据库初始化,用于打开数据库,如果数据库不存在需要创建 并且初始化
 * @param uint32_t max_sat:方案所能支持的最多卫星数量
 *		uint32_t max_tp:方案所能支持的最多tp数量
 *		uint32_t max_prog:方案所能支持的最多prog数量
 * 		uint8_t* default_path:如果为null就是默认的路径
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmDbaseInit(uint32_t max_sat,uint32_t max_tp,uint32_t max_prog,uint8_t* default_path);

/**
 * @brief	关闭数据库,下次再使用前必须再次调用初始化打开数据库
 * @param	dbp:所要关闭的数据库的句柄,关闭的时候会把没有写入文件的修改自动写入
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmDbaseClose(void);

/**
 * @brief	备份数据库的sat tp prog veritfy 文件，用于做恢复
 * @param
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmDbaseBackup(void);

/**
 * @brief	从GxBus_PmDbaseBackup备份的内存中恢复数据库
 * @param
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmDbaseComebackFromMem(void);

/**
 * @brief	释放内存中的备份文件
 * @param
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmDbaseBackupDel(void);

/**
 * @brief	获取卫星的数量
 * @param	void
 * @return	-1:发生错误
 *              正常数字:卫星数量
 */
int32_t GxBus_PmSatNumGet(void);


/**
 * @brief	通过位置获取卫星的信息
 * @param	pos:所要获取信息的起始卫星的位置
 *		Num:想要获取的卫星数量
 *		sat_arry:获取的信息的指针sat_arry:获取的信息的指针,由该函数的使用者开辟空间
 * @return	-1:发生错误
 *		正常数字:读取的真正的卫星数量
 */
int32_t GxBus_PmSatsGetByPos(uint32_t pos, uint32_t num, GxBusPmDataSat * sat_arry);

/**
 * @brief	通过id获取卫星的信息
 * @param	id:所要获取信息的卫星的id
 *		sat:获取的信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmSatGetById(uint32_t id, GxBusPmDataSat * sat);

/**
 * @brief	编辑卫星参数,编辑前需要先获取原始参数 再进行修改 其中id号是不能改动的
 * @param	sat:信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmSatModify(GxBusPmDataSat * sat);

/**
 * @brief	删除卫星,支持批量删除
 * @param	id_arry:所要删除的卫星的id
 *		num:所要删除的卫星数量
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmSatDelete(uint32_t * id_arry, uint32_t num);

/**
 * @brief	添加卫星
 * @param	sat:添加的卫星
 *
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GX_PM_DBASE_FULL:数据库已经满了
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmSatAdd(GxBusPmDataSat * sat);

/**
 * @brief	获取tp的数量
 * @param	void
 *
 * @return	-1:发生错误
 *		正常数字:tp数量
 */
int32_t GxBus_PmTpNumGet(void);

/**
 * @brief	获取某个卫星下的tp的数量
 * @param	sat_id:所要查找的卫星
 *
 *
 * @return	-1:发生错误
 *		正常数字:tp数量
 */
int32_t GxBus_PmTpNumGetBySat(uint16_t sat_id);

/**
 * @brief	通过位置获取tp的信息
 * @param	pos:所要获取信息的起始tp的位置
 *		Num:想要获取的tp数量
 *		tp_arry:获取的信息的指针tp_arry:获取的信息的指针,由该函数的使用者开辟空间
 * @return	-1:发生错误
 *		正常数字:读取的真正的tp数量
 */
int32_t GxBus_PmTpGetByPos(uint32_t pos, uint32_t num, GxBusPmDataTP * tp_arry);

/**
 * @brief	通过位置获取tp的信息,和GxBus_PmTpNumGetBySat配合使用
 * @param	pos:所要获取信息的起始tp的位置
 *		Num:想要获取的tp数量
 *		tp_arry:获取的信息的指针tp_arry:获取的信息的指针,由该函数的使用者开辟空间
 * @return	-1:发生错误
 *		正常数字:读取的真正的tp数量
 */
int32_t GxBus_PmTpGetByPosInSat(uint32_t pos, uint32_t num, GxBusPmDataTP * tp_arry);

/**
 * @brief	通过id获取tp的信息
 * @param	id:所要获取信息的tp的id
 *			tp:获取的信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmTpGetById(uint32_t id, GxBusPmDataTP * tp);

/**
 * @brief	编辑tp参数,编辑前需要先获取原始参数 再进行修改 其中id号是不能改动的
 * @param	tp:信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmTpModify(GxBusPmDataTP * tp);

/**
 * @brief	删除tp,支持批量删除
 * @param	id_arry:所要删除的tp的id
 *		num:所要删除的tp数量
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmTpDelete(uint32_t * id_arry, uint32_t num);

/**
 * @brief	检测tp是否存在 sat 缺少极化方向
 * @param	sat_id:所要检测的sat
 *		fre:所要检测的频率
 *		symbol:所要检测的符号率,如果是c和t的方案该值可以随意传
 *		polar:检测的极化方向 只在卫星方案的tp检测中才有效
 *		modulation:检测调制方式，只有在c方案的tp检测才有效
 *		tp_id:如果存在相同tp会返回最后一个相同的tp的id，不存在则为0
 *
 * @return	0  : 该tp不存在
 *		>0 : 该tp已经存在
 *		-1 : 失败
 */
int32_t GxBus_PmTpExistChek(uint16_t sat_id,
		uint32_t fre,
		uint32_t symbol,
		GxBusPmTpPolar polar,
		fe_modulation_t modulation,
		uint16_t* tp_id);

/**
 * @brief	检测tp是否存在 sat 缺少极化方向
 * @param	sat_id:所要检测的sat
 *		fre1,fre2:所要检测的频率 当fre1<=...<=fre2时 认为是相同频点
 *		symbol1,symbol2:所要检测的符号率,如果是c和t的方案该值可以随意传 symbol1<=...<=symbol2
 *		polar:检测的极化方向 只在卫星方案的tp检测中才有效
 *		modulation:检测调制方式，只有在c方案的tp检测才有效
 *		tp_id:如果存在相同tp会返回最后一个相同的tp的id，不存在则为0
 *
 * @return	0  : 该tp不存在
 *		>0 : 该tp已经存在
 *		-1 : 失败
 */
int32_t GxBus_PmTpExistChekBound(uint16_t sat_id,
		uint32_t fre1,
		uint32_t fre2,
		uint32_t symbol1,
		uint32_t symbol2,
		GxBusPmTpPolar polar,
		fe_modulation_t modulation,
		uint16_t* tp_id);

/**
 * @brief	添加tp
 * @param	tp:添加的tp
 * @return	GXCORE_SUCCESS:执行正常
 *		GX_PM_DBASE_FULL:数据库满
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmTpAdd(GxBusPmDataTP * tp);

/**
 * @brief	获取prog的数量 使用此接口时如果更改了观看模式
 *		应该先更新系统信息里的view_info
 *		再调用此接口获取新的观看模式下的节目数量
 * @param	void
 * @return	-1:发生错误
 *               正常数字:prog数量
 */
int32_t GxBus_PmProgNumGet(void);

/**
 * @brief	通过位置获取prog的信息 使用此接口时如果更改了观看模式
 *		应该先更新系统信息里的view_info
 *		再调用此节口更新节目列表,并且注意调用此节口前一定要调用GxBus_PmProgNumGet
 *		确认当前节目的数量,除非保证没有删减增加过节目 那么是不需要重复调用GxBus_PmProgNumGet的
 * @param	pos:所要获取信息的起始prog的位置
 *		Num:想要获取的prog数量
 *		prog_arry:获取的信息的指针prog_arry:获取的信息的指针,由该函数的使用者开辟空间
 * @return	-1:发生错误
 *		正常数字:读取的真正的prog数量
 */
int32_t GxBus_PmProgGetByPos(uint32_t pos, uint32_t num, GxBusPmDataProg * prog_arry);

/**
 * @brief	通过id获取prog的信息
 * @param	id:所要获取信息的prog的id
 *		prog:获取的信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgGetById(uint32_t id, GxBusPmDataProg * prog);
/**
 * @brief 获取指定的prog
 * @param uint32_t ts_id:和service_id确定一个service 不关心传入0xffffffff
 uint32_t service_id:和ts_id确定一个service 不关心传入0xffffffff
original_id:确定一个service 不关心传入0xffffffff
prog::获取的信息的指针

 * @return     	GXCORE_SUCCESS:执行正常
GXCORE_ERROR:执行失败
 */
int32_t GxBus_PmProgGetBySpecialId(uint32_t ts_id,uint32_t service_id, uint32_t original_id, GxBusPmDataProg * prog);

/**
 * @brief	通过id获取prog的url信息,该信息主要是为了给player播放用的,prog_url的
 *		空间是由使用接口的地方分配的 大小为 GX_PM_MAX_PROG_URL_SIZE
 * @param	prog:所要获取url信息的prog
 *		prog_url:获取的url信息的buffer
 *		uint32_t size:buffer的大小 如果小于GX_PM_MAX_PROG_URL_SIZE会返回错误
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgUrlGet(GxBusPmDataProg* prog, int8_t* prog_url,uint32_t size);

/**
 * @brief	通过id修改节目信息中以bool形式表示的信息,比如skip:0-跳过 1-不跳过
 * @param	type:修改的内容
 *		id_arry:所要修改的id
 *		num:所要修改的节目的数量

 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgBoolModify(GxBusPmProgModifyBoolType type, uint32_t * id_arry, uint32_t num);

/**
 * @brief	修改节目的喜爱组信息 一次一个喜爱组,如果原先节目属于这个喜爱组那么这个
 *		接口会把节目从喜爱组删除,如果节目原先不属于这个喜爱组,那么这个接口会把节目添加进去
 * @param	fav_id:所要修改的喜爱组
 *		id_arry:所要修改的节目的id
 *		Num:所要修改的节目的数量
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgFavModify(uint32_t fav_id, uint32_t * id_arry, uint32_t num);

/**
 * @brief	编辑prog参数,编辑前需要先获取原始参数 再进行修改 其中id号是不能改动的
 * @param	prog:信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgInfoModify(GxBusPmDataProg * prog);

/**
 * @brief	删除prog,支持批量删除
 * @param	id_arry:所要删除的prog的id
 *		num:所要删除的prog数量
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgDelete(uint32_t * id_arry, uint32_t num);

/**
 * @brief	添加prog
 * @param	prog:添加的prog
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 *		GX_PM_DBASE_FULL:数据库已经满了
 */
status_t GxBus_PmProgAdd(GxBusPmDataProg * prog);

/**
 * @brief	移动节目 注意 target_id不能出现在id_arry中
 * @param	id_arry:所要移动的节目id
 *		Num:所要移动的节目数量
 *		target_id:目标id,比如 次参数为5 代表要把选中的节目移动到节目id为5的节目前
 *		type:移动模式,是移动到目标id之前还是之后
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgMove(uint32_t * id_arry,
		uint32_t num,
		uint32_t target_id,
		GxBusPmProgMoveType type);

/**
 * @brief	另外一种特殊的移动节目，需要由调用的人组织好当前观看模式下的所有节目的顺序，
 *		如，当前观看模式下由10个台，那么初始顺序肯定是0~9，如果要把最后一个
 *		台移动到最前面，那么pos_arry={9,0,1,2,3,4,5,6,7,8};其他移动情况，依次类推
 * @param	pos_arry:排列好的顺序，最小值为0最大值肯定为num－1
 *		Num:所要移动的节目数量，肯定等于当前模式下的节目数量
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgMoveSpecial(uint32_t * pos_arry, uint32_t num);

/**
 * @brief 监测节目时否存在,比如用于搜台时候的保存
 * @param tp_id:所要检测的tp_id
ts_id:所要检测的ts id
service_id:所要检测的service id
original_id:所要检测的原始网络id
tuner:所要检测的tuner号
uint8_t data_plp_id: dvbt2节目独有，不用请传入0xff
uint8_t common_plp_exist: dvbt2节目独有，不用请传入0xff
uint8_t common_plp_id: dvbt2节目独有，不用请传入0xff

 * @return     	0:该节目不存在
 >1:该节目已经存在
 -1:失败
 */
//增加一个tp id 再增加原始网络id 导致搜台时需要增加存储参数
int32_t GxBus_PmProgExistChek(uint16_t tp_id,
		uint16_t ts_id,
		uint16_t service_id,
		uint16_t original_id,
		uint16_t tuner,
		uint8_t data_plp_id,
		uint8_t common_plp_exist,
		uint8_t common_plp_id);

/**
 * @brief	获取指定的prog的pos,主要用于epg删除service时的判断,
 * @param	uint32_t ts_id:和service_id确定一个service
 *		uint32_t service_id:和ts_id确定一个service
 *
 * @return	-1:获取失败
 *		正常值:节目的pos
 */
int32_t GxBus_PmProgPosGet(uint32_t ts_id,uint32_t service_id);

/**
 * @brief	获取指定的prog的pos,主要用于epg删除service时的判断
 * @param	uint32_t service_id:确定一个service
 *
 * @return	-1:获取失败
 *		正常值:节目的pos
 */
int32_t GxBus_PmProgPosGetByServiceId(uint32_t service_id);

/**
 * @brief	根据view info重新建立节目列表一般是不需要调用的，因为GxBus_PmSync
 *		和GxBus_PmViewInfoModify都会重建节目列表，除非特殊需要
 * @param
 *
 * @return	-1:获取失败
 *		正常值:该款看模式下的prog数量
 */

int32_t GxBus_PmProgListRebulid(void);
/**
 * @brief	保存自定义节目表，一旦保存了自定义节目表，那么view_info不再起
 *              作用，节目的顺序将按照自定义节目表排列。除非调用
 *              GxBus_PmProgUserListRemove.移除掉自定义列表，那么节目列表又将
 *              恢复由view info控制的状态。所以要注意，在改变节目数量前最好先移
 *              除掉自定义节目表，再合适的时机重新save自定义表，不然节目会混乱。
 * @param	uint32_t* id_arry：存储节目id号的空间，这些id号是用户排好序的。
 *              uint32_t num：id_arry中有几个id
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */

status_t GxBus_PmProgUserListSave(uint32_t* id_arry,uint32_t num);
/**
 * @brief	删除自定义节目表，一旦保存了自定义节目表，那么view_info不再起
 *              作用，节目的顺序将按照自定义节目表排列。除非调用
 *              GxBus_PmProgUserListRemove.移除掉自定义列表，那么节目列表又将
 *              恢复由view info控制的状态。所以要注意，在改变节目数量前最好先移
 *              除掉自定义节目表，再合适的时机重新save自定义表，不然节目会混乱。
 *              del自定义节目列表的时候会根据最近一次保存的view info 重建节目
 *              列表
 * @param
 *
 * @return	GXCORE_SUCCESS:执行正常
 */
status_t GxBus_PmProgUserListDel(void);

/**
 * @brief	获取cas的数量
 * @param	void
 *
 * @return	-1:发生错误
 *              正常数字:cas 数
 */
int32_t GxBus_PmCasNumGet(void);

/**
 * @brief	通过位置获取cas信息
 * @param	pos:位置
 *		Cas:cas信息
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmCasGetByPos(uint32_t pos, GxBusPmDataCasInfot * cas);

/**
 * @brief	获取节目的cas,首先得从节目中获取cas_id
 * @param	cas_id:cas的id
 *		cas:case信息
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmCasGetById(uint32_t cas_id, GxBusPmDataCasInfot * cas);

/**
 * @brief	获取喜爱组的数量
 * @param	void
 *
 * @return     -1:发生错误
 *             正常数字:获取的fav group 记录数
 */
int32_t GxBus_PmFavGroupNumGet(void);

/**
 * @brief	通过位置获取fav group信息
 * @param	pos:位置
 *		num:所要获取的数量
 *		fav_arry:cas信息
 *
 * @return	-1:失败
 *		正常数字:获取的真是数量
 */
int32_t GxBus_PmFavGroupGetByPos(uint32_t pos, uint32_t num, GxBusPmDataFavItem * fav_arry);

/**
 * @brief	通过id获取喜爱组信息
 * @param	id:喜爱组id
 *		fav_arry:cas信息
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmFavGroupGetById(uint32_t id, GxBusPmDataFavItem * fav);

/**
 * @brief	编辑fav参数,编辑前需要先获取原始参数 再进行修改 其中id号是不能改动的
 * @param	fav:信息的指针
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmFavGroupModify(GxBusPmDataFavItem * fav);

/**
 * @brief	开始一个事务 典型应用:搜索存台时由search服务控制保存节目,berkeley下 还没有实现
 * @param	void
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmTransactionBegin(void);

/**
 * @brief	提交一个事务 典型应用:搜索存台时由search服务控制保存节目,berkeley下 还没有实现
 * @param	void
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmTransactionCommit(void);

/**
 * @brief	回滚一个事务 取消开始后的事务,恢复事务开始前的状态,berkeley下 还没有实现
 * @param	void
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */

status_t GxBus_PmTransactionRollback(void);


status_t GxBus_PmViewInfoMemSet(GxBusPmViewInfo* sys);
status_t GxBus_PmViewInfoMemClear(void);

/**
 * @brief	获取观看模式
 *
 * @param	void
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmViewInfoGet(GxBusPmViewInfo* sys);

/**
 * @brief	修改 观看模式
 *
 * @param	void
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t  GxBus_PmViewInfoModify(GxBusPmViewInfo* sys);

/**
 * @brief	获取当前观看的节目信息
 *
 * @param	uint32_t tp_id,
 *              uint32_t cur_prog   : 当前观看节目的pos或者id 由GxBusPmViewInfo.type决定
 *              uint32_t ts_id,
 *              uint32_t service_id
 *
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t  GxBus_PmViewInfoCurPlayGet(uint32_t* tp_id,
		uint32_t* cur_prog,
		uint32_t* ts_id,
		uint32_t* service_id);

/**
 * @brief     恢复数据库的默认信息
 *
 * @param     uint32_t max_sat      : 方案所能支持的最多卫星数量
 *            uint32_t max_tp       : 方案所能支持的最多tp数量
 *            uint32_t max_prog     : 方案所能支持的最多prog数量
 *            uint8_t* default_path : 如果为null就是默认的路径
 *
 * @return    GXCORE_SUCCESS:执行正常
 *            GXCORE_ERROR:执行失败
 */
status_t GxBus_PmLoadDefault(uint32_t max_sat,uint32_t max_tp,uint32_t max_prog,uint8_t* default_path);

/**
 * @brief	同步数据库 执行后数据被真正写入数据库
 * @param	type:所要同步的数据类型
 * @return	GXCORE_SUCCESS:执行正常
 *		GXCORE_ERROR:执行失败
 */
status_t GxBus_PmSync(GxBusPmSyncType type);
/**
 * @brief 增加扩展信息
 *
 * @param    prog_id : 增加扩展信息的节目id
 *           size    : 扩展信息的大小
 *           void* p : 扩展信息
 *
 * @return   GXCORE_SUCCESS:执行正常
 *           GXCORE_ERROR:执行失败
 */
status_t GxBus_PmProgExtInfoAdd(uint32_t prog_id,uint32_t size, void* p);

/**
 * @brief   获取节目扩展信息
 *
 * @param   prog_id : 节目id
 *          size    : 扩展信息的大小
 *          void* p : 用于保存扩展信息的空间
 *
 * @return  GXCORE_SUCCESS : 执行正常
 *          GXCORE_ERROR   : 执行失败
 */
status_t GxBus_PmProgExtInfoGet(uint32_t prog_id,uint32_t size, void* p);

/**
 * @brief 获取pm的模块锁
 *
 * @return   GXCORE_SUCCESS:执行正常
 *           GXCORE_ERROR:执行失败
 */
status_t GxBus_PmLock(void);

/**
 * @brief  释放pm的模块锁
 *
 * @return   GXCORE_SUCCESS:执行正常
 *           GXCORE_ERROR:执行失败
 */
status_t GxBus_PmUnlock(void);

/**
 * @brief  获取数据库变化记录号，用意判断数据库是否发生了变化
 * @return  记录号
 */
int32_t GxBus_PmGetRecord(void);

/* @brief   把当前数据库信息生成符合默认数据库工具格式的文件
 *
 * @param   file_patch:文件生成路径
 *
 * @return  GXCORE_SUCCESS:执行正常
 *          GXCORE_ERROR:执行失败
 */
status_t GxBus_PmCreateDefaultDb(int8_t* file_patch);

__END_DECLS

#endif

/*@}*/

