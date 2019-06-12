source unset.sh
if [ "$1" = "csky-ecos" ] ; then
	echo ARCH=csky OS=ecos Configuration  !
	export ARCH=csky
	export OS=ecos
	export CROSS_PATH=csky-ecos
fi

if [ "$1" = "csky-linux" ] ; then
	echo ARCH=csky OS=linux Configuration  !
	export ARCH=csky
	export OS=linux
	export CROSS_PATH=csky-linux
fi

if [ -z "$CROSS_PATH" ] ; then
	echo -e "\033[31m Config Errror!!! ,please check  ARCH_OS \033[0m"
	echo "               "              
	echo eg: source env.sh csky-ecos
	echo "    "source env.sh csky-linux
fi

# goxceed库版本路径
export GXLIB_PATH=`pwd`/../../goxceed/$CROSS_PATH
export GXSRC_PATH=`pwd`
# linux方案，内核代码路径
export GX_KERNEL_PATH=`pwd`/../linux-2.6.27.55

# 主芯片类型
export CHIP=gx3113h
# demod芯片类型
export DEMOD=atbm888x

# 客户硬件。
# 同一客户相同芯片方案，可能存在多版硬件设计，例如runde,rundeddr1,runde_ddr1_32m等
export DVB_CUSTOM=newstar
# 市场
export DVB_MARKET=dtmb

# 客户硬件市场:${DVB_CUSTOM}_$(DVB_MARKET)。

# 对应客户硬件的loader-sflash.bin、.boot 路径：
# gxappcommon/flashconf/loader-sflash/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)/loader-sflash.bin

# 对应客户市场的invariable_oem.ini、variable_oem.ini 路径(必须确保唯一性):
# gxappcommon/flashconf/ini/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)_$(DVB_MARKET)/invariable_oem.ini 、variable_oem.ini

# 对应客户市场的flash.conf、flash_ts.conf 路径：
# 如果市场版本存在特殊flash分区配置路径(个别市场）：
# gxappcommon/flashconf/conf/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)_$(DVB_MARKET)/flash.conf、flash_ts.conf
# 市场版本flash通用配置路径：
# gxappcommon/flashconf/conf/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)/flash.conf、flash_ts.conf

# 对应客户市场的env.sh 路径(必须确保唯一性):
# gxappcommon/sh/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)_$(DVB_MARKET)/env.sh

# CA市场
# 同一CA，可能存在不同市场版本
# 针对同一市场可能存在多个厂家。不同厂家因硬件平台、CA库等差异，需兼容差异化编译
# 对应CA目录gxapp_common/cas/$DVB_CA_1_NAME/$DVB_CA_MARKET/; gxapp_common/cas/$DVB_CA_2_NAME/$DVB_CA_MARKET/;
export DVB_CA_MARKET=gongban
# 广告市场
export DVB_AD_MARKET=gongban

# 是否编译CA，如值为no则为清流版本
export DVB_CA_FLAG=no

if [ $DVB_CA_FLAG = "yes" ]; then
	#CA枚举（与app_common_porting_stb_api.h中dvb_ca_type_t结构体中对应）
	
	export DVB_CA_TYPE=DVB_CA_TYPE_ABV38
	export DVB_CA_1_NAME=abv_cas38
	export DVB_CA_1_LIB=abvca
	export DVB_CA_1_FLAG=DVB_CA_TYPE_ABV_CAS38_FLAG
fi

#兼容双CA。多数情况下只有一个CA，第二个CA不用设置
#if [ $DVB_CA_FLAG = "yes" ]; then
#	export DVB_CA_2_NAME=byca
#	export DVB_CA_2_LIB=byca
#	export DVB_CA_2_FLAG=DVB_CA_TYPE_BY_FLAG
#fi

# set ad support type
#export DVB_AD_NAME=byads
#export DVB_AD_FLAG=DVB_AD_TYPE_BY_FLAG
#export DVB_AD_NAME=dsads
#export DVB_AD_FLAG=DVB_AD_TYPE_DS_FLAG
#export DVB_AD_LIB=dsad

