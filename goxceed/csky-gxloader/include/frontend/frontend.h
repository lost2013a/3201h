#ifndef _DVBFRONTEND_H_
#define _DVBFRONTEND_H_

typedef enum fe_type {
	FE_QPSK,
	FE_QAM,
	FE_OFDM,
	FE_ATSC,
	FE_DTMB,
} fe_type_t;

typedef enum fe_caps {
	FE_IS_STUPID                  = 0,
	FE_CAN_INVERSION_AUTO         = 0x1,
	FE_CAN_FEC_1_2                = 0x2,
	FE_CAN_FEC_2_3                = 0x4,
	FE_CAN_FEC_3_4                = 0x8,
	FE_CAN_FEC_4_5                = 0x10,
	FE_CAN_FEC_5_6                = 0x20,
	FE_CAN_FEC_6_7                = 0x40,
	FE_CAN_FEC_7_8                = 0x80,
	FE_CAN_FEC_8_9                = 0x100,
	FE_CAN_FEC_AUTO               = 0x200,
	FE_CAN_QPSK                   = 0x400,
	FE_CAN_QAM_16                 = 0x800,
	FE_CAN_QAM_32                 = 0x1000,
	FE_CAN_QAM_64                 = 0x2000,
	FE_CAN_QAM_128                = 0x4000,
	FE_CAN_QAM_256                = 0x8000,
	FE_CAN_QAM_AUTO               = 0x10000,
	FE_CAN_TRANSMISSION_MODE_AUTO = 0x20000,
	FE_CAN_BANDWIDTH_AUTO         = 0x40000,
	FE_CAN_GUARD_INTERVAL_AUTO    = 0x80000,
	FE_CAN_HIERARCHY_AUTO         = 0x100000,
	FE_CAN_8VSB                   = 0x200000,
	FE_CAN_16VSB                  = 0x400000,
	FE_NEEDS_BENDING              = 0x20000000, // not supported anymore, don't use (frontend requires frequency bending)
	FE_CAN_RECOVER                = 0x40000000, // frontend can recover from a cable unplug automatically
	FE_CAN_MUTE_TS                = 0x80000000  // frontend can stop spurious TS data output
} fe_caps_t;

struct dvb_frontend_info {
	char       name[128];
	fe_type_t  type;
	unsigned int      frequency_min;
	unsigned int      frequency_max;
	unsigned int      frequency_stepsize;
	unsigned int      frequency_tolerance;
	unsigned int      symbol_rate_min;
	unsigned int      symbol_rate_max;
	unsigned int      symbol_rate_tolerance;   /* ppm */
	unsigned int      notifier_delay;      /* DEPRECATED */
	fe_caps_t  caps;
};

/**
 *  Check out the DiSEqC bus spec available on http://www.eutelsat.org/ for
 *  the meaning of this struct...
 */
struct dvb_diseqc_master_cmd {
	unsigned char msg [6];    /*  { framing, address, command, data [3] } */
	unsigned char msg_len;    /*  valid values are 3...6  */
};

struct dvb_diseqc_slave_reply {
	unsigned char msg [4];    /*  { framing, data [3] } */
	unsigned char msg_len;    /*  valid values are 0...4, 0 means no msg  */
	int     timeout;    /*  return from ioctl after timeout ms with */
};                          /*  errorcode when no message was received  */

typedef enum fe_sec_voltage {
	SEC_VOLTAGE_13,
	SEC_VOLTAGE_18,
	SEC_VOLTAGE_OFF
} fe_sec_voltage_t;

typedef enum fe_sec_tone_mode {
	SEC_TONE_ON,
	SEC_TONE_OFF
} fe_sec_tone_mode_t;

typedef enum fe_sec_mini_cmd {
	SEC_MINI_A,
	SEC_MINI_B
} fe_sec_mini_cmd_t;

