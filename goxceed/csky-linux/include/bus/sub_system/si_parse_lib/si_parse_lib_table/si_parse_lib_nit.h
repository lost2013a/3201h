/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_NIT_H__
#define __SI_PARSE_LIB_NIT_H__

#include "gxcore.h"
#include "../si_parse_lib_des/nit_name_des.h"
#include "../si_parse_lib_des/service_list_des.h"
#include "../si_parse_lib_des/satellite_delivery_des.h"
#include "../si_parse_lib_des/cable_delivery_des.h"
#include "../si_parse_lib_des/terrestrial_delivery_system_des.h"
#include "../si_parse_lib_des/dtmb_delivery_system_des.h"
__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

typedef struct
{
    uint32_t network_name_count;
    GxSubsystemSiParseNitDes* network_name;

    //    uint32_t linkage_count;
    //    GxSubsystemSiParseLinkageDes* linkage;

    //    uint32_t multi_network_name_count;
    //    GxSubsystemSiParseMultiNitDes* multi_network_name;
}GxSubsystemSiParseNitLoop1;

typedef struct
{
    uint16_t transport_stream_id;
    uint16_t original_network_id;

    uint32_t reserved_future_use:4;
    uint32_t transport_descriptors_length:12;
    uint32_t service_list_count:16;

    GxSubsystemSiParseServiceListDes* service_list;

    uint32_t satellite_delivery_system_count;
    GxSubsystemSiParseSatelliteDeliveryDes* satellite_delivery_system;
    
    uint32_t cable_delivery_system_count;
    GxSubsystemSiParseCableDeliveryDes* cable_delivery_system;
    
    uint32_t terrestrial_delivery_system_count;
    GxSubsystemSiParseTerrestrialDeliveryDes* terrestrial_delivery_system;

    uint32_t dtmb_delivery_system_count;
    GxSubsystemSiParseDtmbDeliveryDes * dtmb_delivery_system;
}GxSubsystemSiParseNitLoop2;

typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t reserved_future_use1:1;
    uint32_t section_length:12;
    uint32_t reserved1:10;

    uint32_t network_id:16;
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t section_number:8;
    uint32_t reserved2:2;

    uint32_t last_section_number:8;
    uint32_t reserved_future_use2:4;
    uint32_t network_descriptors_length:12;
    uint32_t reserved3:8;

    GxSubsystemSiParseNitLoop1 loop1;

    uint32_t reserved_future_use3:4;
    uint32_t transport_stream_loop_length:12;
    uint32_t loop2_count:16;

    GxSubsystemSiParseNitLoop2* loop2;
} GxSubsystemSiParseNIT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