# 选择OTA协议
export DVB_OTA_TYPE=DVB_NATIONALCHIP_OTA

# 设置是否支持高清列表单独显示
export DVB_HD_LIST=no

# 设置loader中是否已开启jpg logo显示支持(需与gxloader中的.config开关一致)
export DVB_JPG_LOGO=yes

# 设置芯片是否支持ac3解码
export AUDIO_DOLBY=no

# 设置是否开启PVR功能（录制、时移等）
export DVB_PVR_FLAG=yes

# 设置是否开启subtitle字幕显示功能
export DVB_SUBTITLE_FLAG=no

# 设置是否开启网络功能（youtube等） (仅linux方案支持此功能)
export DVB_NETWORK_FLAG=yes

# 设置支持OTT类型

# 是否支持USB升级
export DVB_USB_FLAG=yes

# 是否支持PVR快进、快退
export DVB_PVR_SPEED_SUPPORT=0

# 选用前面板类型 panel_xxx(市场)_xxx(厂家)_xxx(面板类型)，如PANEL_TYPE_fd650_RUNDE
# 已支持面板参考：include/bsp/panel_enum.h
export DVB_PANEL_TYPE=PANEL_TYPE_fd650_RUNDE
export PANEL_CLK_GPIO=33
export PANEL_DATA_GPIO=33
export PANEL_STANDBY_GPIO=199
export PANEL_LOCK_GPIO=33

# 选用遥控器宏定义类型 keymap_xxx(市场)_(厂家)，如KEY_GONGBAN_NATIONALCHIP_NEW
# 已支持面板参考:key_xml目录下的.xml group="KEY_GONGBAN_NATIONALCHIP_NEW"等，注意同一个kex(x).xml不能出现遥控器串键的情况（串键遥控器必须不不同key(x).xml中定义）
export DVB_KEY_TYPE=KEY_XINSIDA

# 解调芯片类型 ，参考demod_enum.h定义
export DVB_DEMOD_TYPE=DVB_DEMOD_ATBM888X

# 解调模式，参考demod_enum.h定义（目前不支持DVB_DEMOD_DVBS）
export DVB_DEMOD_MODE=DVB_DEMOD_DTMB

# 配置选用第几路ts输出 : 可选0,1,2，
export DVB_TS_SRC=1

# 配置tuner类型，参考demod/include/tuner_neum.h定义
export DVB_TUNER_TYPE=TUNER_MXL608

# 选择开机画面jpg图片，logo-jpg/目录下为可配置jpg
export DVB_LOGO_JPG=logo_nationalchip_gongban.jpg
# 配置theme资源（有线、地面、标清、高清等），参考development/theme下对应目录
export DVB_THEME=DTMB_MINI_HD
if [ "$1" = "csky-linux" ] ; then
# XML、图片等路径
export DVB_WORK_PATH='"/dvb/"'
# 广播背景图片路径
export DVB_LOGO_PATH='"/dvb/theme/logo.bin"'
export DVB_I_FRAME_PATH='"/dvb/theme/logo.bin"'
fi

if [ "$1" = "csky-ecos" ] ; then
# 广播背景图片路径
export DVB_LOGO_PATH='"/theme/logo.bin"'
export DVB_I_FRAME_PATH='"/theme/logo.bin"'
export DVB_NETWORK_FLAG=no
fi


