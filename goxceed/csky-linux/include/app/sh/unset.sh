unset CHIP
unset DEMOD
#unset ARCH
#unset OS
unset CROSS_PATH
unset GXLIB_PATH
unset GXSRC_PATH
unset GX_KERNEL_PATH

unset DVB_CUSTOM
unset DVB_MARKET
unset DVB_CA_MARKET
unset DVB_AD_MARKET
unset DVB_CA_FLAG
unset DVB_USB_FLAG
unset DVB_PVR_SPEED_SUPPORT
unset DVB_PANEL_TYPE
unset PANEL_CLK_GPIO
unset PANEL_DATA_GPIO
unset PANEL_STANDBY_GPIO
unset PANEL_LOCK_GPIO
unset DVB_KEY_TYPE
# 公版默认不需设置(Arial)，只有特殊字库如矢量/utf-8等字体类型配置
# 字库目录名 （theme/font/xxxx）
unset DVB_FONT_TYPE
# 字库类型（gb2312/utf-8）
unset DVB_LANGUAGE_TYPE
unset DVB_TUNER_TYPE
unset DVB_DEMOD_TYPE
unset DVB_DEMOD_MODE
unset DVB_TS_SRC
unset DVB_AUTO_TEST_FLAG
unset DVB_THEME
unset DVB_MEDIA_FLAG
unset DVB_ZOOM_RESTART_PLAY
unset DVB_BAD_SIGNAL_SHOW_LOGO
# 排序模式
unset LCN_DV
unset DVB_TAXIS_MODE
unset USER_LIST_DV
unset SORT_PROG_BY_PAT_DV
# 硬件静音gpio配置
unset MUTE_GPIO_VALUE
unset MUTE_GPIO_LEVEL
# 音量等级
unset AUDIO_VOLUME_LEVEV
unset AUDIO_VOLUME_STEP


# CA枚举（与app_common_porting_stb_api.h中dvb_ca_type_t结构体中对应），配置参考对应CA代码目录下的readme.txt
unset DVB_CA_TYPE
# 对应市场（厂家）CA链接库名称（如libY1120-tonghui-gx3001-20121212D.a，设为Y1120-tonghui-gx3001-20121212D）
unset DVB_CA_1_LIB
unset DVB_CA_2_LIB
# 对应CA代码中宏定义
unset DVB_CA_1_FLAG
unset DVB_CA_2_FLAG
# 对应CA名称（目录）,如（cdcas3.0）
unset DVB_CA_1_NAME
unset DVB_CA_2_NAME
# 高安MTC
unset DVB_CA_MTC

# 广告名称（目录），配置参考对应广告代码目录下的readme.txt
unset DVB_AD_NAME
unset DVB_AD_FLAG
unset DVB_AD_NAME_1
unset DVB_AD_FLAG_1
# 广告类型
unset DVB_AD_TYPE
# 对应市场（厂家）广告链接库名称
unset DVB_AD_LIB

# OTA协议（类型）
unset DVB_OTA_TYPE
unset OTA_PID
unset OTA_TABLEID

unset DVB_JPG_LOGO
unset AUDIO_DOLBY
unset DVB_SUBTITLE_FLAG
unset DVB_PVR_FLAG
unset DVB_NETWORK_FLAG
unset DVB_USB_WIFI
unset DVB_OTT_NAME
unset DVB_OTT_SERVER
unset LOGO_SHOW_DELAY

unset DVB_HD_LIST
unset DVB_LOGO_JPG
unset DVB_WORK_PATH
unset DVB_LOGO_PATH
unset DVB_I_FRAME_PATH
unset DVB_SYS_MODE
unset DVB_VIDEO_X
unset DVB_VIDEO_Y
unset DVB_VIDEO_W
unset DVB_VIDEO_H
# OSD颜色
unset DVB_OSD_BPP
unset DVB_SAT_MAX
unset DVB_TP_MAX
unset DVB_SERVICE_MAX
unset DVB_DDRAM_TYPE
unset DVB_DDRAM_SIZE
unset DVB_FLASH_SIZE
unset DVB_PAT_TIMEOUT
unset DVB_SDT_TIMEOUT
unset DVB_NIT_TIMEOUT
unset DVB_PMT_TIMEOUT
unset DVB_LCN_DEFAULT
unset DVB_CENTER_FRE
unset DVB_CENTER_SYMRATE
unset DVB_CENTER_QAM
unset DVB_CENTER_BANDWIDTH
unset DVB_FRE_LOW
unset DVB_FRE_HIGH
unset DVB_DUAL_MODE
unset DVB_PROGRAM_TYPE
unset DVB_PCM_AUDIO
unset DVB_PLAY_AD_FORM_USB
unset DVB_PLAY_LOGO
unset MBIS_CLIENT_FLAG
unset DVB_CASCAM_FLAG
unset DVB_CASCAM_CA_MODE
unset DVB_RELEASE_TEST

