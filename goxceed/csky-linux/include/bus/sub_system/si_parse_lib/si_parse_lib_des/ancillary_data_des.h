/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __ANCILLARY_DATA_DES_H__
#define __ANCILLARY_DATA_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*ancillary_data 0x6b ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint8_t ancillary_data_identifier;
    uint8_t reserved;
}GxSubsystemSiParseAncillaryDataDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

