/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __COMPONENT_DES_H__
#define __COMPONENT_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*component 0x50 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved_future_use:4;
    uint32_t stream_content:4;
    uint32_t component_type:8;

    uint32_t component_tag:8;
    uint8_t language[3];

    uint32_t text_length;
    uint8_t* text;
}GxSubsystemSiParseComponentDes;

__END_DECLS

#endif
/*@}*/

