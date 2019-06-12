/**
 *
 * @file        app_common_porting_as_mtc.h
 * @brief
 * @version     1.0.0
 * @date        02/11/2015 09:47:49 AM
 * @author      yugt@nationalchip.com
 *
 */
#ifndef __APP_COMMON_PORTING_AS_MTC_H__
#define __APP_COMMON_PORTING_AS_MTC_H__
#ifdef __cplusplus
extern "C" {
#endif



typedef enum
{
	APP_ENCRYPE_TYPE_TDES = 0,
	APP_ENCRYPE_TYPE_AES
}APP_ENCRYPE_TYPE_e;


typedef struct
{
	unsigned char m_encrype_type    ;
	unsigned char m_encrype_layer   ;
	unsigned int m_encrypt_key_1[4] ; //3: key1 -> key2 -> cw     2:key1->cw
	unsigned int m_encrypt_key_2[4] ; //
	unsigned int m_encrypt_cw[4]    ;
	
	unsigned int  m_descramble_id   ;
}App_Porting_MTC_Info_t ;

/*
* ≥ı ºªØ
*/

int GxApp_Porting_MTC_Init(void);

int GxApp_Porting_GetChipID(unsigned char *pID,unsigned int len);

int GxApp_Porting_MTC_Run(App_Porting_MTC_Info_t *p_info);



int GxApp_Porting_Descramble_Alloc(unsigned int *desc_id);
int GxApp_Porting_Descramble_Release(unsigned int desc_id);
int GxApp_Porting_Descramble_SetCw(unsigned int desc_id,unsigned short pid,
								const unsigned char* OddKey,
                                const unsigned char* EvenKey,int KeyLen );

#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_PORTING_AS_MTC_H__*/

