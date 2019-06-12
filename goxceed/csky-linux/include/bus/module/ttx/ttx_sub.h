#ifndef __COM_TTX_SUB_H__
#define __COM_TTX_SUB_H__

#include <gxtype.h>
#include "gxcore.h"

__BEGIN_DECLS

extern unsigned char ttx_font_data[66585];

//extern GXOSD_RegionHandle_t g_RegionHandle ;
extern uint32_t CLUT[4][8];

extern uint8_t g_chSetNum ;
extern uint8_t CcOpenFlag;
extern uint8_t g_chTtxOsdExit ;
extern uint8_t g_chUserActionTtx;
extern uint8_t g_chMagzineNumber;
extern uint16_t g_wPageNumber;
extern uint8_t g_chSearchNotSetPosition;
extern uint8_t g_bPageRecived;
extern uint8_t g_chTtxStartAddX;
extern uint8_t g_chTtxStartAddY;

#define TTX_USED_CPU_COPY
#define CHARACTER_SIZE_ENLARGE
#define TTX_NEW_CHARACTER_SET
#ifdef TTX_NEW_CHARACTER_SET
#define s_AsciiFontWidth        12
#define s_AsciiFontHeight       16
#else
#define s_AsciiFontWidth        16
#define s_AsciiFontHeight       20
#endif

//Surface
#if 1
//Full Screen
#define TTX_SURFACE_WIDTH   520
#define TTX_SURFACE_HIGHT   500
#define TTX_SURFACE_X_START 20
#define TTX_SURFACE_Y_START 40
#else
//Original
#define TTX_SURFACE_WIDTH   720
#define TTX_SURFACE_HIGHT   576
#define TTX_SURFACE_X_START 120
#define TTX_SURFACE_Y_START 78
#endif


/*#if !(CHIP_GX6103 || CHIP_GX6107 || CHIP_GX3002)
#define TTX_PES_BUFFER   (32*1024)
extern uint32_t BUF_PES_TTX_START_ADDR;          // from ld
extern uint32_t BUF_PES_END_ADDR;                // from ld

#define TTX_FILTER_BUF_START   ((uint32_t)&BUF_PES_TTX_START_ADDR)
#define TTX_FILTER_BUF_SIZE    ((uint32_t)TTX_PES_BUFFER)                   // 32KB


#elif CHIP_GX3002
extern uint32_t BUF_PES_TTX_START_ADDR;
#define TTX_FILTER_BUF_START   ((uint32_t)&BUF_PES_TTX_START_ADDR)
#define TTX_FILTER_BUF_SIZE    (32*1024)
#define STC                    *(volatile uint32_t*)(0x300028A8)

#else*/

//extern uint32_t CHIP_PES_BASE_ADDR;          // from ld
//extern uint32_t BUF_PES_SIZE;                // from ld

#define TTX_FILTER_BUF_START
#define TTX_FILTER_BUF_SIZE

//#endif

//extern uint8_t g_SppBuffer[];

#define PIC_CTRL        *(volatile uint32_t*)(0x40005028)

#define MIX_CTRL        *(volatile uint32_t*)(0x4000501C)


/* Exported Constants ----------------------------------------------------- */
#define PES_PARSE_BUF_SIZE      (64 * 1024)
#define PES_PACKET_MAX_LEN      (1024 * 13)

// 16*45*4+26*45: 16/X26, 16/X27, 16/X28, 16/X29, X0~X25
//#define PAGE_BUFFER_SIZE        4100

// 16*45*2+26*45: 16/X26, 16/X27,  X0~X25
#define PAGE_BUFFER_SIZE                2700
//#define MAGZINE_NUM_CACHE               8
#define DEFAULT_MAGAZINE_NUM_CACHE	3
// for record three magazines, 100 pages pre magazine--300, the magagine number is inputed by app
//#define nBufferBlockNum               (MAGZINE_NUM_CACHE * 100)                   // 246 // 700 // ((720 * 576 * 2 + 180000) / 1300) //
#define ONE_MAGAZINE_BLOCKS		100
#define PES_FROM_SI_NUM                 40
#define nCcBufferBlockNum               100


