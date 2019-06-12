/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __TERRESTRIAL_DELIVERY_SYSTEM_DES_H__
#define __TERRESTRIAL_DELIVERY_SYSTEM_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*terrestrial delivery system 0x5a ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t reserved:16;

    uint32_t centre_frequency;

    uint32_t banwidth:3;
    uint32_t reserved_future_use:5;
    uint32_t constellation:2;
    uint32_t hierarchy_information:3;
    uint32_t code_rate_HP_stream:3;
    uint32_t code_rate_LP_stream:3;
    uint32_t guard_interval:2;
    uint32_t transmission_mode:2;
    uint32_t other_frequency_flag:1;
    uint32_t reserved1:8;

    uint32_t reserved_future_use1;
}GxSubsystemSiParseTerrestrialDeliveryDes;


/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

