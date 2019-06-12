#ifndef __GX_HDMI__MODULE_H__
#define __GX_HDMI__MODULE_H__

#include "gxcore.h"
#include "av/avapi.h"

__BEGIN_DECLS

#define HDMI_CONFIG_VOUT_HDCP_ON         "Hdmi>vout_hdcp_on"
#define HDMI_CONFIG_VOUT_HDCP_MODE       "Hdmi>vout_hdcp_mode"

extern status_t GxHdmi_SetHdcpEnable(int enable);

__END_DECLS

#endif
