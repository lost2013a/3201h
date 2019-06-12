#ifndef GXAV_MODULE_PROPETYTYPES_H
#define GXAV_MODULE_PROPETYTYPES_H

#include "gxav_sdc_propertytypes.h"
#include "gxav_vpu_propertytypes.h"
#include "gxav_audiodec_propertytypes.h"
#include "gxav_audioout_propertytypes.h"
#include "gxav_video_propertytypes.h"
#include "gxav_jpeg_propertytypes.h"
#include "gxav_demux_propertytypes.h"
#include "gxav_vout_propertytypes.h"
#include "gxav_stc_propertytypes.h"
#include "gxav_icam_propertytypes.h"
#include "gxav_iemm_propertytypes.h"

struct fifo_info {
	unsigned int         pin_id;
	void                 *channel;
	enum gxav_direction  dir;
};

typedef int                 GxAVGenericProperty_ClearEventMask;
typedef struct channel_info GxAVGenericProperty_ModuleLinkChannel;
typedef struct channel_info GxAVGenericProperty_ModuleUnLinkChannel;

#endif
