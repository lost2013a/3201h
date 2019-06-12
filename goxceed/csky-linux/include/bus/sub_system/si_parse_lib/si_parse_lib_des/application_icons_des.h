/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __APPLICATION_ICONS_DES_H__
#define __APPLICATION_ICONS_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*application_icons_des 0x0B ÃèÊö·û*/

typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint8_t icon_locator_length;
	uint8_t reserved;

	uint8_t* icon_locator;

	uint16_t icon_flags;
	uint16_t reserved_future_use_length;

	uint8_t* reserved_future_use;
}GxSubsystemSiParseApplicationIconsDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
