/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DATA_BROADCAST_ID_DES_H__
#define __DATA_BROADCAST_ID_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*data_broadcast_id 0x66 ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t data_broadcast_id;

	uint32_t id_selector_byte_count; 
	uint8_t* id_selector_byte ;
}GxSubsystemSiParseDataBroadcaseIdDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
