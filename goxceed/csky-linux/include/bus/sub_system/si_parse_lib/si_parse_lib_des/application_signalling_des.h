/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __APPLICATION_SIGNALLING_DES_H__
#define __APPLICATION_SIGNALLING_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

typedef struct
{
	uint16_t application_type;
	uint16_t reserved_duture_use:3;
	uint16_t AIT_version_number:5;
	uint16_t reserved:8;
}GxSubsystemSiParseAitInfo;

/*data_broadcast_id 0x6f ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t ait_info_count;
	GxSubsystemSiParseAitInfo* ait_info;
}GxSubsystemSiParseApplicationSignallingDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

