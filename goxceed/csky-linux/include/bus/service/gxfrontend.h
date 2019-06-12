
#ifndef __GX_FRONTEND_H__
#define  __GX_FRONTEND_H__

#include <gxbus.h>

#ifndef I386_LINUX

#include "../module/frontend/gxfrontend_module.h"

typedef GxFrontend GxMsgProperty_FrontendSetTp;

typedef int GxMsgProperty_FrontendMonitor;

typedef int GxMsgProperty_FrontendLocked;

typedef int GxMsgProperty_FrontendUnlocked;

typedef GxFrontendDiseqc GxMsgProperty_FrontendSetDiseqc;

#endif

#endif

