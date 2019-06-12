/**
 * @file gxservices.h
 * @author lixb
 * @brief Goxceed Service Bus�������б�
 * @defgroup services_list Goxceed Bus Services List
 */
 /*@{*/
#ifndef __GX_SERVICES_H__
#define __GX_SERVICES_H__

__BEGIN_DECLS

#include "gxbus.h"
#include "gxavdev.h"
#include "gxmsg.h"
#include "service/gxconsole.h"
#include "service/gxgui_view.h"
#include "service/gxsolution.h"
#include "service/gxhotplug.h"
#include "service/gxplayer.h"
#include "service/gxsi.h"
#include "service/gxbook.h"
#include "service/gxupdate.h"

/**CA����,����CAS������*/
extern GxServiceClass ca_service;
/**�������߿���̨����*/
extern GxServiceClass console_app_service;
/**DVB EPG����*/
extern GxServiceClass epg_service;
/**ATSC EPG����*/
extern GxServiceClass atsc_epg_service;
/**ADCANCE EPG����*/
extern GxServiceClass advance_epg_service;
/**ADVANCE SEARCH����*/
extern GxServiceClass advance_search_service;
/** blind SEARCH����*/
extern GxServiceClass blind_search_service;

/**GUI VIEW����*/
extern GxServiceClass gui_view_service;
/**USB/MMC HOT PLUG����*/
extern GxServiceClass hotplug_service;
/**HDMI HOT PLUG����*/
extern GxServiceClass hdmi_hotplug_service;
/**USBWIFI����*/
extern GxServiceClass usbwifi_hotplug_service;
/**USB3G����*/
extern GxServiceClass usb3g_hotplug_service;
/**����������*/
extern GxServiceClass player_service;
/**DVB SEARCH����*/
extern GxServiceClass search_service;
/**DVB SI����*/
extern GxServiceClass si_service;
/**DVB ��Ƶ����*/
extern GxServiceClass frontend_service;
/**ԤԼ����*/
extern GxServiceClass book_service;
extern GxServiceClass extra_service;
extern GxServiceClass solution_service;

/**Goxceed������������*/
extern GxServiceClass update_service;
extern GxServiceClass gxtest_service;

extern GxServiceClass box_service;
/* ATSC SEARCH */
extern GxServiceClass Atsc_search_service;

/* Debug */
extern GxServiceClass debug_service;
__END_DECLS

#endif
/*@}*/
