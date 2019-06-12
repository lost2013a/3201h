#ifndef GXCORE_OS_BSP_H
#define GXCORE_OS_BSP_H


#ifdef ECOS_OS

#include <cyg/io/dev_class.hxx>
#include "av/gxavdev_init.hxx"
#include "av/firmware_init.hxx"
//#include "av/frontend_init.hxx"//由应用自己包
#include "av/audiodac_init.hxx"
#include "av/chip_init.hxx"
#include "shell_init.hxx"

/*
/  unicode code page reference:
/   437   U.S. (OEM)
/   720   Arabic (OEM)
/   1256  Arabic (Windows)
/   737   Greek (OEM)
/   1253  Greek (Windows)
/   1250  Central Europe (Windows)
/   775   Baltic (OEM)
/   1257  Baltic (Windows)
/   850   Multilingual Latin 1 (OEM)
/   852   Latin 2 (OEM)
/   1252  Latin 1 (Windows)
/   855   Cyrillic (OEM)
/   1251  Cyrillic (Windows)
/   866   Russian (OEM)
/   857   Turkish (OEM)
/   1254  Turkish (Windows)
/   858   Multilingual Latin 1 + Euro (OEM)
/   862   Hebrew (OEM)
/   1255  Hebrew (Windows)
/   874   Thai (OEM, Windows)
/   1258  Vietnam (OEM, Windows)
/   932   Japanese Shift-JIS
/   936   Simplified Chinese GBK
/   949   Korean
/   950   Traditional Chinese Big5
*/
#define LANG_US               fs_cp_select_US_class                  cp0        CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_JAPANESE         fs_cp_select_Japanese_class            cp1        CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_SIMP_CHINESE     fs_cp_select_Simplified_Chanese_class  cp2        CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_KOREAN           fs_cp_select_Korean_class              cp3        CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_TRAD_CHINESE     fs_cp_select_Traditional_Chanese_class cp4        CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_ARABIC_O         fs_cp_select_SBCS_class                cp5(720)   CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_ARABIC_W         fs_cp_select_SBCS_class                cp6(1256)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_GREEK_O          fs_cp_select_SBCS_class                cp7(737)   CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_GREEK_W          fs_cp_select_SBCS_class                cp8(1253)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_CENT_EUR         fs_cp_select_SBCS_class                cp9(1250)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_BALTIC_O         fs_cp_select_SBCS_class                cp10(775)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_BALTIC_W         fs_cp_select_SBCS_class                cp11(1257) CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_MULTI_LANTIN1    fs_cp_select_SBCS_class                cp12(850)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_LATIN2_O         fs_cp_select_SBCS_class                cp13(852)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_LATIN1_W         fs_cp_select_SBCS_class                cp14(1252) CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_CYRILLIC_O       fs_cp_select_SBCS_class                cp15(855)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_CYRILLIC_W       fs_cp_select_SBCS_class                cp16(1251) CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_RUSSIAN_O        fs_cp_select_SBCS_class                cp17(866)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_TURKISH_O        fs_cp_select_SBCS_class                cp18(857)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_TURKISH_W        fs_cp_select_SBCS_class                cp19(1254) CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_MULTI_LATIN1_EUR fs_cp_select_SBCS_class                cp20(858)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_HEBREW_O         fs_cp_select_SBCS_class                cp21(862)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_HEBREW_W         fs_cp_select_SBCS_class                cp22(1255) CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_THAI             fs_cp_select_SBCS_class                cp23(874)  CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_VIETNAM          fs_cp_select_SBCS_class                cp24(1258) CYGBLD_ATTRIB_INIT_PRI( 60250 );
#define LANG_UTF8             fs_utf8_class                          utf8       CYGBLD_ATTRIB_INIT_PRI( 60251 );