#define BLACK                  0  // 0x0C0C0C
#define BLUE                   4  // 0xFF0000
#define GREEN                  2  // 0x00FF00
#define RED                    1  // 0x0000FF
#define CYAN                   6  // 0xFFFF00
#define MAGENTA                5  // 0xFF00FF
#define YELLOW                 3  // 0X04D4E4
#define HALF_BLUE              12 // 0xFF8080
#define HALF_GREEN             10 // 0x80FF80
#define HALF_RED               9  // 0x8080FF
#define HALF_CYAN              14 // 0xFFFF80
#define HALF_MAGENTA           13 // 0xFF80FF
#define HALF_YELLOW            11 // 0x80FFFF
#define WHITE                  7  // 0xFCFCFB
#define GREY                   15 // 0x808080
#define TRANSPARENCE           8

#define TTX_AUTO_REFRESH_COLOR      (3-3)
#define TTX_AUTO_CHAR_FONT          (4-3)
// color(TTX_AUTO_REFRESH_COLOR) + 0x1b + A + U + T + O +0x1b + color
#define TTX_SUBPAGE_NUM_COLOR       (TTX_AUTO_CHAR_FONT + 6)

//语言定义
#define	Latin         0x00
#define	Czech         0x01
#define	English       0x02
#define	Estonian      0x03
#define	French        0x04
#define	German        0x05
#define	Italian       0x06
#define	Lettish       0x07
#define	Polish        0x08
#define	Portuguese    0x09
#define	Rumanian      0x0a
#define	Serbian_Latin 0x0b
#define	Swedish       0x0c
#define	Turkish       0x0d
#define	Greek         0x0f
//G0特别字符的坐标
#define TeleTextSection   0x20
#define SubListSize       169//子字符集列表的个数
#define SUBCHAR_NUMBER    13
#define ListSize          96

#ifdef TTX_NEW_CHARACTER_SET
#  define G0_2_3   0x23
#  define G0_2_4   0x24
#  define G0_4_0   0x40
#  define G0_5_B   0x5b
#  define G0_5_C   0x5c
#  define G0_5_D   0x5d
#  define G0_5_E   0x5e
#  define G0_5_F   0x5f
#  define G0_6_0   0x60
#  define G0_7_B   0x7b
#  define G0_7_C   0x7c
#  define G0_7_D   0x7d
#  define G0_7_E   0x7e
#else
#  define G0_2_3   18
#  define G0_2_4   24
#  define G0_4_0   2
#  define G0_5_B   69
#  define G0_5_C   75
#  define G0_5_D   81
#  define G0_5_E   87
#  define G0_5_F   93
#  define G0_6_0   4
#  define G0_7_B   71
#  define G0_7_C   77
#  define G0_7_D   83
#  define G0_7_E   89
#endif
//斯拉夫语系0x1*(G2也选择Cyrillic)

#define	Serbian_Cyrillic         0x10
#define	Serbian_Cyrillic_Set     0x10
#define	Serbian_Cyrillic_1_Set   0x20
#define	Serbian_Cyrillic_2_Set   0x24
#define	Serbian_Cyrillic_3_Set   0x25
#define	Russian                  0x11
#define	Ukrainian                0x12
//阿拉伯语系0x2*(G2也选择Arabic)
#define Arabic                   0x20
//希伯来语系0x3*(G2选择Arabic)
#define Hebrew                   0x30
#define Arabic_Set               0x40
//希伯来语系0x3*(G2选择Arabic)
#define Hebrew_Set               0x55
//希腊语系
#define Greek_Set                0x30


//海明码8/4码提取数据，由于大小端关系。已经进行大小端转换
#define hamming84(data) (((data&(uint8_t)0x1)<<3) + ((data&(uint8_t)0x4)) + ((data&(uint8_t)0x10)>>3) + ((data&(uint8_t)0x40)>>6))
#define L_TO_M(tmp1)    (((tmp1&0x1)<<7)+((tmp1&0x2)<<5)+((tmp1&0x4)<<3)+((tmp1&0x8)<<1)+((tmp1&0x10)>>1)+((tmp1&0x20)>>3)+((tmp1&0x40)>>5)+((tmp1&0x80)>>7))
#define ODD(DATA)       (L_TO_M(DATA)&0x7F)

