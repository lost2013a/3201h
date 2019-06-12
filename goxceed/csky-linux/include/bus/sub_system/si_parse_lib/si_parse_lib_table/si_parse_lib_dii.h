/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_DII_H__
#define __SI_PARSE_LIB_DII_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------���ֱ�-----------------------------------*/

/*dii*/

typedef struct
{
	uint16_t module_id;
	uint16_t reserved1;

	uint32_t module_size;

	uint16_t module_version:8;
	uint16_t module_length:8;
	uint16_t reserved2;

	//GxSubsystemSiParseBiopModule* module;//ò�ƿ��Բ�����
	//private���� ���Բ���
}GxSubsystemSiParseDiiModuleInfo;

/*���ṹ��ʱֻ֧��oc, ����oc��dc�޷���dii����ֱ棬��������ait����pmt��
 * ����dii�Ժ������Ҫ��Ϊ˽�б��з���ѡ����oc����dc��������Ȼsi�޷�֪����oc����dc*/
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
	uint8_t window_size;//dc��oc����ʹ�� Ӧ��Ϊ0x00
	uint8_t ack_perid;//dc��oc����ʹ�� Ӧ��Ϊ0x00

	uint32_t tc_download_window;//dc��oc����ʹ�� Ӧ��Ϊ0x00

	uint32_t tc_download_scenario;

	uint16_t compatibility_des;//Ӧ��Ϊ0x0000
	uint16_t number_modules;
	
	GxSubsystemSiParseDiiModuleInfo* module;

}GxSubsystemSiParseDII;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      ��һ��section���ݽ�����dii��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      dii����
 *               NULL����������
 */
GxSubsystemSiParseDII* GxSubsystm_SiParseLibDiiParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�dii�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibDiiParse��ȡ
 *  �����õ�dii����֮��ĳ��ʱ���ͷ�dii�Ŀռ䡣
 *   
 *  @param       void* dii:dii�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibDiiParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibDiiRelease(void* dii);

__END_DECLS

#endif
/*@}*/