#define MOD_WDT         cyg_wdt_init_class        wdt0       CYGBLD_ATTRIB_INIT_PRI( 60000 );
#define MOD_IRR         cyg_irr_init_class        irr0       CYGBLD_ATTRIB_INIT_PRI( 60100 );
#define MOD_I2C         cyg_i2c_init_class        i2c        CYGBLD_ATTRIB_INIT_PRI( 60150 );
#define MOD_SCI         cyg_sci_init_class        sci0       CYGBLD_ATTRIB_INIT_PRI( 60200 );
#define MOD_FAT         fatfs_init_class          fatfs0     CYGBLD_ATTRIB_INIT_PRI( 60300 );
#define MOD_EXFAT       exfatfs_init_class     exfatfs0      CYGBLD_ATTRIB_INIT_PRI( 60301 );
#define MOD_NTFS        ntfs_init_class           ntfs0      CYGBLD_ATTRIB_INIT_PRI( 60310 );
#define MOD_MINIFS      minifs_init_class         minifs0    CYGBLD_ATTRIB_INIT_PRI( 60320 );
#define MOD_JFFS2       jffs2_init_class          jffs20     CYGBLD_ATTRIB_INIT_PRI( 60350 );
#define MOD_CAMFS       cramfs_init_class         cramfs0    CYGBLD_ATTRIB_INIT_PRI( 60360 );
#define MOD_ROMFS       romfs_init_class          romfs0     CYGBLD_ATTRIB_INIT_PRI( 60370 );
#define MOD_RAMFS       ramfs_init_class          ramfs0     CYGBLD_ATTRIB_INIT_PRI( 60380 );
#define MOD_YAFFS       yaffs_init_class          yafffs0    CYGBLD_ATTRIB_INIT_PRI( 60390 );
#define MOD_MMC         cyg_sd_init_class         sd0        CYGBLD_ATTRIB_INIT_PRI( 60400 );
#define MOD_UART        cyg_serial_init_class     gxserial   CYGBLD_ATTRIB_INIT_PRI( 60600 );
#define MOD_NORFLASH    cyg_norflash_init_class   norflash0  CYGBLD_ATTRIB_INIT_PRI( 60800 );
#define MOD_SPIFLASH    cyg_spi_gx3110_init_class spiflash0  CYGBLD_ATTRIB_INIT_PRI( 60900 );
#define MOD_FLASHIO     cyg_flashio_init_class    flashio    CYGBLD_ATTRIB_INIT_PRI( 61000 );
#define MOD_ETH         cyg_gxethdev_init_class   ethernet0  CYGBLD_ATTRIB_INIT_PRI( 61010 );
#define MOD_WIFI        cyg_gxwifidev_init_class  wifi0      CYGBLD_ATTRIB_INIT_PRI( 61010 );
#define MOD_USB3G       cyg_gxusb3gdev_init_class usb3g0     CYGBLD_ATTRIB_INIT_PRI( 61010 );
#define MOD_NET         cyg_gxnetdev_init_class   net0       CYGBLD_ATTRIB_INIT_PRI( 61100 );
#define MOD_NANDFLASH   nand_init_class           nandflash0 CYGBLD_ATTRIB_INIT_PRI( 61110 );
#define MOD_USB         cyg_usb_init_class        gxusb      CYGBLD_ATTRIB_INIT_PRI( 61200 );
#define MOD_SHELL       gx_shell_class            gxshell    CYGBLD_ATTRIB_INIT_PRI( 61120 );
#define MOD_OTP         cyg_otp_init_class        otp0       CYGBLD_ATTRIB_INIT_PRI( 60700 );
#define MOD_EEPROM(i2c_bus_id, eeprom_model, eeprom_phy_addr)      \
	cyg_eeprom_init_class CYGBLD_ATTRIB_INIT_PRI( 60701 )  eeprom0(i2c_bus_id, eeprom_model, eeprom_phy_addr);
#define MOD_MTC         cyg_mtc_init_class        mtc        CYGBLD_ATTRIB_INIT_PRI( 60710 );
#define MOD_SCPU        cyg_scpu_init_class       scpu       CYGBLD_ATTRIB_INIT_PRI( 60710 );

