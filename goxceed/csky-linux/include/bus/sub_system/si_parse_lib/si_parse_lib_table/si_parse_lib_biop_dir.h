/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_BIOP_DIR_H__
#define __SI_PARSE_LIB_BIOP_DIR_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------���ֱ�-----------------------------------*/

/*biop_dir*/
typedef struct
{
   uint32_t name_count;//��ȻΪ1�����к��治��Ҫѭ����
   uint32_t id_length;
   int8_t* id;//Ҳ��������

   uint32_t kind_length;
   uint8_t* kind;//�൱��object_kind  type_id

   uint8_t binding_type;

   GxSubsystemSiParseIORDes ior;

   //obj info ֱ�Ӻ���
}GxSubsystemSiParseBIOPBINDING;

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
	uint8_t* object_kind;//Ӧ��Ϊ0x64697200Ҳ����"dir"

	uint32_t object_info_length;//��֪����ʲô�� �Ⱥ���
	uint8_t* object_info;

	uint32_t service_context_list_count;//����
	uint8_t* service_context_list;

	uint32_t message_body_length;

	uint32_t bindings_count;

	GxSubsystemSiParseBIOPBINDING* binding;
    
}GxSubsystemSiParseBIOPDIR;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      ��һ��section���ݽ�����biop_dir��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      biop_dir����
 *               NULL����������
 */
GxSubsystemSiParseBIOPDIR* GxSubsystm_SiParseLibBiopDirParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�biop_dir�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibBiopDirParse��ȡ
 *  �����õ�biop_dir����֮��ĳ��ʱ���ͷ�biop_dir�Ŀռ䡣
 *   
 *  @param       GxSubsystemSiParseBIOPDIR* biop_dir:biop_dir�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibBiopDirParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibBiopDirRelease(GxSubsystemSiParseBIOPDIR* biop_dir);

__END_DECLS

#endif
/*@}*/

