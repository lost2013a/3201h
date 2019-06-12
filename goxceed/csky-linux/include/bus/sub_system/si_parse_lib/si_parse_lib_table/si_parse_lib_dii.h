/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_DII_H__
#define __SI_PARSE_LIB_DII_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------各种表-----------------------------------*/

/*dii*/

typedef struct
{
	uint16_t module_id;
	uint16_t reserved1;

	uint32_t module_size;

	uint16_t module_version:8;
	uint16_t module_length:8;
	uint16_t reserved2;

	//GxSubsystemSiParseBiopModule* module;//貌似可以不管先
	//private数据 可以不管
}GxSubsystemSiParseDiiModuleInfo;

/*本结构暂时只支持oc, 并且oc和dc无法从dii本身分辨，而是来自ait或者pmt中
 * 所以dii以后可能需要作为私有表有方案选择是oc还是dc解析，不然si无法知道是oc还是dc*/
typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t private_indicator:1;
    uint32_t section_length:12;
    uint32_t reserved1:10;
    
	uint32_t table_id_extension:16;
	uint32_t version_number:5;
	uint32_t current_next_indicator:1;
	uint32_t section_number:8;
    uint32_t reserved2:2;

	uint8_t last_section_number;
	uint8_t protocol_discriminator;
	uint8_t dsmcc_type;
	uint8_t reserved3;


	uint16_t message_id;
	uint16_t reserved4;

	uint32_t transaction_id;

	uint32_t adaptation_length:8;
	uint32_t message_length:16;
	uint32_t reserved5:8;

	uint8_t* adaptation_data;

	uint32_t download_id;

	uint16_t block_size;
	uint8_t window_size;//dc和oc都不使用 应该为0x00
	uint8_t ack_perid;//dc和oc都不使用 应该为0x00

	uint32_t tc_download_window;//dc和oc都不使用 应该为0x00

	uint32_t tc_download_scenario;

	uint16_t compatibility_des;//应该为0x0000
	uint16_t number_modules;
	
	GxSubsystemSiParseDiiModuleInfo* module;

}GxSubsystemSiParseDII;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      把一段section数据解析成dii表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      dii数据
 *               NULL：发生错误
 */
GxSubsystemSiParseDII* GxSubsystm_SiParseLibDiiParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放dii的空间，应用应该在通过GxSubsystm_SiParseLibDiiParse获取
 *  解析好的dii数据之后某个时刻释放dii的空间。
 *   
 *  @param       void* dii:dii的存储空间，是通过GxSubsystm_SiParseLibDiiParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibDiiRelease(void* dii);

__END_DECLS

#endif
/*@}*/

