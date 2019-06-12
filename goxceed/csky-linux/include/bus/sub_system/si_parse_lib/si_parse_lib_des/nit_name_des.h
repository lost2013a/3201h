/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __NIT_NAME_DES_H__
#define __NIT_NAME_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*network name 0x40 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t name_length:24;

    uint8_t* name;
} GxSubsystemSiParseNitDes;

__END_DECLS

#endif
/*@}*/

