/*
 * =====================================================================================
 *
 *       Filename:  firmware_init.hxx
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

struct gxav_firmware_info;

extern "C" int gxav_firmware_add_static(struct gxav_firmware_info *firmware);

#define DEFINE_FIRMWARE(chip, name)                                        \
	class cyg_firmware_class_##chip##_##name {                             \
		public:                                                            \
			cyg_firmware_class_##chip##_##name(void) {                     \
				extern struct gxav_firmware_info firmware_##chip##_##name; \
				gxav_firmware_add_static(&firmware_##chip##_##name);       \
			}                                                              \
	}

#ifdef ECOS_OS

#define DEFINE_CHIP_FIRMWARE(chip)  \
DEFINE_FIRMWARE(chip, dolby      ); \
DEFINE_FIRMWARE(chip, dts        ); \
DEFINE_FIRMWARE(chip, avsa       ); \
DEFINE_FIRMWARE(chip, avsv       ); \
DEFINE_FIRMWARE(chip, dra        ); \
DEFINE_FIRMWARE(chip, h263       ); \
DEFINE_FIRMWARE(chip, h264       ); \
DEFINE_FIRMWARE(chip, mpeg12a    ); \
DEFINE_FIRMWARE(chip, mpeg4_aac  ); \
DEFINE_FIRMWARE(chip, mpeg4v     ); \
DEFINE_FIRMWARE(chip, ogg        ); \
DEFINE_FIRMWARE(chip, ra_aac     ); \
DEFINE_FIRMWARE(chip, rv         ); \
DEFINE_FIRMWARE(chip, ra_ra8lbr  ); \
DEFINE_FIRMWARE(chip, jpeg       ); \
DEFINE_FIRMWARE(chip, audio      ); \
DEFINE_FIRMWARE(chip, video      );

DEFINE_CHIP_FIRMWARE(gx3201)
DEFINE_CHIP_FIRMWARE(gx3211)
DEFINE_CHIP_FIRMWARE(gx3113c)
DEFINE_CHIP_FIRMWARE(gx3113c_nds)
DEFINE_CHIP_FIRMWARE(gx3211_nds)
DEFINE_CHIP_FIRMWARE(gx6605s)

#else

#endif

