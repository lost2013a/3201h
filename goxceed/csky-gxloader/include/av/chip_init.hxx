/*
 * =====================================================================================
 *
 *       Filename:  chip_init.hxx
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

struct gxav_device;
extern "C" int chip_register(struct gxav_device *dev);

#define DEFINE_CHIP(name)                                              \
	class cyg_chip_class_##name {                                  \
		public:                                                \
			cyg_chip_class_##name(void) {                  \
				extern struct gxav_device chip_##name; \
				chip_register(&chip_##name);           \
			}                                              \
	}

#ifdef ECOS_OS

DEFINE_CHIP( gx3201  );
DEFINE_CHIP( gx3211  );
DEFINE_CHIP( gx3113c );
DEFINE_CHIP( gx6605s );

#else


#endif
