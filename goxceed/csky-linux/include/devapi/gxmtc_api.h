#ifndef _GXMTC_API_H_
#define _GXMTC_API_H_

enum mtc_api_key_from {
	GXMTC_API_KEY_FROM_SOFT,
	GXMTC_API_KEY_FROM_OTP,
	GXMTC_API_KEY_FROM_CALC,
	GXMTC_API_KEY_FROM_NDS,
	GXMTC_API_KEY_FROM_MEM,
};

enum mtc_api_algorithm {
	GXMTC_API_DES,
	GXMTC_API_3DES,
	GXMTC_API_AES128,
	GXMTC_API_AES192,
	GXMTC_API_AES256,
	GXMTC_API_MULTI2,
	GXMTC_API_SMS4,
};

enum mtc_api_sub_mode {
	GXMTC_API_ECB,
	GXMTC_API_CBC,
	GXMTC_API_CFB,
	GXMTC_API_OFB,
	GXMTC_API_CTR,
};

enum mtc_api_wait_mode {
	GXMTC_API_QUERY_MODE,
	GXMTC_API_INTERRUPT_MODE,
};

enum mtc_api_residue_msg {
	GXMTC_API_RES_CLEAR,
	GXMTC_API_RES_CTS,
	GXMTC_API_RES_RBT,
	// other is clear
};

enum mtc_api_short_msg {
	GXMTC_API_SHO_CLEAR,
	GXMTC_API_SHO_IV,
	GXMTC_API_SHO_IV2,
	// other is clear
};

struct mtc_api_key_s{
	enum mtc_api_key_from key_from;
	unsigned char *value;                 //使用nds模式时，该指针指向选择 nds key 的索引值(0 ~ 7)的地址
	unsigned char  len;
};

struct mtc_api_iv_s {
	unsigned char *value;
	unsigned char  len;
};

struct mtc_api_counter_s {
	unsigned char *value;
	unsigned char  len;
};

enum mtc_api_desc_type {
	GXMTC_API_DESC_TYPE_CAS2,
	GXMTC_API_DESC_TYPE_DES,
};

enum mtc_api_cw_odd_even {
	GXMTC_API_CW_ODD_FIRST,
	GXMTC_API_CW_EVEN_FIRST,
};

#define MTC_API_INPUT_MAX_NUM   5
struct mtc_api_input_s {
	int            num;
	unsigned char *buf[MTC_API_INPUT_MAX_NUM];
	int            size[MTC_API_INPUT_MAX_NUM];
};

struct mtc_api_output_s {
	unsigned char *buf;
	int   size;
};

struct mtc_api_data_s {
	struct mtc_api_input_s    input;
	struct mtc_api_output_s   output;
	struct mtc_api_key_s      key;
	struct mtc_api_iv_s       iv;          //sub_mode 为CBC/CFB/OFB模式下要配,其他不配
	struct mtc_api_counter_s  counter;     //sub_mode 为CTR 模式要配，其他不配
	enum mtc_api_algorithm    algo;
	enum mtc_api_sub_mode     sub_mode;
	enum mtc_api_wait_mode    wait_mode;
	enum mtc_api_residue_msg  residue_msg; //残差处理方式　　default use 0
	enum mtc_api_short_msg    short_msg;   //短消息处理方法　default use 0
};

int GxMtc_NdsKeyGenerate(int nds_key_index);
int GxMtc_DataEncrypt(struct mtc_api_data_s *mtc_api_data);
int GxMtc_DataDecrypt(struct mtc_api_data_s *mtc_api_data);

/*
 *  GxMtc_CwDecrypt 是为了兼容已经在用的版本，GxMtc_DecryptCw 则是当前应该使用的解 cw
 *  接口，以后会统一使用GxMtc_DecryptCw
 *
 *  GxMtc_DecryptCw：新增参数为对流里奇偶秘钥的存放顺序配置(奇在前还是偶在前)
 */
int GxMtc_CwDecrypt(struct mtc_api_input_s *input, enum mtc_api_desc_type desc_type, int desc_id, enum mtc_api_algorithm algorithm, enum mtc_api_sub_mode sub_mode);
int GxMtc_DecryptCw(struct mtc_api_input_s *input, enum mtc_api_desc_type desc_type, int desc_id, \
		enum mtc_api_algorithm algorithm, enum mtc_api_sub_mode sub_mode, enum mtc_api_cw_odd_even odd_even);

#endif

