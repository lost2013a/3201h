/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __TIME_SHIFT_SERVICE_DES_H__
#define __TIME_SHIFT_SERVICE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*time shifted service 0x4c ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;

    uint16_t reference_service_id;
}GxSubsystemSiParseTimeShiftedDes;

__END_DECLS

#endif
/*@}*/

