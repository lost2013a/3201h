#ifndef __GX_BUS_AVDEV_H__
#define __GX_BUS_AVDEV_H__

#include <av/gxav.h>
#include <av/gxav_icam_propertytypes.h>
#include <gxcore.h>
#include <devapi/gxmtc_api.h>

__BEGIN_DECLS

extern int GxAvdev_CreateDevice(int pid) ;
extern int GxAvdev_DestroyDevice(int dev_id) ;
extern int GxAvdev_OpenFirmware(const char* file) ;
extern int GxAvdev_CloseFirmware(int firmware) ;
extern int GxAvdev_OpenModule(int dev, int type, int id) ;
extern int GxAvdev_CloseModule(int dev, int module) ;
extern int GxAvdev_CloseLogo(void);
extern int GxAvdev_AllocDemux(int tsid);
extern int GxAvdev_FreeDemux(int dmxid);
extern int GxAvdev_SppDBGLock(const char *file, int line, const char *function);
extern int GxAvdev_SppDBGUnlock(const char *file, int line, const char *function);

#define GxAvdev_SppLock(x) GxAvdev_SppDBGLock(__FILE__, __LINE__, __FUNCTION__)

#define GxAvdev_SppUnlock(x) GxAvdev_SppDBGUnlock(__FILE__, __LINE__, __FUNCTION__)

int GxAvdev_SetI2cAckWaitTime(unsigned int delay);

int   GxAvdev_LayerEnable         (int dev, int vpu, int layer, int flag);
int   GxAvdev_GetLayerEnable      (int dev, int vpu, int layer);
int   GxAvdev_SetLayerMainSurface (int dev, int vpu, int layer, void *surface);
int   GxAvdev_UnSetLayerMainSurface (int dev, int vpu, int layer, void *surface);
void *GxAvdev_GetLayerMainSurface (int dev, int vpu, int layer);
int   GxAvdev_SetLayerTop         (int dev, int vpu, int layer, int flag);
int   GxAvdev_SetLayerViewport    (int dev, int vpu, int layer, GxAvRect* rect);
int   GxAvdev_SetLayerClipport    (int dev, int vpu, int layer, GxAvRect* rect);
int   GxAvdev_SetLayerAntiFlicker (int dev, int vpu, int layer, int flag);
int   GxAvdev_SetSurfaceAlpha     (int dev, int vpu, void *surface, GxAlpha *alpha);
int   GxAvdev_SetVirtualResolution(int dev, int vpu, int width, int height);

unsigned int GxAvdev_GetKernelVersion(void);
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))


#define NDS_KEY_MAX_CW (128)
typedef struct {
	GxIcamProperty_ControlWord cw[NDS_KEY_MAX_CW];
	int nb_cw;
}NDSKeyCW;

int GxAvdev_NDSCWGen(NDSKeyCW* cw);
int GxAvdev_NDSKeyGen(NDSKeyCW* cw);

__END_DECLS

#endif
