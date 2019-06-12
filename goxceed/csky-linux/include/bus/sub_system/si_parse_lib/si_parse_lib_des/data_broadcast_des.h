/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DATA_BROADCAST_DES_H__
#define __DATA_BROADCAST_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*data_broadcast 0x64 ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t data_broadcast_id;

    uint16_t component_tag;
    uint16_t selector_length;

    uint8_t* selector_type;

    uint8_t language[3];
    uint8_t text_length;

    uint8_t* text;
}GxSubsystemSiParseDataBroadcastDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