typedef enum fe_status {
	FE_HAS_SIGNAL  = 0x01,   /*  found something above the noise level */
	FE_HAS_CARRIER = 0x02,   /*  found a DVB signal  */
	FE_HAS_VITERBI = 0x04,   /*  FEC is stable  */
	FE_HAS_SYNC    = 0x08,   /*  found sync bytes  */
	FE_HAS_LOCK    = 0x10,   /*  everything's working... */
	FE_TIMEDOUT    = 0x20,   /*  no lock within the last ~2 seconds */
	FE_REINIT      = 0x40    /*  frontend was reinitialized,  */
} fe_status_t;                   /*  application is recommended to reset */
/*  DiSEqC, tone and parameters */

typedef enum fe_spectral_inversion {
	INVERSION_OFF,
	INVERSION_ON,
	INVERSION_AUTO
} fe_spectral_inversion_t;

typedef enum fe_code_rate {
	FEC_NONE = 0,
	FEC_1_2,
	FEC_2_3,
	FEC_3_4,
	FEC_4_5,
	FEC_5_6,
	FEC_6_7,
	FEC_7_8,
	FEC_8_9,
	FEC_AUTO,
	/* below for DVB-S2 */
	FEC_S2_QPSK_1_2,
	FEC_S2_QPSK_2_3,
	FEC_S2_QPSK_3_4,
	FEC_S2_QPSK_5_6,
	FEC_S2_QPSK_7_8,
	FEC_S2_QPSK_8_9,
	FEC_S2_QPSK_3_5,
	FEC_S2_QPSK_4_5,
	FEC_S2_QPSK_9_10,
	FEC_S2_8PSK_1_2,
	FEC_S2_8PSK_2_3,
	FEC_S2_8PSK_3_4,
	FEC_S2_8PSK_5_6,
	FEC_S2_8PSK_7_8,
	FEC_S2_8PSK_8_9,
	FEC_S2_8PSK_3_5,
	FEC_S2_8PSK_4_5,
	FEC_S2_8PSK_9_10
} fe_code_rate_t;

typedef enum fe_modulation {
	QPSK,
	QAM_16,
	QAM_32,
	QAM_64,
	QAM_128,
	QAM_256,
	QAM_AUTO,

	VSB_8,
	VSB_16,
	PSK_8,
	APSK_16,
	APSK_32,
	DQPSK,

	CRXX = 14,//dvbs
	CR12,
	CR23,
	CR34,
	CR45,
	CR56,
	CR67,
	CR78,

	CRXXX = 22,//dvbs2
	QPSK14,
	QPSK13,
	QPSK25,
	QPSK12,
	QPSK35,
	QPSK23,
	QPSK34,
	QPSK45,
	QPSK56,
	QPSK89,
	QPSK910,
	_8PSK35,
	_8PSK23,
	_8PSK34,
	_8PSK56,
	_8PSK89,
	_8PSK910
} fe_modulation_t;

typedef enum fe_transmit_mode {
	TRANSMISSION_MODE_2K,
	TRANSMISSION_MODE_8K,
	TRANSMISSION_MODE_AUTO
} fe_transmit_mode_t;

typedef enum fe_bandwidth {
	BANDWIDTH_8_MHZ,
	BANDWIDTH_7_MHZ,
	BANDWIDTH_6_MHZ,
	BANDWIDTH_AUTO
} fe_bandwidth_t;

typedef enum fe_guard_interval {
	GUARD_INTERVAL_1_32,
	GUARD_INTERVAL_1_16,
	GUARD_INTERVAL_1_8,
	GUARD_INTERVAL_1_4,
	GUARD_INTERVAL_AUTO
} fe_guard_interval_t;

typedef enum fe_hierarchy {
	HIERARCHY_NONE,
	HIERARCHY_1,
	HIERARCHY_2,
	HIERARCHY_4,
	HIERARCHY_AUTO
} fe_hierarchy_t;

struct dvb_qpsk_parameters {
	unsigned int         symbol_rate;  /* symbol rate in Symbols per second */
	fe_code_rate_t   fec_inner;    /* forward error correction (see above) */
};

