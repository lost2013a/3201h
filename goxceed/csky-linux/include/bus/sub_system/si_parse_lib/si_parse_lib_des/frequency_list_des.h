/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __FREQUENCY_LIST_DES_H__
#define __FREQUENCY_LIST_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*frequency_list 0x62 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t reserved_future_use:6;
    uint32_t coding_type:2;

    uint32_t centre_frequency_count;

    uint32_t* centre_frequency;
}GxSubsystemSiParseFrequencyListDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

