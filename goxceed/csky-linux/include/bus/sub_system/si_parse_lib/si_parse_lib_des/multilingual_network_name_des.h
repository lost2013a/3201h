/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __MULTILINGUAL_NETWORK_NAME_DES_H__
#define __MULTILINGUAL_NETWORK_NAME_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*multilingual network name 0x5b ÃèÊö·û*/
typedef struct
{
    uint8_t language[3];
    uint8_t network_name_length;

    uint8_t* network_name;
}GxSubsystemSiParseMulitiNit;

typedef struct
{
    uint32_t descriptor_tag:8;  
    uint32_t descriptor_length:8;
    uint32_t network_name_count:16;

    GxSubsystemSiParseMulitiNit* network_name;
}GxSubsystemSiParseMulitiNitDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