struct dvb_qam_parameters {
	unsigned int         symbol_rate; /* symbol rate in Symbols per second */
	fe_code_rate_t   fec_inner;   /* forward error correction (see above) */
	fe_modulation_t  modulation;  /* modulation type (see above) */
};

struct dvb_vsb_parameters {
	fe_modulation_t modulation;  /* modulation type (see above) */
};

struct dvb_ofdm_parameters {
	fe_bandwidth_t      bandwidth;
	fe_code_rate_t      code_rate_HP;  /* high priority stream code rate */
	fe_code_rate_t      code_rate_LP;  /* low priority stream code rate */
	fe_modulation_t     constellation; /* modulation type (see above) */
	fe_transmit_mode_t  transmission_mode;
	fe_guard_interval_t guard_interval;
	fe_hierarchy_t      hierarchy_information;
};


struct dvb_frontend_parameters {
	unsigned int frequency;     /* (absolute) frequency in Hz for QAM/OFDM/ATSC */
	/* intermediate frequency in kHz for QPSK */
	fe_spectral_inversion_t inversion;
	union {
		struct dvb_qpsk_parameters qpsk;
		struct dvb_qam_parameters  qam;
		struct dvb_ofdm_parameters ofdm;
		struct dvb_vsb_parameters  vsb;
	} u;
	unsigned int unicable_init_fre; //unicable centre freq 按本振计算 (9750/10600...)
	unsigned short tone_if_freq;// user center freq (1210..)
	unsigned char lnb_index;
	unsigned char scrpf;// //unicable ifeq channel (0~7)

};

struct dvb_frontend_event {
	fe_status_t status;
	struct dvb_frontend_parameters parameters;
};
#if 1

//cth
#define MAX_EVENT 8
struct dvb_fe_events {
    struct dvb_frontend_event events[MAX_EVENT];
    int eventw;
    int eventr;
    int overflow;
};
#endif

struct fe_tp_parameters {
	unsigned int frequency;
	unsigned int symbol_rate;
};

struct fe_blindscan_parameters {
	unsigned int fcenter;
	unsigned int lpf_bw_window;
	unsigned int tp_num;
	int lsymbol_rate;
};

struct tp_info {
	unsigned int type;//0:DVBS 1:DIRECTV 2:DVBS2 3:DVBS2
	unsigned int frequency;
	unsigned int symbol_rate;
	unsigned int modulation;
};

/**
 * When set, this flag will disable any zigzagging or other "normal" tuning
 * behaviour. Additionally, there will be no automatic monitoring of the lock
 * status, and hence no frontend events will be generated. If a frontend device
 * is closed, this flag will be automatically turned off when the device is
 * reopened read-write.
 */
#define FE_TUNE_MODE_ONESHOT 0x01

#define FE_GET_INFO                61

#define FE_DISEQC_RESET_OVERLOAD   62
#define FE_DISEQC_SEND_MASTER_CMD  63
#define FE_DISEQC_RECV_SLAVE_REPLY 64
#define FE_DISEQC_SEND_BURST       65  /* fe_sec_mini_cmd_t */

#define FE_SET_TONE                66  /* fe_sec_tone_mode_t */
#define FE_SET_VOLTAGE             67  /* fe_sec_voltage_t */
#define FE_ENABLE_HIGH_LNB_VOLTAGE 68  /* int */

#define FE_READ_STATUS             69
#define FE_READ_BER                70
#define FE_READ_SIGNAL_STRENGTH    71
#define FE_READ_SNR                72
#define FE_READ_UNCORRECTED_BLOCKS 73

#define FE_SET_FRONTEND            76
#define FE_GET_FRONTEND            77
#define FE_GET_EVENT               78
#define FE_SET_FRONTEND_TUNE_MODE  81 /* unsigned int */

#define FE_DISHNETWORK_SEND_LEGACY_CMD 80
#define FE_SET_BLINDSCAN           82
#define FE_GET_BLINDSCAN           83

#define FE_GET_TP_INFO             85

#endif /*_DVBFRONTEND_H_*/

