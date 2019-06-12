/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_DDB_H__
#define __SI_PARSE_LIB_DDB_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------���ֱ�-----------------------------------*/

/*ddb*/


/*���ṹ��ʱֻ֧��oc, ����oc��dc�޷���ddb����ֱ棬��������ait����pmt��
 * ����ddb�Ժ������Ҫ��Ϊ˽�б��з���ѡ����oc����dc��������Ȼsi�޷�֪����oc����dc*/
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

	uint32_t download_id;

	uint32_t adaptation_length:8;
	uint32_t message_length:16;
	uint32_t reserved5:8;

	uint8_t* adaptation_data;

	uint16_t module_id;
	uint8_t module_version;
	uint8_t reserved6;

	uint16_t block_number;//��һ��Ϊ0
	
	uint32_t data_len;//message_length-adaptation_length-6

	uint8_t* data;

}GxSubsystemSiParseDDB;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      ��һ��section���ݽ�����ddb��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      ddb����
 *               NULL����������
 */
GxSubsystemSiParseDDB* GxSubsystm_SiParseLibDdbParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�ddb�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibDdbParse��ȡ
 *  �����õ�ddb����֮��ĳ��ʱ���ͷ�ddb�Ŀռ䡣
 *   
 *  @param       void* ddb:ddb�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibDdbParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibDdbRelease(void* ddb);

__END_DECLS

#endif
/*@}*/

