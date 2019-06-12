#ifndef __SI_PARSE_LIB_MGT_H__
#define __SI_PARSE_LIB_MGT_H__
#include "gxcore.h"
__BEGIN_DECLS

typedef struct
{
    uint32_t table_type:16;//表类型
    uint32_t reserved:3;//预留
    uint32_t table_type_PID:13;//表PID

    uint32_t reserved2:27;
    uint32_t table_type_version_number:5;//当前域的值等于上面的ersion_number和实际表的version_number，可以根据1mod32计算version_number的值

    uint32_t number_bytes;//loop总长度

    uint32_t reserved3:20;
    uint32_t table_type_descriptors_length:12;//内循环中descriptor的长度
}GxSubsystemSiParseMGTLoop;

typedef struct 
{
    uint32_t table_id:8;
    uint32_t section_indicator:1;
    uint32_t private_indicator:1;
    uint32_t reserved1:10;
    uint32_t section_length:12;

    uint32_t table_id_extension:16;
    uint32_t reserved2:2;
    uint32_t version_number:5;
    uint32_t current_next_indictor:1; 
    uint32_t section_number:8;

    uint32_t last_section_number:8;
    uint32_t protocol_version:8;
    uint32_t tables_defined:16;
    GxSubsystemSiParseMGTLoop * loop;

    uint32_t reserved3:20;
    uint32_t descriptors_length:12;
    uint32_t CRC_32;//为了保持ATSC协议完整解析，CRC页进行解析.
}GxSubsystemSiParseMGT;
__END_DECLS
#endif