# 芯片mark名称，同一系列可能有多款芯片。例如gx3211系列芯片，
# gx3201h/gx3113h/gx3202q-d等等。根据需要在对应env.sh中添加
# DVB_CHIP_MARK用以生成readme.txt的一致性。
unset DVB_CHIP_MARK

# 原development/app/include/sys_common_config.h中配置项，统一支持env.sh中配置/
# 修改。
unset DVB_DISPLAY_SCREEN_MODE
unset DVB_HDMI_MODE
unset DVB_HDMI_SWITCH_FLAG
unset DVB_ASPECT_MODE
unset DVB_PLAY_FREEZE_SWITCH
unset DVB_AUTO_ADAPT
unset DVB_VOLUME_VALUE
unset DVB_AUDIO_TRACK
unset DVB_RADIO_AUDIO_TRACK
unset DVB_AC3_BYPASS_MODE
unset DVB_TRACK_GLOBLE_FLAG
unset DVB_VOLUMN_GLOBLE_FLAG
unset DVB_MUTE_FLAG
unset DVB_MENU_LANGUAGE
unset DVB_TELTEXT_LANGUAGE
unset DVB_OSD_TRANS
unset DVB_VIDEOCOLOR_BRIGHTNESS
unset DVB_VIDEOCOLOR_SATURATION
unset DVB_VIDEOCOLOR_CONTRAST
unset DVB_BAR_TIME
unset DVB_TIMEZONE
unset DVB_PASSWORD_FLAG
unset DVB_PASSWORD_LEN
unset DVB_PASSWORD
unset DVB_MANUSAL_SEARCH_FRE
unset DVB_MANUSAL_SEARCH_SYM
unset DVB_MANUSAL_SEARCH_QAM
unset DVB_MANUSAL_SEARCH_BANDWIDTH
unset DVB_PLAY_DURATION
unset DVB_FRONT_MONITER_DURATION
unset DVB_MAX_SEARIAL_LEN
unset DVB_DTMB_DVBC_SWITCH
unset DVB_PVR_DURATION_VALUE
unset DVB_PVR_PVR_TIMESHIFT_DEFAULT
unset DVB_SUBTITLE_LANG_VALUE
unset DVB_SUBTITLE_MODE_VALUE
unset DVB_FACTORY_FLAG_VALUE

# (新增)参数默认值。客户化方案如需配置为其他值，在对应市场env.sh中配置/修改。

# 默认不开启MTC
export DVB_CA_MTC=0

# 默认点阵字库目录
export DVB_FONT_TYPE=Arial
# 默认多语言gb2312
export DVB_LANGUAGE_TYPE=gb2312

# 默认OSD颜色
export DVB_OSD_BPP=16

# 默认不开启网络 
export DVB_NETWORK_FLAG=no

# 默认不开启迈伦斯推送数据广播 
export MBIS_CLIENT_FLAG=no

# 默认升级pid和tableid值。客户化方案如需配置为其他值，在对应市场env.sh中配置/修改。
export OTA_PID=0x1e61
export OTA_TABLEID=0x88

# 默认音量等级0～32，音量值范围0～96
# gx3201h/gx3113h指标测试版本，根据需要对应市场env.sh中 配置音量等级0~32,音量范围0~64
# 特殊市场化方案如需配置为其他值，在对应市场env.sh中配置/修改。
export AUDIO_VOLUME_LEVEV=32
export AUDIO_VOLUME_STEP=3

# 默认非高安CA
export DVB_CASCAM_FLAG=no
export DVB_CASCAM_CA_MODE=MODE_NONE

# 默认编译演示版本,编译生产/发布版本时自动将对应市场unset.sh中DVB_RELEASE_TEST修
# 改为release
export DVB_RELEASE_TEST=release

