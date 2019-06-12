/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DVB_J_APPLICATION_DES_H__
#define __DVB_J_APPLICATION_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*dvb_j_application 0x3 ÃèÊö·û*/
typedef struct
{
	uint32_t parameter_length:8;
	uint32_t reserved:24;

	uint8_t* parameter;
}GxSubsystemSiParseParameter;

typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t parameter_count;

	GxSubsystemSiParseParameter* parameter;
}GxSubsystemSiParseDvbJApplicationDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
