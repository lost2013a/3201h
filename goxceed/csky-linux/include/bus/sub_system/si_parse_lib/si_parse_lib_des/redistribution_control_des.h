#ifndef __REDISTRIBUTIION_CONTROL_DES_H__
#define __REDISTRIBUTIOIN_CONTROL_DES_H__
__BEGIN_DECLS
typedef struct {
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:16;
    uint8_t * attribute;
}GxSubsystemSiParseRedistributionControlDes;
__END_DECLS
#endif
