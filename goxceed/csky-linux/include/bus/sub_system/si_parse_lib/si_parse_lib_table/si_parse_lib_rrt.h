#ifndef __SI_PARSE_LIB_RRT_H__
#define __SI_PARSE_LIB_RRT_H__
__BEGIN_DECLS
typedef struct {
    uint32_t abbrev_rating_value_length:8;
    uint32_t reserved:24;

    GxSubsystemSiParseMSSstruct abbrev_rating_value_text;

    uint32_t rating_value_length:8;
    uint32_t reserved2:24;
    GxSubsystemSiParseMSSstruct rating_value_text;
}dimensionvalue;

typedef struct {
    uint32_t dimension_name_length:8;
    uint32_t reserved2:24;

    GxSubsystemSiParseMSSstruct dimension_name_text;
    uint32_t reserved:27;
    uint32_t graduated_scale:1;
    uint32_t values_defined:4;
    dimensionvalue * value_info;
}GxSubsystemSiParseRRTLoop;

typedef struct {
    uint32_t reserved:24;
    uint32_t rating_region:8;
}tableidextension;

typedef struct {
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t private_indicator:1;
    uint32_t reserved:10;
    uint32_t section_length:12;

    tableidextension rating_region_info;

    uint32_t reserved2:2;
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t section_number:8;
    uint32_t last_section_number:8;
    uint32_t protocol_version:8;

    uint32_t rating_region_name_length:8;
    uint32_t reserved4:24;

    GxSubsystemSiParseMSSstruct rating_region_name_text;
    uint32_t reserved5:24;
    uint32_t dimensions_defined:8;

    GxSubsystemSiParseRRTLoop * loop;

    uint32_t reserved3:22;
    uint32_t descriptor_length:10;
    uint32_t CRC_32;
}GxSubsystemSiParseRRT;
__END_DECLS
#endif
