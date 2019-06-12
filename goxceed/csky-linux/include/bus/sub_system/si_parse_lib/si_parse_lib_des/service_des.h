/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SERVICE_DES_H__
#define __SERVICE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*service 0x48 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t service_type:8;
    uint32_t service_provider_length:8;

    uint8_t* provider_name;

    uint32_t service_name_length;

    uint8_t* service_name;
}GxSubsystemSiParseServiceDes;

__END_DECLS

#endif
/*@}*/

