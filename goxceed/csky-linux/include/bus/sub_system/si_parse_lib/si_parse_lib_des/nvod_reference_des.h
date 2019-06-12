/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __NVOD_REFERENCE_DES_H__
#define __NVOD_REFERENCE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*NVOD reference 0x4b ÃèÊö·û*/
typedef struct
{
    uint16_t  transport_stream_id;
    uint16_t  original_network_id;
    uint16_t  service_id;
    uint16_t  reserved;
}GxSubsystemSiParseNvodInfo;

typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t descriptor_count:16;

    GxSubsystemSiParseNvodInfo* descriptor;
}GxSubsystemSiParseNvodDes;

__END_DECLS

#endif
/*@}*/

