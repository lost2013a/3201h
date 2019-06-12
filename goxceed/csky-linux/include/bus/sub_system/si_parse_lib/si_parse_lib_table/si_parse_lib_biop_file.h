/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_BIOP_FILE_H__
#define __SI_PARSE_LIB_BIOP_FILE_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------���ֱ�-----------------------------------*/

/*biop_file*/

typedef struct
{
    uint32_t magic;//Ӧ��Ϊ0x42494F50

    uint8_t  version_major;
    uint8_t  version_minor;
    uint8_t  byte_order;//0x00Ϊ���
    uint8_t  message_type;

	uint32_t message_size;

	uint32_t object_key_length;//
	uint8_t* object_key;//����Ҫ������ȷ�������

	uint32_t object_kind_length;//Ӧ��Ϊ<=0x4
	uint8_t* object_kind;//Ӧ��Ϊ0x66696C00Ҳ����"file"

	uint32_t object_info_length;//��֪����ʲô�� �Ⱥ���
	uint8_t* object_info;

	uint32_t service_context_list_count;//����
	uint8_t* service_context_list;

	uint32_t message_body_length;

	uint32_t content_length;
	uint8_t* content;

    
}GxSubsystemSiParseBIOPFILE;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      ��һ��section���ݽ�����biop_file��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      biop_file����
 *               NULL����������
 */
GxSubsystemSiParseBIOPFILE* GxSubsystm_SiParseLibBiopFileParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�biop_file�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibBiopFileParse��ȡ
 *  �����õ�biop_file����֮��ĳ��ʱ���ͷ�biop_file�Ŀռ䡣
 *   
 *  @param       GxSubsystemSiParseBIOPFILE* biop_file:biop_file�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibBiopFileParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibBiopFileRelease(GxSubsystemSiParseBIOPFILE* biop_file);

__END_DECLS

#endif
/*@}*/

