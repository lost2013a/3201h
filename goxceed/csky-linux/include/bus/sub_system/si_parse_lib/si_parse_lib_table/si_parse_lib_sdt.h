/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_SDT_H__
#define __SI_PARSE_LIB_SDT_H__

#include "gxcore.h"
#include "../si_parse_lib_des/stuffing_des.h"
#include "../si_parse_lib_des/bouquet_name_des.h"
#include "../si_parse_lib_des/service_des.h"
#include "../si_parse_lib_des/country_availability_des.h"
#include "../si_parse_lib_des/linkage_des.h"
#include "../si_parse_lib_des/nvod_reference_des.h"
#include "../si_parse_lib_des/time_shift_service_des.h"
#include "../si_parse_lib_des/mosaic_des.h"
#include "../si_parse_lib_des/ca_identifier_des.h"
#include "../si_parse_lib_des/telephone_des.h"
#include "../si_parse_lib_des/multilingual_service_name_des.h"
#include "../si_parse_lib_des/private_data_specifier_des.h"
#include "../si_parse_lib_des/data_broadcast_des.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------¸÷ÖÖ±í-----------------------------------*/

typedef struct
{
    uint32_t service_id:16;
    uint32_t EIT_schedule_flag:1;
    uint32_t EIT_present_following_flag:1;
    uint32_t running_status:3;
    uint32_t free_CA_mode:1;
    uint32_t reserved1:10;

    uint32_t descriptors_loop_length:12;
    uint32_t reserved2:20;

    uint32_t stuffing_count;
    GxSubsystemSiParseStuffingDes* stuffing;

    uint32_t bouquet_name_count;
    GxSubsystemSiParseBouquetDes* bouquet_name;

    uint32_t service_count;
    GxSubsystemSiParseServiceDes* service;

    uint32_t country_availability_count;
    GxSubsystemSiParseCountryDes* country_availability;

   //uint32_t linkage_count;
   //GxSubsystemSiParseLinkageDes* linkage;

    uint32_t NVOD_reference_count;
    GxSubsystemSiParseNvodDes* NVOD_reference;

    uint32_t time_shifted_service_count;
    GxSubsystemSiParseTimeShiftedDes* time_shifted_service;

    //uint32_t mosaic_count;
    //GxSubsystemSiParseMosaicDes* mosaic;

    uint32_t ca_identifier_count;
    GxSubsystemSiParseCaIdentifierDes* ca_identifier;

    //uint32_t telephone_count;
    //GxSubsystemSiParseTelephoneDes* telephone;

    uint32_t muliti_service_name_count;
    GxSubsystemSiParseMulitiServiceDes* muliti_service_name;

    //uint32_t private_data_specifier_count;
    //GxSubsystemSiParsePrivateDes* private_data;

    uint32_t data_broadcast_count;
    GxSubsystemSiParseDataBroadcastDes* data_broadcast;

}GxSubsystemSiParseSdtInfo;

typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t section_length:12;
    uint32_t reserved1:11;

    uint32_t transport_stream_id:16;
    uint32_t section_number:8;
    uint32_t last_section_number:8;

    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t original_network_id:16;
    uint32_t reserved2:10;

    uint32_t sdt_info_count;
    GxSubsystemSiParseSdtInfo* sdt_info;
}GxSubsystemSiParseSDT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

