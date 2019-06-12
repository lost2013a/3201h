#ifndef _MBIS_CLIENT_API_H_
#define _MBIS_CLIENT_API_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//--------------------  test api  ----------------------------

int mbis_client_api_test(void);

//--------------------  service api  ----------------------------

/// service initial
int mbis_client_api_init(void);

/// commit pes packet
int mbis_client_api_pes_commit(const unsigned char* sPes, int iLen);

/// service uninitial
void mbis_client_api_uninit(void);

//--------------------  access api  -----------------------------

// ��ⲥ���Ƿ�����Ȩ.
// --->0:��CA��Ȩ, 1:��CA��Ȩ.
// --->(1)ͬ����Ѷ�汾: ��Ҫ��ȡ������CAS�ţ������ж��Ƿ�����Ȩ.
// --->(2)ɽ���汾: ����Ҫ������Ȩ���, ���Ƿ��� 1.
int mbis_client_api_get_license(void);

int mbis_client_api_get_xml(char* path, unsigned int* pVersion);


typedef enum eMX_ENCRY_ALG{
	ENCRY_NONE = 0,        /// not use encrypt
	ENCRY_AES_ECB_128,     /// 128 bit AES in ECB mode
	ENCRY_AES_ECB_192,     /// 192 bit AES in ECB mode
	ENCRY_AES_ECB_256,     /// 256 bit AES in ECB mode
	ENCRY_AES_CBC_128,     /// 128 bit AES in CBC mode
	ENCRY_AES_CBC_192,     /// 192 bit AES in CBC mode
	ENCRY_AES_CBC_256,     /// 256 bit AES in CBC mode
	ENCRY_AES_CFB_128,     /// 128 bit AES in CFB mode
	ENCRY_AES_CFB_192,     /// 192 bit AES in CFB mode
	ENCRY_AES_CFB_256,     /// 256 bit AES in CFB mode
	ENCRY_AES_OFB_128,     /// 128 bit AES in OFB mode
	ENCRY_AES_OFB_192,     /// 192 bit AES in OFB mode
	ENCRY_AES_OFB_256,     /// 256 bit AES in OFB mode
	ENCRY_DES_EDE3_ECB,    /// Three key triple DES EDE in ECB mode
	ENCRY_DES_EDE3_CBC,    /// Three key triple DES EDE in CBC mode
	ENCRY_DES_EDE3_CFB,    /// Three key triple DES EDE in CFB mode
	ENCRY_DES_EDE3_OFB,    /// Three key triple DES EDE in OFB mode
	ENCRY_DES_ECB,         /// DES in ECB mode
	ENCRY_DES_CBC,         /// DES in CBC mode
	ENCRY_DES_CFB,         /// DES in CFB mode
	ENCRY_DES_OFB,         /// DES in OFB mode
	ENCRY_RC5_ECB,         /// RC5 cipher in ECB mode
	ENCRY_RC5_CBC,         /// RC5 cipher in CBC mode
	ENCRY_RC5_CFB,         /// RC5 cipher in CFB mode
	ENCRY_RC5_OFB,         /// RC5 cipher in OFB mode
	ENCRY_IDEA_ECB,        /// IDEA in ECB mode
	ENCRY_IDEA_CBC,        /// IDEA in CBC mode
	ENCRY_IDEA_CFB,        /// IDEA in CFB mode
	ENCRY_IDEA_OFB,        /// IDEA in OFB mode
	ENCRY_BLOWFISH_ECB,    /// Blowfish in ECB mode
	ENCRY_BLOWFISH_CBC,    /// Blowfish in CBC mode
	ENCRY_BLOWFISH_CFB,    /// Blowfish in CFB mode
	ENCRY_BLOWFISH_OFB,    /// Blowfish in OFB mode
	ENCRY_CAST5_ECB,       /// CAST5 in ECB mode
	ENCRY_CAST5_CBC,       /// CAST5 in CBC mode
	ENCRY_CAST5_CFB,       /// CAST5 in CFB mode
	ENCRY_CAST5_OFB,       /// CAST5 in OFB mode
	ENCRY_Unknown          /// Unknown
}MX_ENCRY_ALG;


#define MX_MAX_KEY 256

typedef struct stx_MX_Encry_Msg{
	MX_ENCRY_ALG  alg;             // ���ؼ����㷨��Ϣ.
	int           iKeySize;        // ���ؽ�����Կ���� (��λ:�ֽ�).
	unsigned char key[MX_MAX_KEY]; // ���ؽ�����Կ.
}MX_Encry_Msg;

// ����OID��Ӧ���ļ�·��(file)���Լ�������Ϣ(msg).
// ����ֵ:
//    -1: δ�ҵ����ļ�.  ����file, msgֵ������.
//     0: �ļ��ݲ�����.  ����file, msgֵ������.
//     1: �ɹ���ͬʱ�����ļ�·��(file), ���ļ��Ľ�����Ϣ(msg).
int mbis_client_api_get_file(const char* oid, char* file, MX_Encry_Msg* msg);

//int mbis_client_api_get_file(const char* oid, char* file);

int mbis_client_api_progress(const char* oid, unsigned int* pOutReceive, unsigned int* pOutTotal);

int mbis_client_api_get_size(const char* oid, unsigned int* uFileSize);

//---------------------------------------------------------------

int mbis_client_api_total_progress(unsigned int* pOutReceive, unsigned int* pOutTotal);

//---------------------------------------------------------------

typedef enum AD_Type{
	AD_Preroll = 1,
	AD_Pause   = 2,
	AD_Role    = 3
}ADType;

typedef struct _AdDesc{
	char m_File[256];
}AdDesc;

AdDesc* mbis_client_api_get_ad_file(const char* oid, ADType eADType, int* pAdNum);

void mbis_client_api_ad_release(AdDesc* pAd);

//---------------------------------------------------------------

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MBIS_CLIENT_API_H_