# 宏定义参数项
# 音视频同步方式 0-PCR_RECOVER 1-VPTS_RECOVER 2-APTS_RECOVER 3-AVPTS_RECOVER 4-NO_RECOVER
export DVB_SYS_MODE=0
# 全屏视频X位置
export DVB_VIDEO_X=0
# 全屏视频Y位置
export DVB_VIDEO_Y=0
# 全屏视频宽大小
export DVB_VIDEO_W=1024
# 全屏视频高大小
export DVB_VIDEO_H=576
# 卫星最大个数（有线、地面方案设置为1）
export DVB_SAT_MAX=1
# TP频点最大个数
export DVB_TP_MAX=100
# 节目最大个数
export DVB_SERVICE_MAX=200
# DDRAM 类型
export DVB_DDRAM_TYPE=ddr3
# DDRAM 大小
export DVB_DDRAM_SIZE=128
# FLASH 大小
export DVB_FLASH_SIZE=8
# 搜索PAT超时时间（ms）
export DVB_PAT_TIMEOUT=3000
# 搜索SDT超时时间（ms）
export DVB_SDT_TIMEOUT=5000
# 搜索NIT超时时间（ms）
export DVB_NIT_TIMEOUT=10000
# 搜索PMT超时时间（ms）
export DVB_PMT_TIMEOUT=8000
# LCN开启模式下，非标码流无逻辑频道号的节目，默认起始逻辑频道号
export DVB_LCN_DEFAULT=500
# 主频点参数
export DVB_CENTER_FRE=714
export DVB_CENTER_SYMRATE=6875
export DVB_CENTER_QAM=2
# 带宽
export DVB_CENTER_BANDWIDTH=8
# 是否支持dvbc-dtmb双模
export DVB_DUAL_MODE=no
# 是否搜索全部节目
export DVB_PROGRAM_TYPE=PROGRAM_TYPE_FTA
# 硬件自动测试开关。yes- 开启自动测试功能 no -关闭自动测试功能
export DVB_AUTO_TEST_FLAG=no
# 是否支持多媒体功能
export DVB_MEDIA_FLAG=yes
# 视频缩放是否重新播放
export DVB_ZOOM_RESTART_PLAY=no
export DVB_BAD_SIGNAL_SHOW_LOGO=yes

# 排序模式
# 是否具有逻辑频道号规范。yes- 具有逻辑频道号规范 no- 无逻辑频道号规范
# 注意：如果开启LCN_DV，DVB_TAXIS_MODE必须为TAXIS_MODE_NON，即同时只存在一种排
# 序方式
export LCN_DV=no
# 排序方式，参考 csky-ecos/include/bus/module/pm/gxpm_manage.h
# 0- TAXIS_MODE_NON 1- TAXIS_MODE_CAS 2- TAXIS_MODE_LETTER 3- TAXIS_MODE_TP
# 4- TAXIS_MODE_TUNER 5- TAXIS_MODE_SCRAMBLE 6- TAXIS_MODE_SERVICE_ID 
# 7- TAXIS_MODE_USER
export DVB_TAXIS_MODE=0
# 农网等码流不规范市场，节目service_id重复、无序并无逻辑频道号规范
# 要求搜索节目按照pat表中的顺序进行排序
# yes- 按pat表排序 no- 不按pat表排序
# 注意：如果开启SORT_PROG_BY_PAT_DV，DVB_TAXIS_MODE必须为TAXIS_MODE_NON
# 即同时只存在一种排序方式。
export SORT_PROG_BY_PAT_DV=yes
# 是否使用私有数据管理。yes- 使用私有管理 no- 不使用私有管理
export USER_LIST_DV=no

#
# 硬件静音gpio配置 
# 静音gpio管脚 
export MUTE_GPIO_VALUE=31
# 设置为静音，gpio拉高/拉低(取消静音相反设置)。 1-- 拉高 0--拉低
export MUTE_GPIO_LEVEL=1

# echo export path
if [ -z "$CROSS_PATH" ] ; then
	echo
else
	echo CHIP=$CHIP
	echo DEMOD=$DEMOD
	echo PATH:
	echo GX_KERNEL_PATH=$GX_KERNEL_PATH
	echo GXLIB_PATH=$GXLIB_PATH
	echo DVB_CUSTOM=$DVB_CUSTOM
	echo DVB_MARKET=$DVB_MARKET
	echo DVB_CA_FLAG=$DVB_CA_FLAG
	echo DVB_PROGRAM_TYPE=$DVB_PROGRAM_TYPE
	if [ $DVB_CA_FLAG = "yes" ]; then
		echo DVB_CA_MARKET=$DVB_CA_MARKET
		echo DVB_CA_TYPE=$DVB_CA_TYPE
		echo DVB_CA_1_NAME=$DVB_CA_1_NAME
