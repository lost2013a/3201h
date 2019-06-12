#ifndef __SI_PARSE_LIB_STT_H__
#define __SI_PARSE_LIB_STT_H__
__BEGIN_DECLS
typedef struct{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t private_indicator:1;
    uint32_t reserved:10;
    uint32_t section_length:12;

    uint32_t table_id_extension:16;
    uint32_t reserved2:2; 
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t section_number:8;

    uint32_t last_section_number:8;
    uint32_t protocol_version:8;
    uint32_t reserved3:16;

    uint32_t system_time;

    uint32_t reserved4:8;
    uint32_t GPS_UTC_offset:8;
    uint32_t daylight_saving:16;
    uint32_t CRC_32;
}GxSubsystemSiParseSTT;
__END_DECLS
#endif
