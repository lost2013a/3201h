/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __BOUQUET_NAME_H__
#define __BOUQUET_NAME_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*bouquet name  0x47 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t name_length:24;

    uint8_t* name;
}GxSubsystemSiParseBouquetDes;

__END_DECLS

#endif
/*@}*/

