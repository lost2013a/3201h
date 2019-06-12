/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __STREAM_IDENTIFIER_DES_H__
#define __STREAM_IDENTIFIER_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*stream identifier 0x52 ÃèÊö·û*/
typedef struct
{

    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t component_tag:8;
    uint32_t reserved:8;
}GxSubsystemSiParseStreamIdentifierDes;

__END_DECLS

#endif
/*@}*/

