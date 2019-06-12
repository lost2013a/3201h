#ifndef __APP_MSG_ENUM_H__
#define __APP_MSG_ENUM_H__
#include "gxservices.h"
#include "gxapp_sys_config.h"
#if defined (DVB_OTT_TYPE)&& (OTT_VOOLE_CIBN == DVB_OTT_TYPE)
#include "app_cibn_service.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
#if defined (DVB_OTT_TYPE)&& (OTT_VOOLE_CIBN == DVB_OTT_TYPE)
	GXMSG_APP_INIT = GXMSG_CIBN_END,
#else
	GXMSG_APP_INIT = GXMSG_TOTAL_NUM,
#endif
    GXMSG_SUBTITLE_INIT = GXMSG_APP_INIT,
    GXMSG_SUBTITLE_DESTROY,
    GXMSG_SUBTITLE_HIDE,
    GXMSG_SUBTITLE_SHOW,
    GXMSG_SUBTITLE_DRAW,
    GXMSG_SUBTITLE_CLEAR,
#if DVB_CASCAM_FLAG 
	GXMSG_CASCAM_EVENT,
#endif
    GXMAX_MSG_NUM
}gxmsg_type_t;


#ifdef __cplusplus
}
#endif

#endif /* __APP_MSG_ENUM_H__ */

