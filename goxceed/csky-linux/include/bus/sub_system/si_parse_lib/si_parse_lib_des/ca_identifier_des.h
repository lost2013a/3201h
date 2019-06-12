/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __CA_IDENTIFIER_DES_H__
#define __CA_IDENTIFIER_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*CA identifier 0x53 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t ca_system_count:16;
    uint16_t* ca_system_id;
}GxSubsystemSiParseCaIdentifierDes;

__END_DECLS

#endif
/*@}*/

