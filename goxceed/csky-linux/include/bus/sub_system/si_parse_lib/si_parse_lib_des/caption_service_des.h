#ifndef __CAPTION_SERVICE_DES_H__ 
__BEGIN_DECLS
typedef struct line21{
    uint32_t reserved:31;
    uint32_t line32_filed:1;
}Line21st;
typedef struct {
    uint32_t reserved:26;
    uint32_t caption_service_number:6;
}CaptionServiceNumber;
typedef union{
    Line21st line32_filed_info;
    CaptionServiceNumber caption_service_number_info;
}JudgeDigitalcc;
typedef struct {
    uint8_t language[3];
    uint32_t digital_cc:1;
    uint32_t reserved:7;

    JudgeDigitalcc digital_cc_info;
    
    uint32_t easy_reader:1;
    uint32_t wide_aspect_ratio:1;
    uint32_t reserved2:30;
}GxSubsystemSiParseCSDinfo;
typedef struct{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:11;
    uint32_t number_of_service:5;
    GxSubsystemSiParseCSDinfo * csdinfo;
}GxSubsystemSiParseCaptionServiceDes;
__END_DECLS
#define __CAPTION_SERVICE_DES_H__ 
#endif
