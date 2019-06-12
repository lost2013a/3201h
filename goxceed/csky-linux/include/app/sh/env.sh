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

# goxceed��汾·��
export GXLIB_PATH=`pwd`/../../goxceed/$CROSS_PATH
export GXSRC_PATH=`pwd`
# linux�������ں˴���·��
export GX_KERNEL_PATH=`pwd`/../linux-2.6.27.55

# ��оƬ����
export CHIP=gx3113h
# demodоƬ����
export DEMOD=atbm888x

# �ͻ�Ӳ����
# ͬһ�ͻ���ͬоƬ���������ܴ��ڶ��Ӳ����ƣ�����runde,rundeddr1,runde_ddr1_32m��
export DVB_CUSTOM=newstar
# �г�
export DVB_MARKET=dtmb

# �ͻ�Ӳ���г�:${DVB_CUSTOM}_$(DVB_MARKET)��

# ��Ӧ�ͻ�Ӳ����loader-sflash.bin��.boot ·����
# gxappcommon/flashconf/loader-sflash/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)/loader-sflash.bin

# ��Ӧ�ͻ��г���invariable_oem.ini��variable_oem.ini ·��(����ȷ��Ψһ��):
# gxappcommon/flashconf/ini/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)_$(DVB_MARKET)/invariable_oem.ini ��variable_oem.ini

# ��Ӧ�ͻ��г���flash.conf��flash_ts.conf ·����
# ����г��汾��������flash��������·��(�����г�����
# gxappcommon/flashconf/conf/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)_$(DVB_MARKET)/flash.conf��flash_ts.conf
# �г��汾flashͨ������·����
# gxappcommon/flashconf/conf/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)/flash.conf��flash_ts.conf

# ��Ӧ�ͻ��г���env.sh ·��(����ȷ��Ψһ��):
# gxappcommon/sh/$(CHIP)/$(DEMOD)/$(DVB_CUSTOM)_$(DVB_MARKET)/env.sh

# CA�г�
# ͬһCA�����ܴ��ڲ�ͬ�г��汾
# ���ͬһ�г����ܴ��ڶ�����ҡ���ͬ������Ӳ��ƽ̨��CA��Ȳ��죬����ݲ��컯����
# ��ӦCAĿ¼gxapp_common/cas/$DVB_CA_1_NAME/$DVB_CA_MARKET/; gxapp_common/cas/$DVB_CA_2_NAME/$DVB_CA_MARKET/;
export DVB_CA_MARKET=gongban
# ����г�
export DVB_AD_MARKET=gongban

# �Ƿ����CA����ֵΪno��Ϊ�����汾
export DVB_CA_FLAG=no

if [ $DVB_CA_FLAG = "yes" ]; then
	#CAö�٣���app_common_porting_stb_api.h��dvb_ca_type_t�ṹ���ж�Ӧ��
	
	export DVB_CA_TYPE=DVB_CA_TYPE_ABV38
	export DVB_CA_1_NAME=abv_cas38
	export DVB_CA_1_LIB=abvca
	export DVB_CA_1_FLAG=DVB_CA_TYPE_ABV_CAS38_FLAG
fi

#����˫CA�����������ֻ��һ��CA���ڶ���CA��������
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

# ѡ��OTAЭ��
export DVB_OTA_TYPE=DVB_NATIONALCHIP_OTA

# �����Ƿ�֧�ָ����б�����ʾ
export DVB_HD_LIST=no

# ����loader���Ƿ��ѿ���jpg logo��ʾ֧��(����gxloader�е�.config����һ��)
export DVB_JPG_LOGO=yes

# ����оƬ�Ƿ�֧��ac3����
export AUDIO_DOLBY=no

# �����Ƿ���PVR���ܣ�¼�ơ�ʱ�Ƶȣ�
export DVB_PVR_FLAG=yes

# �����Ƿ���subtitle��Ļ��ʾ����
export DVB_SUBTITLE_FLAG=no

# �����Ƿ������繦�ܣ�youtube�ȣ� (��linux����֧�ִ˹���)
export DVB_NETWORK_FLAG=yes

# ����֧��OTT����

# �Ƿ�֧��USB����
export DVB_USB_FLAG=yes

# �Ƿ�֧��PVR���������
export DVB_PVR_SPEED_SUPPORT=0

# ѡ��ǰ������� panel_xxx(�г�)_xxx(����)_xxx(�������)����PANEL_TYPE_fd650_RUNDE
# ��֧�����ο���include/bsp/panel_enum.h
export DVB_PANEL_TYPE=PANEL_TYPE_fd650_RUNDE
export PANEL_CLK_GPIO=33
export PANEL_DATA_GPIO=33
export PANEL_STANDBY_GPIO=199
export PANEL_LOCK_GPIO=33

# ѡ��ң�����궨������ keymap_xxx(�г�)_(����)����KEY_GONGBAN_NATIONALCHIP_NEW
# ��֧�����ο�:key_xmlĿ¼�µ�.xml group="KEY_GONGBAN_NATIONALCHIP_NEW"�ȣ�ע��ͬһ��kex(x).xml���ܳ���ң�������������������ң�������벻��ͬkey(x).xml�ж��壩
export DVB_KEY_TYPE=KEY_XINSIDA

# ���оƬ���� ���ο�demod_enum.h����
export DVB_DEMOD_TYPE=DVB_DEMOD_ATBM888X

# ���ģʽ���ο�demod_enum.h���壨Ŀǰ��֧��DVB_DEMOD_DVBS��
export DVB_DEMOD_MODE=DVB_DEMOD_DTMB

