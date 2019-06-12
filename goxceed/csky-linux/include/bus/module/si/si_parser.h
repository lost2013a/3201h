#ifndef __SI_PARSER_H__
#define __SI_PARSER_H__

#include <gxtype.h>
#include <stdint.h>
#include <ctype.h>
#include "gxcore.h"

__BEGIN_DECLS

typedef enum parser_status {
	PRIVATE_SECTION_OK,
	PRIVATE_SUBTABLE_OK
}private_parse_status;

/**
 * @brief	˽�б�Ľ�������
 * @param  p_section_data[IN]   : section���ݴ洢�ĵ�ַ
 *                len          : section���ݵĳ���

 * @Return private_parse_status
 */
typedef private_parse_status (*private_table_parser)(uint8_t *p_section_data, uint32_t len);

typedef enum parser_mode
{
	PARSE_WITH_STANDARD,   // need free standard parse result space
	PARSE_PRIVATE_ONLY,    // only care about private parse
	PARSE_STANDARD_ONLY,
	PARSE_SECTION_ONLY      // get the original section data
}private_parser_mode;

typedef struct table_cfg
{
	private_parser_mode mode;
	private_table_parser table_parse_fun;
}private_table_cfg;



//descriptor�Ĺ�����������
typedef int32_t (*des_parser)(uint8_t tag, uint8_t *p_section_data, uint16_t len, uint8_t *p_parsed_data);

/*description parser register*/
typedef struct
{
	uint16_t table_id;
	uint16_t desc_tag;
	des_parser des_parser_cb;
}GxDescRegister;

/* Exported Variables ----------------------------------------------------- */

/* Exported Macros -------------------------------------------------------- */
#define GET_TABLE_ID(parse_data) (*(uint8_t*)(parse_data))

#define SEC_PRIVATE_PARSE		((void*)NULL)
#define SEC_LEN_ERROR			((void*)0xfffffff1)
#define SEC_SYNTAX_INDICATOR	((void*)0xfffffff2)
#define SEC_NO_MEMORY			((void*)0xfffffff3)
#define SEC_SECTION_OK          ((void*)0xfffffff4)
#define SEC_SUBTABLE_OK         ((void*)0xfffffff5)
/* Exported Messages ------------------------------------------------------ */

/* Exported Functions ----------------------------------------------------- */
status_t GxBus_SiParserDescReg(GxDescRegister *reg);

status_t GxBus_SiParserDescUnreg(GxDescRegister *unreg);

/**
 * @brief	Ϊ�洢�������si���ݽ���һ���ڴ��
 * @param  void
 * @Return GXCORE_SUCCESS  �����ڴ�سɹ�
 GXCORE_ERROR  �����ڴ��ʧ��
 */
status_t GxBus_SiParserBufCreate(void);

/**
 * @brief	�ͷ�Ϊ�洢�������si�������������ڴ��
 * @param   void
 * @Return  void
 */
void GxBus_SiParserBufRelease(void);

/**
 * @brief	�ڻ�õ�si�������������ݣ���Ҫ��ʾ���ô˽ӿ����ͷ�
 ���ڴ�������뵽���ڴ��
 * @param   parsed_data   �洢���������ݵ��ڴ����ʼ��ַ
 * @Return  GXCORE_SUCCESS  �ͷ��ڴ��ɹ�
 GXCORE_ERROR  �ͷ��ڴ��ʧ��
 */
status_t GxBus_SiParserBufFree(uint8_t *parsed_data);

/**
 * @brief ���б�������������
 * @param  table_parse   �����˽�б������������˽�б��������������
 ��NULL
 * @param section_data   section���������ڴ����ʼ��ַ
 * @param len  section���ݵĳ���
 * @Return
 */
void* GxBus_SiParser(private_table_cfg *table_cfg,
		uint8_t *section_data,
		uint32_t len, int16_t si_subtable_id);
__END_DECLS

#endif /* __SI_PARSER_H__ */

