/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_BIOP_FILE_H__
#define __SI_PARSE_LIB_BIOP_FILE_H__

#include "gxcore.h"
#include "../si_parse_lib_des/iop_ior_des.h"


__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------各种表-----------------------------------*/

/*biop_file*/

typedef struct
{
    uint32_t magic;//应该为0x42494F50

    uint8_t  version_major;
    uint8_t  version_minor;
    uint8_t  byte_order;//0x00为大端
    uint8_t  message_type;

	uint32_t message_size;

	uint32_t object_key_length;//
	uint8_t* object_key;//很重要，用来确定对象的

	uint32_t object_kind_length;//应该为<=0x4
	uint8_t* object_kind;//应该为0x66696C00也就是"file"

	uint32_t object_info_length;//不知道干什么用 先忽略
	uint8_t* object_info;

	uint32_t service_context_list_count;//忽略
	uint8_t* service_context_list;

	uint32_t message_body_length;

	uint32_t content_length;
	uint8_t* content;

    
}GxSubsystemSiParseBIOPFILE;

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      把一段section数据解析成biop_file表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      biop_file数据
 *               NULL：发生错误
 */
GxSubsystemSiParseBIOPFILE* GxSubsystm_SiParseLibBiopFileParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放biop_file的空间，应用应该在通过GxSubsystm_SiParseLibBiopFileParse获取
 *  解析好的biop_file数据之后某个时刻释放biop_file的空间。
 *   
 *  @param       GxSubsystemSiParseBIOPFILE* biop_file:biop_file的存储空间，是通过GxSubsystm_SiParseLibBiopFileParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibBiopFileRelease(GxSubsystemSiParseBIOPFILE* biop_file);

__END_DECLS

#endif
/*@}*/

