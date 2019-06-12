/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SHORT_EVENT_DES_H__
#define __SHORT_EVENT_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*short event 0x4d ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:16;

    uint8_t language[3];
    uint32_t event_name_length:8;

    uint8_t* event_name;

    uint32_t text_length;

    uint8_t* text;
}GxSubsystemSiParseShortEventDes;

__END_DECLS

#endif
/*@}*/

