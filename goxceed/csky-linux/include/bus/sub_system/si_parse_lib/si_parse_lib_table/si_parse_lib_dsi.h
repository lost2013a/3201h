/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_DSI_H__
#define __SI_PARSE_LIB_DSI_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------各种表-----------------------------------*/

/*dsi*/

typedef struct
{
	GxSubsystemSiParseIORDes ior;

	//download_taps;//忽略
	//service_context_list;//忽略
	//user_info;//忽略
}GxSubsystemSiParseDsiServiceGateWay;

/*本结构暂时只支持oc, 并且oc和dc无法从dsi本身分辨，而是来自ait或者pmt中
 * 所以dsi以后可能需要作为私有表有方案选择是oc还是dc解析，不然si无法知道是oc还是dc*/
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

	uint32_t server_id1;
	uint32_t server_id2;
	uint32_t server_id3;
	uint32_t server_id4;
	uint32_t server_id5;/*20个字节的server id 并且因该全为0xff*/

	uint16_t compatibility_des;//应该为0x0000
	uint16_t private_data_length;//在oc中 以后的字节数全部是ServiceGateWay，并且只有一个ServiceGateWay
	
	GxSubsystemSiParseDsiServiceGateWay service_gate_way;
}GxSubsystemSiParseDSI;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      把一段section数据解析成dsi表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      dsi数据
 *               NULL：发生错误
 */
GxSubsystemSiParseDSI* GxSubsystm_SiParseLibDsiParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放dsi的空间，应用应该在通过GxSubsystm_SiParseLibDsiParse获取
 *  解析好的dsi数据之后某个时刻释放dsi的空间。
 *   
 *  @param       void* dsi:dsi的存储空间，是通过GxSubsystm_SiParseLibDsiParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibDsiRelease(void* dsi);

__END_DECLS

#endif
/*@}*/