#		echo DVB_CA_1_LIB=$DVB_CA_1_LIB
#		echo DVB_CA_1_FLAG=$DVB_CA_1_FLAG
		echo DVB_CA_2_NAME=$DVB_CA_2_NAME
#		echo DVB_CA_2_LIB=$DVB_CA_2_LIB
#		echo DVB_CA_2_FLAG=$DVB_CA_2_FLAG
	fi
	if [ -z "$DVB_AD_NAME" ] ; then
		echo
	else
		echo DVB_AD_MARKET=$DVB_AD_MARKET
		echo DVB_AD_NAME=$DVB_AD_NAME
#		echo DVB_AD_FLAG=$DVB_AD_FLAG
#		echo DVB_AD_LIB=$DVB_AD_LIB
	fi
	echo DVB_OTA_TYPE=$DVB_OTA_TYPE
	echo DVB_JPG_LOGO=$DVB_JPG_LOGO
	echo DVB_HD_LIST=$DVB_HD_LIST
	echo DVB_USB_FLAG=$DVB_USB_FLAG
	echo DVB_PVR_FLAG=$DVB_PVR_FLAG
	echo DVB_SUBTITLE_FLAG=$DVB_SUBTITLE_FLAG
	echo AUDIO_DOLBY=$AUDIO_DOLBY
	echo DVB_NETWORK_FLAG=$DVB_NETWORK_FLAG
	echo DVB_PVR_SPEED_SUPPORT=$DVB_PVR_SPEED_SUPPORT
	echo DVB_PANEL_TYPE=$DVB_PANEL_TYPE
	echo DVB_KEY_TYPE=$DVB_KEY_TYPE
	echo DVB_LOGO_JPG=$DVB_LOGO_JPG
	echo DVB_TUNER_TYPE=$DVB_TUNER_TYPE
	echo DVB_DEMOD_TYPE=$DVB_DEMOD_TYPE
	echo DVB_DEMOD_MODE=$DVB_DEMOD_MODE
	echo DVB_TS_SRC=$DVB_TS_SRC
	echo DVB_SYS_MODE=$DVB_SYS_MODE
	echo DVB_CENTER_FRE=$DVB_CENTER_FRE
	echo DVB_DDRAM_TYPE=$DVB_DDRAM_TYPE
	echo DVB_DDRAM_SIZE=$DVB_DDRAM_SIZE
	echo DVB_FLASH_SIZE=$DVB_FLASH_SIZE
#	echo DVB_CENTER_SYMRATE=$DVB_CENTER_SYMRATE
#	echo DVB_CENTER_QAM=$DVB_CENTER_QAM
#   echo DVB_CENTER_BANDWIDTH=$DVB_CENTER_BANDWIDTH
	echo DVB_DUAL_MODE=$DVB_DUAL_MODE
    echo DVB_AUTO_TEST_FLAG=$DVB_AUTO_TEST_FLAG
	echo DVB_THEME=$DVB_THEME
	echo DVB_MEDIA_FLAG=$DVB_MEDIA_FLAG
	echo DVB_ZOOM_RESTART_PLAY=$DVB_ZOOM_RESTART_PLAY
	echo DVB_BAD_SIGNAL_SHOW_LOGO=$DVB_BAD_SIGNAL_SHOW_LOGO
	echo LCN_DV=$LCN_DV
	echo DVB_TAXIS_MODE=$DVB_TAXIS_MODE
	echo SORT_PROG_BY_PAT_DV=$SORT_PROG_BY_PAT_DV
	echo USER_LIST_DV=$USER_LIST_DV
	echo MUTE_GPIO_VALUE=$MUTE_GPIO_VALUE
	echo MUTE_GPIO_LEVEL=$MUTE_GPIO_LEVEL
fi






 




