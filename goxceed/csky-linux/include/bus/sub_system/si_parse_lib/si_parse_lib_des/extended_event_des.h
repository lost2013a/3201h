/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __EXTENDED_EVENT_DES_H__
#define __EXTENDED_EVENT_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*extended event 0x4e ÃèÊö·û*/
typedef struct
{
    uint32_t item_descriptor_length;
    uint8_t* item_descriptor;

    uint32_t itrm_length;
    uint8_t* item;
}GxSubsystemSiParseExtendedEventItemDes;

typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t descriptor_number:4;
    uint32_t last_descriptor_number:4;
    uint32_t reserved:8;

    uint8_t language[3];
    uint32_t length_of_items:8;

    uint32_t item_descriptor_count;
    GxSubsystemSiParseExtendedEventItemDes* item_descriptor;

    uint32_t text_length;
    uint8_t* text;
}GxSubsystemSiParseExtendedEventDes;

__END_DECLS

#endif
/*@}*/

