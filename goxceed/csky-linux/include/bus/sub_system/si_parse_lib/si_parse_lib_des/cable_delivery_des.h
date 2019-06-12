/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __CABLE_DELIVERY_H__
#define __CABLE_DELIVERY_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*-----------------------------¸÷ÖÖÃèÊö·û-----------------------------------*/

/*cable delivery system 0x44 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:16;

    uint32_t frequency;

    uint32_t reserved_future_use:12;
    uint32_t FEC_outer:4;
    uint32_t modulation:8;
    uint32_t reserved1:8;

    uint32_t symbol_rate:28;
    uint32_t FEC_inner:4;
}GxSubsystemSiParseCableDeliveryDes;

__END_DECLS

#endif
/*@}*/

