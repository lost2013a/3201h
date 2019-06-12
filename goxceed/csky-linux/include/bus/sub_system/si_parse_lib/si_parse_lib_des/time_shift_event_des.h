/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __TIME_SHIFT_EVENT_DES_H__
#define __TIME_SHIFT_EVENT_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*time shifted event 0x4f ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reference_service_id:16;
    uint32_t reference_event_id:16;
    uint32_t reserved:16;
}GxSubsystemSiParseTimeShiftEventDes;

__END_DECLS

#endif
/*@}*/