# ����ѡ�õڼ�·ts��� : ��ѡ0,1,2��
export DVB_TS_SRC=1

# ����tuner���ͣ��ο�demod/include/tuner_neum.h����
export DVB_TUNER_TYPE=TUNER_MXL608

# ѡ�񿪻�����jpgͼƬ��logo-jpg/Ŀ¼��Ϊ������jpg
export DVB_LOGO_JPG=logo_nationalchip_gongban.jpg
# ����theme��Դ�����ߡ����桢���塢����ȣ����ο�development/theme�¶�ӦĿ¼
export DVB_THEME=DTMB_MINI_HD
if [ "$1" = "csky-linux" ] ; then
# XML��ͼƬ��·��
export DVB_WORK_PATH='"/dvb/"'
# �㲥����ͼƬ·��
export DVB_LOGO_PATH='"/dvb/theme/logo.bin"'
export DVB_I_FRAME_PATH='"/dvb/theme/logo.bin"'
fi

if [ "$1" = "csky-ecos" ] ; then
# �㲥����ͼƬ·��
export DVB_LOGO_PATH='"/theme/logo.bin"'
export DVB_I_FRAME_PATH='"/theme/logo.bin"'
export DVB_NETWORK_FLAG=no
fi


# �궨�������
# ����Ƶͬ����ʽ 0-PCR_RECOVER 1-VPTS_RECOVER 2-APTS_RECOVER 3-AVPTS_RECOVER 4-NO_RECOVER
export DVB_SYS_MODE=0
# ȫ����ƵXλ��
export DVB_VIDEO_X=0
# ȫ����ƵYλ��
export DVB_VIDEO_Y=0
# ȫ����Ƶ���С
export DVB_VIDEO_W=1024
# ȫ����Ƶ�ߴ�С
export DVB_VIDEO_H=576
# ���������������ߡ����淽������Ϊ1��
export DVB_SAT_MAX=1
# TPƵ��������
export DVB_TP_MAX=100
# ��Ŀ������
export DVB_SERVICE_MAX=200
# DDRAM ����
export DVB_DDRAM_TYPE=ddr3
# DDRAM ��С
export DVB_DDRAM_SIZE=128
# FLASH ��С
export DVB_FLASH_SIZE=8
# ����PAT��ʱʱ�䣨ms��
export DVB_PAT_TIMEOUT=3000
# ����SDT��ʱʱ�䣨ms��
export DVB_SDT_TIMEOUT=5000
# ����NIT��ʱʱ�䣨ms��
export DVB_NIT_TIMEOUT=10000
# ����PMT��ʱʱ�䣨ms��
export DVB_PMT_TIMEOUT=8000
# LCN����ģʽ�£��Ǳ��������߼�Ƶ���ŵĽ�Ŀ��Ĭ����ʼ�߼�Ƶ����
export DVB_LCN_DEFAULT=500
# ��Ƶ�����
export DVB_CENTER_FRE=714
export DVB_CENTER_SYMRATE=6875
export DVB_CENTER_QAM=2
# ����
export DVB_CENTER_BANDWIDTH=8
# �Ƿ�֧��dvbc-dtmb˫ģ
export DVB_DUAL_MODE=no
# �Ƿ�����ȫ����Ŀ
export DVB_PROGRAM_TYPE=PROGRAM_TYPE_FTA
# Ӳ���Զ����Կ��ء�yes- �����Զ����Թ��� no -�ر��Զ����Թ���
export DVB_AUTO_TEST_FLAG=no
# �Ƿ�֧�ֶ�ý�幦��
export DVB_MEDIA_FLAG=yes
# ��Ƶ�����Ƿ����²���
export DVB_ZOOM_RESTART_PLAY=no
export DVB_BAD_SIGNAL_SHOW_LOGO=yes

# ����ģʽ
# �Ƿ�����߼�Ƶ���Ź淶��yes- �����߼�Ƶ���Ź淶 no- ���߼�Ƶ���Ź淶
# ע�⣺�������LCN_DV��DVB_TAXIS_MODE����ΪTAXIS_MODE_NON����ͬʱֻ����һ����
# ��ʽ
export LCN_DV=no
# ����ʽ���ο� csky-ecos/include/bus/module/pm/gxpm_manage.h
# 0- TAXIS_MODE_NON 1- TAXIS_MODE_CAS 2- TAXIS_MODE_LETTER 3- TAXIS_MODE_TP
# 4- TAXIS_MODE_TUNER 5- TAXIS_MODE_SCRAMBLE 6- TAXIS_MODE_SERVICE_ID 
# 7- TAXIS_MODE_USER
export DVB_TAXIS_MODE=0
# ũ�����������淶�г�����Ŀservice_id�ظ����������߼�Ƶ���Ź淶
# Ҫ��������Ŀ����pat���е�˳���������
# yes- ��pat������ no- ����pat������
# ע�⣺�������SORT_PROG_BY_PAT_DV��DVB_TAXIS_MODE����ΪTAXIS_MODE_NON
# ��ͬʱֻ����һ������ʽ��
export SORT_PROG_BY_PAT_DV=yes
# �Ƿ�ʹ��˽�����ݹ���yes- ʹ��˽�й��� no- ��ʹ��˽�й���
export USER_LIST_DV=no

#
# Ӳ������gpio���� 
# ����gpio�ܽ� 
export MUTE_GPIO_VALUE=31
# ����Ϊ������gpio����/����(ȡ�������෴����)�� 1-- ���� 0--����
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






 