//海明码24/18码提取数据，由于大小端关系。已经进行大小端转换
#define hamming2418_1(data) ((uint32_t)(((data&0x2)<<2) + (data&0x4) + ((data&0x8)>>2) + ((data&0x20)>>5)))
#define hamming2418_2(data) ((uint32_t)(L_TO_M(data)&0x7f))
#define hamming2418_3(data) ((uint32_t)(L_TO_M(data)&0x7f))

struct page_link {
	uint8_t m_chLinkEn;//显示结构使能
	uint8_t m_chMagazine;
	uint8_t m_chPage;
	uint16_t m_wSubcode;
};

struct x_29_pack {
	uint8_t m_chDefaultG0G2;
	uint8_t m_chDefaultG02;
	uint8_t m_chX29Langctrl;
	uint8_t m_chDefaultFrontCol;
	uint8_t m_chDefaultFrontClut;
	uint8_t m_chBackColourChangeEn;

};

struct x_26_pack {
	uint8_t m_chAddress;
	uint8_t m_chMode;
	uint8_t m_chData;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

struct view_page {
	uint8_t m_chDefaultG0G2;
	uint8_t m_chDefaultG02;
	uint8_t m_chX28Langctrl;
	uint8_t m_chDefaultFrontClut;
	uint8_t m_chDefaultBackClut;
	uint8_t m_chDefaultBackCol;
	uint8_t m_chDefaultFrontCol;
	uint8_t m_chShowState:7;
	uint8_t m_chShow24:1;
	uint8_t m_chModChar[26][40];
	struct x_26_pack m_X26Pack[16][13];
	struct page_link m_PageLink[4];
};

struct page_buffer {
	uint8_t  m_chNowMagazine ;
	uint8_t  m_chNowPage     ;
	uint16_t m_wNowSubCode   ;
	uint8_t  m_chTransMeth   ;
	uint8_t  m_chC4_C10      ;
	uint8_t  m_chDefaultG0G2 ;
	uint8_t  m_chPageContext[30][41];
	uint8_t  m_chPageX26Context[16][41];  // the MAX count is 0xf, from "draft ETSI EN 300 706 V1.2.1"
	uint8_t  m_chPageX27Context[16][41];  // the MAX count is 0xf, from "draft ETSI EN 300 706 V1.2.1"
	//uint8_t  m_chPageX28Context[16][41];// the MAX count is 0xf, from "draft ETSI EN 300 706 V1.2.1"
	//uint8_t  m_chPageX29Context[16][41];// the MAX count is 0xf, from "draft ETSI EN 300 706 V1.2.1"
	struct page_buffer *m_NextPage;
	struct page_buffer *m_PriorPage;
}*PageLinkList;

struct osd_view {
	uint8_t m_chChar;                // 字符
	uint32_t m_chFrontColor;         // 前景色颜色,见色表
	uint8_t m_chCharSize;            // 0普通, 1纵向放大1倍, 2横向放大1倍,  3双倍
	uint8_t m_chG0G2LanguageSelect;  // g0g2语言选择
	uint8_t m_chG02LanguageSelect;   // g0的第二个字符集语言选择
	uint8_t m_chSetSelect;           // 0:G0第一个字符集1:G2字符集2:分裂镶嵌字符集
	                                 // 3:联合镶嵌字符集4:平滑镶嵌字符集8:G0的第二个字符集
	uint32_t m_chBackColor;          // 背景色
	uint8_t m_chFlash;               // 闪烁
	uint8_t m_chConceal;
	uint8_t m_chMosaics;             // 1:Mosaics 0:Alpha
	uint8_t m_chContiguousM;         // 1:Contiguous Mosaics 0:Separated Mosaics
	uint8_t m_chHoldMosaics;
	uint8_t m_chHoldChar;
	uint8_t m_chX26ChangeDataEnable; // for X26
	uint8_t m_chX26ChangeChar;
	uint8_t m_chX26ColumnMode16;     // for X26 Column Mode 0x10 : GO Characters without diacriticak mark
};



typedef enum com_ttx_err {
	COM_TTX_NO_ERROR = 1,
	COM_TTX_PAGE_INSERT_NO_ERROR,
	COM_TTX_PAGE_INSERT_ERROR,
	COM_TTX_PAGE_DEC_SUCCEED,
	COM_TTX_PAGE_IN_DEC,
	COM_TTX_BUF_CLEAN_NO_ERROR,
	COM_TTX_BUF_CLEAN_ERROR,
}com_ttx_err_t;



typedef struct color_pre_s {
	int32_t r;
	int32_t g;
	int32_t b;
}color_pre_t;

#ifndef _PES_HEADER_MARCO_
#define _PES_HEADER_MARCO_
#define pes_packet_head__stream_id(ts_data_ptr)             (*((uint8_t*)ts_data_ptr + 3))
#define pes_packet_head__PES_packet_length_h(ts_data_ptr)   (*((uint8_t*)ts_data_ptr + 4))
#define pes_packet_head__PES_packet_length_l(ts_data_ptr)   (*((uint8_t*)ts_data_ptr + 5))
#define pes_packet_head__PES_header_data_length(pes_buffer) (*((uint8_t*)((uint8_t*)pes_buffer + 8)))
#endif

#define teletext_buffer_packet_ptr(buffer_ptr,packet_num,packet_length) ((uint8_t*)((uint8_t*)buffer_ptr + packet_num*packet_length))
#define pes_datafield_head__data_unit_id(pes_packet_ptr)                (*((uint8_t*)pes_packet_ptr))
#define pes_datafield_head__packet_ptr(pes_packet_ptr)                  ((uint8_t*)pes_packet_ptr + 3)
#define teletext_pack_head__magazine_address(packet_ptr)                (*((uint8_t*)packet_ptr + 1))
#define teletext_pack_head__packet_address(packet_ptr)                  (*((uint8_t*)packet_ptr + 2))


//x0
#define pack_x0__page_number_units(packet_ptr) (*((uint8_t*)packet_ptr + 3))
#define pack_x0__page_number_tens(packet_ptr)  (*((uint8_t*)packet_ptr + 4))
#define pack_x0__s1(packet_ptr)                (*((uint8_t*)packet_ptr + 5))
#define pack_x0__s2_c4(packet_ptr)             (*((uint8_t*)packet_ptr + 6))
#define pack_x0__s3(packet_ptr)                (*((uint8_t*)packet_ptr + 7))
#define pack_x0__s4_c5_c6(packet_ptr)          (*((uint8_t*)packet_ptr + 8))
#define pack_x0__c7_c8_c9_c10(packet_ptr)      (*((uint8_t*)packet_ptr + 9))
#define pack_x0__c11_c14(packet_ptr)           (*((uint8_t*)packet_ptr + 10))
#define pack_x0__data(packet_ptr,x)            (*((uint8_t*)packet_ptr + 11 + x))
//27包

#define pack_x27_0_3__Designation_Code(packet_ptr)        (*((uint8_t*)packet_ptr + 3))
#define pack_x27_0_3__Link_ptr(packet_ptr,link_num)       (((uint8_t*)packet_ptr + 4 + 6 * link_num))
#define pack_x27_0_3__Link_Control(packet_ptr)            (*((uint8_t*)packet_ptr + 40))
#define pack_x27_0_3__CRC(packet_ptr)                     (*((uint8_t*)packet_ptr + 41))

#define Link__page_number_units(Link_ptr)      (*((uint8_t*)Link_ptr + 0))
#define Link__page_number_tens(Link_ptr)       (*((uint8_t*)Link_ptr + 1))
#define Link__s1(Link_ptr)                     (*((uint8_t*)Link_ptr + 2))
#define Link__s2_m1(Link_ptr)                  (*((uint8_t*)Link_ptr + 3))
#define Link__s3(Link_ptr)                     (*((uint8_t*)Link_ptr + 4))
#define Link__s4_m2_m3(Link_ptr)               (*((uint8_t*)Link_ptr + 5))

//8/30/1
#define pack_8_30_1__Designation_Code(packet_ptr)              (*((uint8_t*)packet_ptr + 3))
#define pack_8_30_1__page_number_units(packet_ptr)             (*((uint8_t*)packet_ptr + 4))
#define pack_8_30_1__page_number_tens(packet_ptr)              (*((uint8_t*)packet_ptr + 5))
#define pack_8_30_1__s1(packet_ptr)                            (*((uint8_t*)packet_ptr + 6))
#define pack_8_30_1__s2_m1(packet_ptr)                         (*((uint8_t*)packet_ptr + 7))
#define pack_8_30_1__s3(packet_ptr)                            (*((uint8_t*)packet_ptr + 8))
#define pack_8_30_1__s4_m2_m3(packet_ptr)                      (*((uint8_t*)packet_ptr + 9))
#define pack_8_30_1__Network_Identification_Code_1(packet_ptr) (*((uint8_t*)packet_ptr + 10))
#define pack_8_30_1__Network_Identification_Code_2(packet_ptr) (*((uint8_t*)packet_ptr + 11))
#define pack_8_30_1__p1_o5_r1(packet_ptr)                      (*((uint8_t*)packet_ptr + 12))
#define pack_8_30_1__Date1(packet_ptr)                         (*((uint8_t*)packet_ptr + 13))
#define pack_8_30_1__Date2(packet_ptr)                         (*((uint8_t*)packet_ptr + 14))
#define pack_8_30_1__Date3(packet_ptr)                         (*((uint8_t*)packet_ptr + 15))
#define pack_8_30_1__Time1(packet_ptr)                         (*((uint8_t*)packet_ptr + 16))
#define pack_8_30_1__Time2(packet_ptr)                         (*((uint8_t*)packet_ptr + 17))
#define pack_8_30_1__Time3(packet_ptr)                         (*((uint8_t*)packet_ptr + 18))
#define pack_8_30_1__data(packet_ptr,x)                        (*((uint8_t*)packet_ptr + 19 + x))
//pack_26
#define pack_x26__Designation_Code(packet_ptr)   (*((uint8_t*)packet_ptr + 3))
#define pack_x26__data(packet_ptr,y,x)           (*(((uint8_t*)packet_ptr + 4 + y * 3 + x)))

#define pack_x28__Designation_Code(packet_ptr)   (*((uint8_t*)packet_ptr + 3));
#define pack_x28__data(packet_ptr,y,x)           (*(((uint8_t*)packet_ptr + 4 + y * 3 + x)))

#define pack_x29__Designation_Code(packet_ptr)   (*((uint8_t*)packet_ptr + 3));
#define pack_x29__data(packet_ptr,y,x)           (*(((uint8_t*)packet_ptr + 4 + y * 3 + x)))

extern void teletext_dec_main(void);

extern void initial_teletext(void);

extern int draw_screen(uint8_t);

extern void  user_interface(uint8_t );

extern void osd_draw_teletext(uint8_t ,uint8_t ,struct osd_view* );

extern uint8_t    teletext_dec_8_30_1(uint8_t*);

extern void teletext_dec_x0(uint8_t*,uint8_t);

extern void teletext_dec_x27(struct page_buffer*);

extern void teletext_dec_x1_24(struct page_buffer*,uint8_t);

extern void teletext_dec_x26(struct page_buffer*);

extern void teletext_dec_x28(struct page_buffer*);

extern void teletext_dec_x29(uint8_t,struct page_buffer*);

extern void ttx_parse_x0_x24_char(uint8_t , struct view_page *,struct osd_view *);

extern void ttx_buffer_malloc(uint8_t **);

extern int ttx_buffer_is_full(void);

extern void check_packet_length(uint8_t *,uint32_t ,uint8_t *);

extern void color_check(uint32_t *, uint32_t , uint16_t *, uint8_t , uint32_t*);

extern void ttx_get_data(uint8_t* pData,uint16_t* pLength);

extern status_t ttx_filter_setup(uint16_t ttx_pid);
status_t ttx_filter_free(void);
extern status_t ttx_filter_resert(void);
status_t ttx_demux_open(void);
void ttx_filter_handle(void);
extern void character_enlarger_width(uint8_t *pPreChar,uint32_t nLength,uint8_t *pResult);

extern void character_enlarger_height(uint8_t *pPreChar, uint32_t nLength,uint8_t chCountPerLine,uint8_t *pResult);

extern void draw_wait_page(void);

__END_DECLS

#endif /* __COM_TTX_SUB_H__ */

