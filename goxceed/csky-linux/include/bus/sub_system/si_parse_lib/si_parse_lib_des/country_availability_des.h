/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __COUNTRY_AVAILABILITY_DES_H__
#define __COUNTRY_AVAILABILITY_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*country availability 0x49 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t country_availability_flag:1;
    uint32_t reserved:15;
    
    uint32_t country_count;
    uint8_t* country;
}GxSubsystemSiParseCountryDes;

__END_DECLS

#endif
/*@}*/

