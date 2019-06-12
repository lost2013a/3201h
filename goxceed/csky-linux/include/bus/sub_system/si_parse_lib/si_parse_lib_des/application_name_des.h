/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __APPLICATION_NAME_DES_H__
#define __APPLICATION_NAME_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*application_name_des 0x01 ÃèÊö·û*/
typedef struct
{
	uint8_t  language[3];
	uint8_t  name_length;

	uint8_t* name;
}GxSubsystemSiParseApplicationNameInfo;

typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t application_name_count;

	GxSubsystemSiParseApplicationNameInfo* name;

}GxSubsystemSiParseApplicationNameDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