#define FIRM_CLASS(chip, name) cyg_firmware_class_##chip##_##name  firm_class_##chip##_##name CYGBLD_ATTRIB_INIT_PRI( 60260 );

#define CODEC_AVSA(chip)        FIRM_CLASS(chip, avsa      )
#define CODEC_DRA(chip)         FIRM_CLASS(chip, dra       )
#define CODEC_DTS(chip)         FIRM_CLASS(chip, dts       )
#define CODEC_MPEG212A(chip)    FIRM_CLASS(chip, mpeg12a   )
#define CODEC_MPEG4_AAC(chip)   FIRM_CLASS(chip, mpeg4_aac )
#define CODEC_MPEG4V(chip)      FIRM_CLASS(chip, mpeg4v    )
#define CODEC_OGG(chip)         FIRM_CLASS(chip, ogg       )
#define CODEC_RA_AAC(chip)      FIRM_CLASS(chip, ra_aac    )
#define CODEC_RA_RA8LBR(chip)   FIRM_CLASS(chip, ra_ra8lbr )
#define CODEC_RV(chip)          FIRM_CLASS(chip, rv        )
#define CODEC_AUDIO(chip)       FIRM_CLASS(chip, audio     )
#define CODEC_VIDEO(chip)       FIRM_CLASS(chip, video     )

#define AUDIODAC_CLASS(name) cyg_audiodac_class_##name  audiodac_class_##name CYGBLD_ATTRIB_INIT_PRI( 60260 );

#define AUDIODAC_PT4344   AUDIODAC_CLASS( cs4344 )
#define AUDIODAC_PT8211   AUDIODAC_CLASS( pt8211 )
#define AUDIODAC_PT8234   AUDIODAC_CLASS( pt8234 )
#define AUDIODAC_PT4334   AUDIODAC_CLASS( cs4334 )
#define AUDIODAC_PT4345   AUDIODAC_CLASS( cs4345 )

#define FRONTEND_CLASS(name) cyg_frontend_class_##name frontend_class_##name CYGBLD_ATTRIB_INIT_PRI( 60260 );

#define MOD_GX1001 FRONTEND_CLASS(gx1001)
#define MOD_GX1101 FRONTEND_CLASS(gx1101)
#define MOD_GX1131 FRONTEND_CLASS(gx1131)
#define MOD_GX1201 FRONTEND_CLASS(gx1201)
#define MOD_GX1501 FRONTEND_CLASS(gx1501)

#define MOD_1131(n,p)         cyg_frontend_class_gx1131        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60170 );
#define MOD_1201(n,p)         cyg_frontend_class_gx1201        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60160 );
#define MOD_1101(n,p)         cyg_frontend_class_gx1101        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60180 );
#define MOD_1501(n,p)         cyg_frontend_class_gx1501        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60190 );
#define MOD_113x(n,p)         cyg_frontend_class_gx113x        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60200 );
#define MOD_1001(n,p)         cyg_frontend_class_gx1001        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60210 );
#define MOD_1503(n,p)         cyg_frontend_class_gx1503        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60220 );
#define MOD_1211(n,p)         cyg_frontend_class_gx1211        frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60230 );
#define MOD_ATBM886X(n,p)     cyg_frontend_class_atbm886x      frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60240 );
#define MOD_3211(n,p)     cyg_frontend_class_gx3211      frontend(n,p)   CYGBLD_ATTRIB_INIT_PRI( 60241 );

#define MOD_AV(p)   CYGBLD_ATTRIB_INIT_PRI( 60500 ) cyg_av_init_class av0(p);

#define CHIP_CLASS(name) cyg_chip_class_##name  chip_class_##name CYGBLD_ATTRIB_INIT_PRI( 60260 );

#define CHIP_GX3211  CHIP_CLASS(gx3211)
#define CHIP_GX3201  CHIP_CLASS(gx3201)
#define CHIP_GX3113C CHIP_CLASS(gx3113c)
#define CHIP_GX6605S CHIP_CLASS(gx6605s)

#endif

#endif

