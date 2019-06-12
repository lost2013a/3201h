/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DVB_J_APPLICATION_LOCATION_DES_H__
#define __DVB_J_APPLICATION_LOCATION_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*dvb_j_application location 0x4 ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t base_directory_length;

	uint8_t* base_directory;

	uint32_t class_path_extension_length;

	uint8_t* class_path_extension;

	uint32_t initial_class_length;

	uint8_t* initial_class;
}GxSubsystemSiParseDvbJApplicationLocationDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
