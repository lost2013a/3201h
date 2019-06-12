/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __PRIVATE_DATA_SPECIFIER_DES_H__
#define __PRIVATE_DATA_SPECIFIER_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*private_data_specifier 0x5f ÃèÊö·û*/
typedef struct
{
	uint32_t descriptor_tag:8;
	uint32_t descriptor_length:8;
	uint32_t reserved:16;

	uint32_t private_data_specifier;
}GxSubsystemSiParsePrivateDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

