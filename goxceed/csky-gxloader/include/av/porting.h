#ifndef __GX_PORTING_H__
#define __GX_PORTING_H__

#include "config.h"
#include "gxav.h"
#include "video.h"

#ifndef CONFIG_AV_VIDEO_DEC
extern int gx_video_disp_patch(int id);
extern int gx_video_close(int id);
extern int gx_video_zoom_require(int id);
extern int gx_video_pp_zoom(int id);
extern int gx_video_ppopen_require( int id );
extern int gx_video_frame_rate_transform_require(int id);
extern int h_vd_get_disp_zoom_mode(void);
extern void gx_video_init_switchxy(int id, unsigned int switchx, unsigned int switchy);
extern void video_sync_strict_enable(struct video_sync *sync, unsigned int enable);;
extern int gx_video_ppclose_require( int id );
extern unsigned int video_sync_get_frame_dis(struct video_sync *sync);
extern int gx_video_cap_frame(int id, struct cap_frame *frame);
extern int videodisp_get_showing_frame(struct gxav_video_module *module, struct cap_frame *frame);
#endif


#endif
