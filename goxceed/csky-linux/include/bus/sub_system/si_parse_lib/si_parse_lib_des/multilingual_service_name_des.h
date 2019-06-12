/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __MULTILINGUAL_SERVICE_NAME_DES_H__
#define __MULTILINGUAL_SERVICE_NAME_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*multilingual_service_name 0x5d ÃèÊö·û*/
typedef struct
{
    uint8_t language[3];
    uint8_t service_provider_name_length;

    uint8_t* service_provider_name;

    uint32_t service_name_length;

    uint8_t* service_name;
}GxSubsystemSiParseMulitiService;

typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t service_name_count:16;

    GxSubsystemSiParseMulitiService* service_name;
}GxSubsystemSiParseMulitiServiceDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

