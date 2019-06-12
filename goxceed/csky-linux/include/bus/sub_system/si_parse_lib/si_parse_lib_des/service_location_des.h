#ifndef __SERVICE_LOCATION_DES_H__
#define __SERVICE_LOCATION_DES_H__
#include "gxcore.h"
__BEGIN_DECLS
typedef struct {
    uint32_t stream_type:8;
    uint32_t reserved:11;
    uint32_t elementary_PID:13;

    uint8_t ISO_639_language_code[3];
    uint32_t reserved2:8;
}Elements;

typedef struct {
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:3;
    uint32_t PCR_PID:13;

    uint32_t number_elements:8;
    uint32_t reserved2:24;

    Elements * elemets_info;
}GxSubsystemSiParseSLDdes;
__END_DECLS
#endif
