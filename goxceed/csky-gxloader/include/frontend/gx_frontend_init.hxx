#ifndef	GX3110_FRONTEND_INIT_H
#define	GX3110_FRONTEND_INIT_H

#ifdef __cplusplus

extern "C" void gx3110_frontend_mod_init(unsigned int num ,const char *profile);

class cyg_frontend_init_class {
public:
        cyg_frontend_init_class(unsigned int num,const char *profile)
	{
                gx3110_frontend_mod_init(num,profile);
	}
};

extern "C" void frontend_mod_init_gx113x  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1001  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1503  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1501  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1101  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1201  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1211  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_atbm884x(unsigned int num, const char *profile);
extern "C" void frontend_mod_init_atbm888x(unsigned int num, const char *profile);
extern "C" void frontend_mod_init_hd2816  (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_lgs9x   (unsigned int num, const char *profile);
extern "C" void frontend_mod_init_gx1801  (unsigned int num, const char *profile);

#define DEFINE_FRONTEND(name)                                                       \
	class cyg_frontend_class_##name {                                           \
	public:                                                                     \
		cyg_frontend_class_##name(unsigned int num,const char *profile) {   \
                        frontend_mod_init_##name(num,profile);                      \
			}                                                           \
	}

DEFINE_FRONTEND( gx1001 );
DEFINE_FRONTEND( gx1503 );
DEFINE_FRONTEND( gx1101 );
DEFINE_FRONTEND( gx113x );
DEFINE_FRONTEND( gx1201 );
DEFINE_FRONTEND( gx1211 );
DEFINE_FRONTEND( gx1501 );
DEFINE_FRONTEND( atbm884x );
DEFINE_FRONTEND( hd2816 );
DEFINE_FRONTEND( lgs9x );
DEFINE_FRONTEND( gx1801 );


#endif
#endif
