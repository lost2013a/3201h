#ifndef __SI_PARSE_LIB_VCT_H__
#define __SI_PARSE_LIB_VCT_H__
#include "gxcore.h"
#include "../si_parse_lib_des/extended_channel_name_des.h"
#include "../si_parse_lib_des/service_location_des.h"
#include "../si_parse_lib_des/ATSC_time_shifted_service_des.h"
__BEGIN_DECLS
typedef struct{
    uint32_t path_select:1;
    uint32_t out_of_band:1;
    uint32_t reserved:30;
}CVCTspace;
typedef struct {
    uint32_t reserved;
}TVCTvacant;
typedef union{
    CVCTspace cvctinfo;
    TVCTvacant tvctinfo;  
}Distinguish;
typedef struct {
    uint8_t short_name[14];
    uint32_t reserved:16;

    uint32_t major_channel_number:10;
    uint32_t minor_channel_number:10;
    uint32_t modulation_mode:8;
    uint32_t reserved5:4;

    uint32_t carrier_frequency;
    uint32_t channel_TSID:16;
    uint32_t program_number:16;

    uint32_t ETM_location:2;
    uint32_t access_controlled:1;
    uint32_t hidden:1;
    uint32_t reserved2:28;

    Distinguish info;

    uint32_t reserved6:6;
    uint32_t hide_guide:1;
    uint32_t reserved3:3;
    uint32_t service_type:6;
    uint32_t source_id:16;

    uint32_t reserved4:22;
    uint32_t descriptor_length:10;


    uint32_t extendednamedes_count;
    GxSubsystemSiParseExtendedNamedes * extendednamedes;

    uint32_t sld_count;
    GxSubsystemSiParseSLDdes * sldes;

    uint32_t tssd_count;
    GxSubsystemSiParseTSSDdes * tssdes;
}GxSubsystemSiParseVCTloop;
typedef struct {
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t private_indicator:1;
    uint32_t reserved:10;
    uint32_t section_length:12;

    uint32_t transport_stream_id:16;
    uint32_t reserved2:10;
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;

    uint32_t section_number:8;
    uint32_t last_section_number:8;
    uint32_t protocol_version:8;
    uint32_t num_channels_in_section:8;

    GxSubsystemSiParseVCTloop * loop;
    uint32_t reserved3:22;
    uint32_t additional_descriptors_length:10;
    uint32_t CRC_32;
}GxSubsystemSiParseVCT;
__END_DECLS
#endif
