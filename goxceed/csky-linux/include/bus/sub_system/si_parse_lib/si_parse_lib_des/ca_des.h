/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __CA_DES_H__
#define __CA_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*ca  0x9 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t ca_system_id:16;

    uint32_t reserved:3;
    uint32_t ca_pid:13;
    uint32_t private_data_length:16;

    uint8_t* private_data;
}GxSubsystemSiParseCaDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

