#ifndef __GX_SOLUTION_SERVICE_H__
#define __GX_SOLUTION_SERVICE_H__

#include "gxbus.h"
#include "gxtype.h"
#include "gxcore.h"
#include "gui_core/gdi_core.h"
#include "gui_core/gui_core.h"

__BEGIN_DECLS

typedef struct {
	status_t (*MsgInit)(handle_t self);
	status_t (*MsgCleanup)(handle_t self);
} GxSolutionServiceConfigPara;

status_t GxSolutionServiceConfig(GxSolutionServiceConfigPara *config);

__END_DECLS

#endif

