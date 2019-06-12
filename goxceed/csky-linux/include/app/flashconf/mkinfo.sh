#!/bin/bash
cd $GXSRC_PATH/flash
echo 软件信息：					>readme.txt
echo							>>readme.txt
echo 厂家信息：					$DVB_CUSTOM>> readme.txt
echo 市场信息：					$DVB_MARKET>>readme.txt
echo                            >>readme.txt
if [ -z "$DVB_CHIP_MARK" ] ; then
echo 解码芯片：					$CHIP>>readme.txt
else
echo 解码芯片：                 $DVB_CHIP_MARK>>readme.txt
fi
echo 解调芯片：					$DEMOD>>readme.txt
echo TUNE型号:					$DVB_TUNER_TYPE>>readme.txt
echo 面板类型：					$DVB_PANEL_TYPE>>readme.txt
echo 红外类型：					$DVB_KEY_TYPE>>readme.txt
echo 内存信息：					$DVB_DDRAM_TYPE / $DVB_DDRAM_SIZE m>>readme.txt
echo 闪存大小：					$DVB_FLASH_SIZE m>>readme.txt
echo							>>readme.txt
echo 驱动版本：                 $(grep -R "GOXCEED_VERSON" $GXLIB_PATH/include/gxcore_version.h|awk '{print $3}')>>readme.txt
echo 操作系统：					$OS>>readme.txt
echo 硬件版本：                 $(awk -F '=' '/\['system'\]/{a=1}a==1&&$1~/'hardware_version'/{print $2;exit}' $GXSRC_PATH/flash/variable_oem.ini)>>readme.txt
echo 软件版本：                 $(awk -F '=' '/\['software'\]/{a=1}a==1&&$1~/'application_version'/{print $2;exit}' $GXSRC_PATH/flash/variable_oem.ini)>>readme.txt
if [ -f $GXSRC_PATH/../../.repo/manifests.git/config ]; then
echo 分支信息：                 $(grep -R "merge" $GXSRC_PATH/../../.repo/manifests.git/config|awk '{print $3}')>>readme.txt
fi
if [ -f $GXSRC_PATH/../.git/HEAD ]; then
echo GIT 信息：                 $(git rev-list HEAD -n 1 | cut -c 1-10)>>readme.txt
fi
if [ $DVB_RELEASE_TEST = release ] ; then
echo 软件类型：					发布软件>>readme.txt
else
echo 软件类型：                 测试软件,仅用于测试使用>>readme.txt
fi
echo 发布时间：					$(date +%Y/%m/%d_%H:%M)>>readme.txt
echo 发布作者:					$(who | awk '{w[$1]+=1} END{for(a in w) if(w[a]>1) print a}')>>readme.txt
echo							>>readme.txt
if [ $DVB_CA_FLAG = yes ]; then
echo CA  类型：                 $DVB_CA_1_NAME>>readme.txt
fi
if [ -z "$DVB_AD_NAME" ] ; then
echo                            >>readme.txt
else
echo 广告类型：                 $DVB_AD_NAME>>readme.txt
fi
if [ $MBIS_CLIENT_FLAG = yes ]; then
echo 广告推送：                 mbis_client>>readme.txt
fi
echo							>>readme.txt
echo 主频  点：                 $DVB_CENTER_FRE m>>readme.txt
if [ $DVB_LANGUAGE_TYPE = utf-8 ]; then
echo 字库类型：                 矢量字库>>readme.txt
elif [ $DVB_LANGUAGE_TYPE = gb2312 ]; then
echo 字库类型：                 点阵字库>>readme.txt
fi
echo OSD 位数：                 $DVB_OSD_BPP 位>>readme.txt
if [ $DVB_SYS_MODE = 0 ]; then
echo 同步模式：                 PCR同步>>readme.txt
elif [ $DVB_SYS_MODE = 2 ]; then
echo 同步模式：                 ATPS同步>>readme.txt
fi
if [ $LCN_DV = yes ]; then
echo LCN 开关：                 开>>readme.txt
else
echo LCN 开关：                 关>>readme.txt
fi
if [ $SORT_PROG_BY_PAT_DV = yes ]; then
echo 排序方式：					pat表节目顺序排序>>readme.txt
else
if [ $DVB_TAXIS_MODE = 0 ]; then
echo 排序方式：                 默认/逻辑频道号排序>>readme.txt
elif [ $DVB_TAXIS_MODE = 6 ]; then
echo 排序方式：                 service id排序>>readme.txt
fi
fi

if [ $DVB_OTA_TYPE = DVB_NATIONALCHIP_OTA ]; then
echo OTA 协议：                 OTA公版协议>>readme.txt
echo 升级 pid：                 $OTA_PID>>readme.txt
echo 升级表id:                  $OTA_TABLEID>>readme.txt
else
echo OTA 协议：					$DVB_OTA_TYPE>>readme.txt
fi
echo                            >>readme.txt
if [ $DVB_CA_MTC = 1 ]; then
echo MTC 高安：                 开>>readme.txt
fi
if [ $DVB_CASCAM_FLAG = 1 ]; then
echo 高安  CA：                 $DVB_CASCAM_CA_MODE>>readme.txt
fi
if [ -z "$DVB_OTT_NAME" ] ; then
echo 
else
echo OTT 类型：                 $DVB_OTT_NAME / $DVB_OTT_SERVER>>readme.txt
echo WIFI型号：                 $DVB_USB_WIFI>>readme.txt
fi
if [ $DVB_MEDIA_FLAG = yes ]; then
echo 媒体播放：                 支持>>readme.txt
fi

if [ $DVB_PVR_FLAG = yes ]; then
echo PVR 支持：                 支持>>readme.txt
fi

if [ $DVB_DUAL_MODE = yes ]; then
echo 双模支持：                 支持>>readme.txt
fi

mv readme.txt readme_ubuntu.txt
iconv -f utf8 -t gbk readme_ubuntu.txt > readme.txt
cd -
