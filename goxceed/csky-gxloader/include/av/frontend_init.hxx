/*
 * =====================================================================================
 *
 *       Filename:  frontend_init.hxx
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2010年12月07日 16时27分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhuzhg
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */

struct dvb_frontend;
extern "C" int register_frontend(struct dvb_frontend *ft);

#define DEFINE_FRONTEND(name)                                               \
	class cyg_frontend_class_##name {                                   \
		public:                                                     \
			cyg_frontend_class_##name(void) {                   \
				extern struct dvb_frontend frontend_##name; \
				register_frontend(&frontend_##name);        \
			}                                                   \
	}

#ifdef ECOS_OS

DEFINE_FRONTEND( gx1001 );
DEFINE_FRONTEND( gx1101 );
DEFINE_FRONTEND( gx1131 );
DEFINE_FRONTEND( gx1201 );
DEFINE_FRONTEND( gx1501 );

#else


#endif
