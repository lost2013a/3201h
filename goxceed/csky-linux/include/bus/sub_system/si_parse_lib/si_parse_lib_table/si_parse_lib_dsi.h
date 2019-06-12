/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_DSI_H__
#define __SI_PARSE_LIB_DSI_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------���ֱ�-----------------------------------*/

/*dsi*/

typedef struct
{
	GxSubsystemSiParseIORDes ior;

	//download_taps;//����
	//service_context_list;//����
	//user_info;//����
}GxSubsystemSiParseDsiServiceGateWay;

/*���ṹ��ʱֻ֧��oc, ����oc��dc�޷���dsi����ֱ棬��������ait����pmt��
 * ����dsi�Ժ������Ҫ��Ϊ˽�б��з���ѡ����oc����dc��������Ȼsi�޷�֪����oc����dc*/
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
	uint32_t server_id5;/*20���ֽڵ�server id �������ȫΪ0xff*/

	uint16_t compatibility_des;//Ӧ��Ϊ0x0000
	uint16_t private_data_length;//��oc�� �Ժ���ֽ���ȫ����ServiceGateWay������ֻ��һ��ServiceGateWay
	
	GxSubsystemSiParseDsiServiceGateWay service_gate_way;
}GxSubsystemSiParseDSI;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      ��һ��section���ݽ�����dsi��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      dsi����
 *               NULL����������
 */
GxSubsystemSiParseDSI* GxSubsystm_SiParseLibDsiParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�dsi�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibDsiParse��ȡ
 *  �����õ�dsi����֮��ĳ��ʱ���ͷ�dsi�Ŀռ䡣
 *   
 *  @param       void* dsi:dsi�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibDsiParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibDsiRelease(void* dsi);

__END_DECLS

#endif
/*@}*/

