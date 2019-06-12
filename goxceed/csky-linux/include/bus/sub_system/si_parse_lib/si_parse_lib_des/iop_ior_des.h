/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __IOP_IOR_DES_H__
#define __IOP_IOR_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

#define BIO_PROFILE_TAG   (0x49534F06)
#define BIO_OBJ_LOCATION_TAG   (0x49534F50)
#define BIO__MAGIC   (0x42494F50)

typedef struct
{
	uint32_t component_tag;

	uint32_t component_length:8;
	uint32_t reserved1:24;

	uint32_t carousel_id;

	uint16_t module_id;
	uint8_t version_major;
	uint8_t version_minor;

	uint32_t object_key_length;//应该小于等于0x4

	uint8_t* object_key;
}GxSubsystemSiParseBiopObjLocation;

typedef struct
{
	uint32_t tag;
	uint32_t data_length;

	uint8_t data_byte_order;
	uint8_t lite_component_count;
	uint16_t reserved1;
	
	GxSubsystemSiParseBiopObjLocation obj_location;
	
	//GxSubsystemSiParseDsmConnBinder dsm_binder;//貌似是定位pmt用的，暂时不用
	//GxSubsystemSiParseBiopLiteComponent lite_component;//不知道干什么用

}GxSubsystemSiParseBiopProfile;



/*iop ior描述*/
typedef struct
{
    uint32_t type_id_length;
    uint8_t* type_id;

	uint32_t tagged_profiles_count;//只要第一个profile，其他忽略

	union
	{
		GxSubsystemSiParseBiopProfile bio_profile;
//		GxSubsystemSiParseLiteOptionsProfile lite_options_profile;//指向其他业务的对象 暂时不支持
	};
	//其他profile统统忽略
}GxSubsystemSiParseIORDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

