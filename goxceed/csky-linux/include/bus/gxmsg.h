#ifndef __GX_MSG_H__
#define __GX_MSG_H__

/**服务总线支持最大消息数量*/
#define GXMSG_MAX_NUM_SUPPORT               (300)

/**预定义消息*/
typedef enum {
	GXMSG_PLAYER_PLAY,
	GXMSG_PLAYER_STOP,
	GXMSG_PLAYER_PAUSE,
	GXMSG_PLAYER_RESUME,
	GXMSG_PLAYER_SEEK,
	GXMSG_PLAYER_SPEED,
	GXMSG_PLAYER_RECORD,
	GXMSG_PLAYER_VIDEO_COLOR,
	GXMSG_PLAYER_VIDEO_CLIP,
	GXMSG_PLAYER_VIDEO_WINDOW,
	GXMSG_PLAYER_VIDEO_ASPECT,
	GXMSG_PLAYER_VIDEO_INTERFACE,
	GXMSG_PLAYER_VIDEO_MODE_CONFIG,
	GXMSG_PLAYER_VIDEO_OUTPUT_DEF,
	GXMSG_PLAYER_VIDEO_OUTPUT_POWER,
	GXMSG_PLAYER_VIDEO_AUTO_ADAPT,
	GXMSG_PLAYER_VIDEO_HIDE,
	GXMSG_PLAYER_VIDEO_SHOW,
	GXMSG_PLAYER_VIDEO_MOSAIC_DROP,
	GXMSG_PLAYER_VIDEO_USERDATA_CONFIG,
	GXMSG_PLAYER_AUDIO_DOWNMIX,
	GXMSG_PLAYER_AUDIO_SYNC,
	GXMSG_PLAYER_AUDIO_MUTE,
	GXMSG_PLAYER_AUDIO_VOLUME,
	GXMSG_PLAYER_AUDIO_TRACK,
	GXMSG_PLAYER_AUDIO_DESCRIPTOR_TRACK,
	GXMSG_PLAYER_AUDIO_SWITCH,
	GXMSG_PLAYER_AUDIO_INTERFACE,
	GXMSG_PLAYER_AUDIO_MODE_CONFIG,
	GXMSG_PLAYER_AUDIO_AC3_MODE,
	GXMSG_PLAYER_SUBTITLE_SYNC,
	GXMSG_PLAYER_SUBTITLE_LOAD,
	GXMSG_PLAYER_SUBTITLE_UNLOAD,
	GXMSG_PLAYER_SUBTITLE_SWITCH,
	GXMSG_PLAYER_SUBTITLE_HIDE,
	GXMSG_PLAYER_SUBTITLE_SHOW,
	GXMSG_PLAYER_SUBTITLE_RESOLUTION,
	GXMSG_PLAYER_PLAY_CONFIG,
	GXMSG_PLAYER_DELAY_CONFIG,
	GXMSG_PLAYER_PVR_CONFIG,
	GXMSG_PLAYER_RECORD_CONFIG,
	GXMSG_PLAYER_DISPLAY_SCREEN,
	GXMSG_PLAYER_TIME_SHIFT,
	GXMSG_PLAYER_MULTISCREEN_PLAY,
	GXMSG_PLAYER_FREEZE_FRAME_SWITCH,
	GXMSG_PLAYER_STATUS_REPORT,
	GXMSG_PLAYER_AVCODEC_REPORT,
	GXMSG_PLAYER_SPEED_REPORT,
	GXMSG_PLAYER_RESOLUTION_REPORT,
	GXMSG_PLAYER_RECORD_OVERFLOW,
	GXMSG_PLAYER_PROCESS_FINISH,
	GXMSG_PLAYER_TRACK_ADD,
	GXMSG_PLAYER_TRACK_DEL,
	GXMSG_PLAYER_BANDWIDTH_SWITCH,
	GXMSG_PLAYER_AD_AUDIO_ENABLE,
	GXMSG_PLAYER_AD_AUDIO_DISABLE,
	GXMSG_FRONTEND_STOP_MONITOR,
	GXMSG_FRONTEND_START_MONITOR,
	GXMSG_FRONTEND_SET_TP,
	GXMSG_FRONTEND_SET_DISEQC,
	GXMSG_FRONTEND_LOCKED,
	GXMSG_FRONTEND_UNLOCKED,
	GXMSG_SI_SUBTABLE_GET,
	GXMSG_SI_SUBTABLE_CREATE,
	GXMSG_SI_SUBTABLE_MODIFY,
	GXMSG_SI_SUBTABLE_RELEASE,
	GXMSG_SI_SUBTABLE_START,
	GXMSG_SI_SUBTABLE_STOP,
	GXMSG_SI_SECTION_OK_FOR_TEST,
	GXMSG_SI_SECTION_OK,
	GXMSG_SI_SUBTABLE_OK,
	GXMSG_SI_SUBTABLE_TIME_OUT,
	GXMSG_SI_SUBTABLE_RELEASE_OK,
	GXMSG_EPG_NUM_GET,
	GXMSG_EPG_GET,
	GXMSG_EPG_NVOD_GET,
	GXMSG_EPG_CREATE,
	GXMSG_EPG_CLEAN,
	GXMSG_EPG_RELEASE,
	GXMSG_EPG_PARENTAL_GET,
	GXMSG_EPG_PARENTAL_SEND,
	GXMSG_EPG_GET_LOCK,
	GXMSG_EPG_GET_UNLOCK,
	GXMSG_EPG_FILTER_NUM_GET,/* 携带的参数为uint32_t* */
	GXMSG_EPG_FILTER_INFO_GET,/* 携带的参数为GxMsgProperty_EpgFilterInfo* */
	GXMSG_EPG_FILTER_MODIFY,/* 携带的参数为GxMsgProperty_EpgFilterModify* */
	GXMSG_EPG_FULL,
	GXMSG_EPG_EXIST,
	GXMSG_EPG_TIMEOUT,
	GXMSG_EPG_FULL_SPEED,
	GXMSG_BOOK_TRIGGER,
	GXMSG_BOOK_FINISH,
	GXMSG_BOOK_GET,
	GXMSG_BOOK_CREATE,
	GXMSG_BOOK_MODIFY,
	GXMSG_BOOK_DESTROY,
	GXMSG_BOOK_START,
	GXMSG_BOOK_STOP,
	GXMSG_BOOK_RESET,
	//ca v1.0.2
	GXMSG_CA_REGISTER_CAS,              /**<CAS 注册消息,携带参数GxMsgProperty_RegisterCas*/
	GXMSG_CA_UNREGISTER_CAS,            /**<CAS 去注册消息,携带参数GxMsgProperty_UnregisterCas*/
	GXMSG_CA_ON_EVENT,                  /**<CAS UI菜单事件响应消息,携带参数GxMsgProperty_OnEvent*/
	GXMSG_CA_ON_IOCTRL,                 /**<CAS 控制扩展,携带参数GxMsgProperty_OnIoctrl*/

	/*以下3个消息用于最新到GxCas,与前面几个无关 */
	GXMSG_CA_LINK_EVENT,            /**<链接需要接收消息到CA，用打开到CA句柄链接*/
	GXMSG_CA_UNLINK_EVENT,          /**<把不许要接收消息到CA去链接 */
	GXMSG_CA_DESCRAMBLE_ADDPID,
	GXMSG_CA_DESCRAMBLE_DELPID,
	GXMSG_CA_EVENT,                 /**<GUI接收此消息并处理，参数为消息文本到指针，使用完需要主动释放 */

	GXMSG_SEARCH_BACKUP,
	GXMSG_SEARCH_SCAN_SAT_START,
	GXMSG_SEARCH_SCAN_CABLE_START,
	GXMSG_SEARCH_SCAN_T_START,
	GXMSG_SEARCH_SCAN_DTMB_START,
	GXMSG_SEARCH_SCAN_DVBT2_START,
	GXMSG_SEARCH_SCAN_STOP,
	GXMSG_SEARCH_SAVE,
	GXMSG_SEARCH_STOP_OK,//
	GXMSG_SEARCH_NOT_SAVE,
	GXMSG_SEARCH_NEW_PROG_GET,          //注册的人请注意 这是普通消息
	GXMSG_SEARCH_STATUS_REPLY,          //注册得人请注意 这是普通消息
	GXMSG_SEARCH_SAT_TP_REPLY,                  //注册得人请注意 这是普通消息
	GXMSG_SEARCH_BLIND_SCAN_START,
	GXMSG_SEARCH_BLIND_SCAN_STOP,
	GXMSG_SEARCH_BLIND_SCAN_FINISH,
	GXMSG_SEARCH_BLIND_SCAN_REPLY,
	GXMSG_CONSOLE_HELP,
	GXMSG_CONSOLE_SEARCH,
	GXMSG_CONSOLE_EPG,
	GXMSG_CONSOLE_LOCK_TS,
	GXMSG_CONSOLE_PLAY,

	GXMSG_GUI_WARNING,
	GXMSG_GUI_RETURN_MESSAGE,

	// extra服务提供的服务:时间同步...
	GXMSG_EXTRA_SYNC_TIME,
	GXMSG_EXTRA_SYNC_TIME_OK,
	GXMSG_EXTRA_RELEASE,        ///< 释放extra服务所占用的资源

	GXMSG_UPDATE_OPEN,                  /**<GxMsgProperty_UpdateOpen*/
	GXMSG_UPDATE_START,
	GXMSG_UPDATE_STOP,
	GXMSG_UPDATE_STATUS,
	GXMSG_UPDATE_PROTOCOL_SELECT,     /**<GxMsgProperty_UpdateProtocolSelected*/
	GXMSG_UPDATE_PROTOCOL_CTRL,         /**<GxMsgProperty_UpdateProtocolCtrl*/
	GXMSG_UPDATE_PARTITION_SELECT,
	GXMSG_UPDATE_PARTITION_CTRL,

	GXMSG_HOTPLUG_IN,
	GXMSG_HOTPLUG_OUT,
	GXMSG_HOTPLUG_CLEAN,

	GXMSG_HDMI_HDCP_ENABLE,
	GXMSG_HDMI_HOTPLUG_IN,
	GXMSG_HDMI_HOTPLUG_OUT,
	GXMSG_HDMI_HDCP_FAIL,
	GXMSG_HDMI_HDCP_SUCCESS,

	GXMSG_USBWIFI_HOTPLUG_IN,
	GXMSG_USBWIFI_HOTPLUG_OUT,

	GXMSG_USB3G_HOTPLUG_IN,
	GXMSG_USB3G_HOTPLUG_OUT,

	GXMSG_BOX_RECORD_CONTROL,
	GXMSG_BOX_ENABLE,
	GXMSG_BOX_DISABLE,
	GXMSG_BOX_SET_DISEQC,
	//ATSC-EPG
	GXMSG_ATSC_EPG_GET,
	GXMSG_ATSC_EPG_FREE,
	GXMSG_ATSC_EPG_CREATE,
	GXMSG_ATSC_EPG_CLEAN,
	GXMSG_ATSC_EPG_RELEASE,
	GXMSG_ATSC_EPG_END,
	GXMSG_ATSC_EPG_BEGIN,

	GXMSG_EPG_BEGIN,
	GXMSG_EPG_END,
	GXMSG_EPG_FREE,
	//ATSC_SEARCH
	GXMSG_SEARCH_DVB_SAT_SCAN_START,
	GXMSG_SEARCH_ATSC_T_SCAN_START,
	GXMSG_SEARCH_ATSC_C_SCAN_START,
	//GXMSG_SEARCH_SAT_TP_PROCESS_REPLY,
	GXMSG_SEARCH_CONTINUE,

	//SI Table Console
	GXMSG_SI_CONSOLE_CONFIG,
	GXMSG_SI_CONSOLE_START,
	GXMSG_SI_CONSOLE_STOP,
	GXMSG_SI_CONSOLE_CHANGE,

	GXMSG_USER1,
	GXMSG_USER2,
	GXMSG_USER3,
	GXMSG_USER4,
	GXMSG_USER5,
	GXMSG_USER6,
	GXMSG_USER7,
	GXMSG_USER8,
	GXMSG_USER9,
	GXMSG_USER10,
	GXMSG_TOTAL_NUM
}GxMsgID_List;

#endif