# 4:3 / 16:9配置,默认配置为4:3输出
export DVB_DISPLAY_SCREEN_MODE=DISPLAY_SCREEN_4X3

# 分辨率配置。默认配置为VIDEO_OUTPUT_HDMI_1080I_50HZ
# 标清方案，国内市场env.sh需修改为VIDEO_OUTPUT_PAL。
# 国外方案，根据市场需求修改。例如VIDEO_OUTPUT_YCBCR_1080I_60HZ/VIDEO_OUTPUT_NTSC_M等
export DVB_HDMI_MODE=VIDEO_OUTPUT_HDMI_1080P_60HZ

# 默认切换分辨率支持. yes/no, 标清方案默认不支持。
export DVB_HDMI_SWITCH_FLAG=yes

# pan-scan/letter-box模式配置，默认配置为ASPECT_NORMAL
# 根据市场需求，可配置为ASPECT_PAN_SCAN/ASPECT_LETTER_BOX等
export DVB_ASPECT_MODE=ASPECT_NORMAL

# 静帧切台,默认开启. yes/no
export DVB_PLAY_FREEZE_SWITCH=yes

# 不同节目制式变化，制式自适应，默认关闭。yes/no
export DVB_AUTO_ADAPT=no

# 默认音量
export DVB_VOLUME_VALUE=48

# 默认设置为左声道
export DVB_AUDIO_TRACK=AUDIO_TRACK_LEFT

# 默认广播节目设置为左声道（仅针对特殊市场，需设置广播节目声道需求）
export DVB_RADIO_AUDIO_TRACK=AUDIO_TRACK_LEFT

# 默认AC3_BYPASS模式
export DVB_AC3_BYPASS_MODE=AUDIO_AC3_DECODE_MODE

# 默认使用全局声道标志 yes/no
export DVB_TRACK_GLOBLE_FLAG=yes

# 默认全局音量标志 yes/no
export DVB_VOLUMN_GLOBLE_FLAG=yes

# 默认静音标志 yes/no
export DVB_MUTE_FLAG=no

# 默认菜单语言
export DVB_MENU_LANGUAGE=LANGUAGE_CHINESE

# 默认TELTEXT语言
export DVB_TELTEXT_LANGUAGE=LANGUAGE_ENGLISH

# 默认SUBTITLE语言
export DVB_SUBTITLE_LANGUAGE=LANGUAGE_ENGLISH

# 默认OSD透明度
export DVB_OSD_TRANS=10

# 默认亮度
export DVB_VIDEOCOLOR_BRIGHTNESS=50

# 默认饱和度
export DVB_VIDEOCOLOR_SATURATION=50

# 默认对比度
export  DVB_VIDEOCOLOR_CONTRAST=50

# 默认信息条超时关闭时间(s)
export DVB_BAR_TIME=2

# 默认时区
export DVB_TIMEZONE=8

# 默认密码开启标志
export DVB_PASSWORD_FLAG=yes

# 默认密码长度
export DVB_PASSWORD_LEN=4

# 默认密码
export DVB_PASSWORD="0000"

# 默认手动搜索频点/符号绿/调制方式/带宽，根据市场需求是否使用/配置
export DVB_MANUSAL_SEARCH_FRE=506000
export DVB_MANUSAL_SEARCH_SYM=6875
export DVB_MANUSAL_SEARCH_QAM=2
export DVB_MANUSAL_SEARCH_BANDWIDTH=8

# 默认连续切台遥控器超时时间(ms)
export DVB_PLAY_DURATION=300

# 默认前端监测时间(ms)
export DVB_FRONT_MONITER_DURATION=1000

# 默认序列号长度，根据市场规范配置/修改
export DVB_MAX_SEARIAL_LEN=20

# 默认dtbm/dvbc模式，仅针对双模方案有效 0--dtbm, 1--dvbc
export DVB_DTMB_DVBC_SWITCH=0

# 默认PVR录制时间
export DVB_PVR_DURATION_VALUE=0

# 默认PVR时移时间
export DVB_PVR_PVR_TIMESHIFT_DEFAULT=0

# 默认SUBTITLE语言序号
export DVB_SUBTITLE_LANG_VALUE=0

# 默认SUBTITLE模式
export DVB_SUBTITLE_MODE_VALUE=0

# 默认工厂模式
export DVB_FACTORY_FLAG_VALUE=0


