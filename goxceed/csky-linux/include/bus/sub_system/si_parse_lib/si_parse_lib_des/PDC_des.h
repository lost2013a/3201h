/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __PDC_DES_H__
#define __PDC_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*PDC_descriptor 0x69 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved_future_use:4;
    uint32_t reserved:12;

    uint32_t programme_identification_label:20;
    uint32_t reserved1:12;
}GxSubsystemSiParsePdcDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

