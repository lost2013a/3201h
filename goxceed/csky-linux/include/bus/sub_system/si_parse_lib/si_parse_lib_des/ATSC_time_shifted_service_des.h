#ifndef __ATSC_TIME_SHIFTED_SERVICE_DES_H__
#define __ATSC_TIME_SHIFTED_SERVICE_DES_H__
#include "gxcore.h"
__BEGIN_DECLS
typedef struct {
    uint32_t reserved:6;
    uint32_t time_shift:10;
    uint32_t reserved2:6;
    uint32_t major_channel_number:10;

    uint32_t minor_channel_number:10;
    uint32_t reserved3:22;
}TSSServices;

typedef struct {
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:11;
    uint32_t number_of_services:5;

    TSSServices * service_info;
}GxSubsystemSiParseTSSDdes;

__END_DECLS
#endif
