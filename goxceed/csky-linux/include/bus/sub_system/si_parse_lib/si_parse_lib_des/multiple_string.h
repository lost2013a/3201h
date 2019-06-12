#ifndef __MULTIPLE_STRING_H__
#define __MULTIPLE_STRING_H__
#include "gxcore.h"
typedef struct {
    uint32_t compression_type:8;
    uint32_t mode:8;
    uint32_t number_bytes:8;
    uint32_t reserved:8;
    uint8_t * string_byte;
}GxSubsystemSiParseMssnumberSegments;
typedef struct {
    uint8_t ISO_639_language_code[3];
    uint32_t number_segments:8;
    GxSubsystemSiParseMssnumberSegments * segments_info;
}GxSubsystemSiParseMssnumberStrings;

typedef struct {
    uint32_t number_string:8;
    uint32_t reserved:24;
    GxSubsystemSiParseMssnumberStrings * string_info;
}GxSubsystemSiParseMSSstruct;
#endif
