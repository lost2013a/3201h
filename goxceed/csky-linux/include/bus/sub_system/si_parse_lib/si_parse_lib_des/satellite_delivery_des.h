/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SATELLITE_DELIVERY_H__
#define __SATELLITE_DELIVERY_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*satellite delivery system 0x43 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t orbital_position:16;

    uint32_t frequency;

    uint32_t west_east_flag:1;
    uint32_t polarization:2;
    uint32_t modulation:5;
    uint32_t reserved:24;

    uint32_t symbol_rate:28;
    uint32_t FEC_inner:4;
}GxSubsystemSiParseSatelliteDeliveryDes;

__END_DECLS

#endif
/*@}*/

