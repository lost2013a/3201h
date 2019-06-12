#ifndef _MBIS_CLIENT_APP_INTERFACE_H_
#define _MBIS_CLIENT_APP_INTERFACE_H_


/* 严格的数据保护 */ 
//#define MBIS_DATA_PROTECT_ENABLE
/* 是否需要支持DRM文件实时解密 */
//#define MBIS_DRM_SUPPORT_TEST


/* 打印输出 */ 
#define MBIS_CLIENT_PRINT_OPEN

#ifdef MBIS_CLIENT_PRINT_OPEN

#define MBIS_Dbg(...)                          do {                                            \
                                                    printf("[mbis]\t");                        \
                                                    printf(__VA_ARGS__);                        \
                                                } while(0)
#else
#define MBIS_Dbg(...)                          do {                                            \
                                                } while(0)                                               
#endif 

extern void  mbis_client_porting_init(void);
extern void  mbis_client_porting_uninit(void); 
extern char *mbis_client_porting_get_usb_dir(void); 
extern int32_t mbis_client_porting_xml_enter(void); 
extern int32_t mbis_client_porting_demux_restart(uint8_t lock_mbis_freq); 
extern int32_t mbis_client_porting_ad_pause_play(uint8_t pause_flag); 
extern int32_t mbis_client_porting_ad_get_type(void); 


#endif
