/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __MULTILINGUAL_COMPONENT_DES_H__
#define __MULTILINGUAL_COMPONENT_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*multilingual_component 0x5e ÃèÊö·û*/
typedef struct
{
    uint8_t language[3];
    uint8_t text_length;

    uint8_t* text;
}GxSubsystemSiParseMulitiComponent;

typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t component_tag:8;
	uint32_t reserved:8;

    uint32_t component_count;

    GxSubsystemSiParseMulitiComponent* component;
}GxSubsystemSiParseMulitiComponentDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

