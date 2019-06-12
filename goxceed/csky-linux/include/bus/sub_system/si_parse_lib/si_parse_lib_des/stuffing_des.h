/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __STUFFING_DES_H__
#define __STUFFING_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*stuffing  0x42 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:24;

    uint8_t* stuffing_byte;
} GxSubsystemSiParseStuffingDes;


__END_DECLS

#endif
/*@}*/

