#ifndef GXBOX_H
#define GXBOX_H

#include <gxcore.h>

__BEGIN_DECLS

// DTV Function ------------------------------------------------------------

// Features

typedef enum
{
	GXBOX_FEATURE_CAST,			// cast with HTTP 1.1
	GXBOX_FEATURE_MULTICAST,	// cast with Mutlicast UDP
	GXBOX_FEATURE_SENDKEY,		// sendkey
	GXBOX_FEATURE_PLAY,			// play a program
	GXBOX_FEATURE_ALL
}GxBoxFeature;

status_t GxBox_SetFeatureEnable(GxBoxFeature eFeature, unsigned int bEnable);
unsigned int GxBox_GetFeatureEnable(GxBoxFeature eFeature);

// Properities

#define GXBOX_PROPERITY_MODEL			"boxModel"
#define GXBOX_PROPERITY_HW_VERSION		"boxHwVersion"
#define GXBOX_PROPERITY_SW_VERSION		"boxSwVersion"
#define GXBOX_PROPERITY_CHIPSET			"boxChipset"
#define GXBOX_PROPERITY_BOX_ID			"boxID"
#define GXBOX_PROPERITY_NAME			"boxName"
#define GXBOX_PROPERITY_FRONTEND_NUM	"boxFrontendNum"
#define GXBOX_PROPERITY_FRIENDLY_NAME	"boxFriendlyName"

status_t GxBox_SetProperityString(const char *pszKey, const char *pszValue);
status_t GxBox_SetProperityInteger(const char *pszKey, const int nValue);

const char *GxBox_GetProperityString(const char *pszKey);
int GxBox_GetProperityInteger(const char *pszKey, const int nDefault);

// Playing State

typedef struct
{
	int32_t nProgramID;
	int32_t nTransportID;
}GxBoxPlayingProgram;

void GxBox_SetPlayingProgram(GxBoxPlayingProgram *pPlayingProgram);

// Program DB
void GxBox_UpdateClientProgram();

// DTV Callback
typedef struct
{	// all % is based on 1, (no 100)
	float fSignalStrength;
	float fQualitySNR;
	float fQualityErrorRate;
	int bSyncLocked;
}GxBoxFrontendState;

// Callbacks Definition
// Query Status
typedef status_t(*GxBoxDTVQueryFronendStateRequestCallback)(const int nFrontendID, GxBoxFrontendState *pState);
// Notification
typedef status_t(*GxBoxDTVTransportChangedNotificationCallback)(const int nTransport, const int nProgramID);
typedef status_t(*GxBoxDTVPlayProgramRequestCallback)(const int nProgramID);
// Hooks
typedef status_t(*GxBoxDTVPrepareCastProgramRequestCallback)(const int nProgramID);
typedef status_t(*GxBoxDTVFinishCastProgramRequestCallback)(const int nProgramID);

typedef struct
{
	GxBoxDTVQueryFronendStateRequestCallback 		cbQueryFronendStateRequestCallback;
	GxBoxDTVTransportChangedNotificationCallback 	cbTransportChangedNotificationCallback;
	GxBoxDTVPlayProgramRequestCallback 				cbPlayProgramRequestCallback;
	
	GxBoxDTVPrepareCastProgramRequestCallback		cbPrepareCastProgramRequestCallback;
	GxBoxDTVFinishCastProgramRequestCallback		cbFinishCastProgramRequestCallback;
}GxBoxDTVCallbacks;
status_t GxBox_SetDTVCallbacks(GxBoxDTVCallbacks *pCallbackSet);

//status_t GxBox_SendEvent();


/* ---------------------------   DMR Function ------------------------------ */
typedef struct
{
	const char *pszDcTitle;		// <dc:title>
	const char *pszDcCreator;	// <dc:creator>
	const char *pszDcDescription;	// <dc:description>
	const char *pszUpnpClass;	// <upnp:class>
	const char *pszUpnpAlbum;	// <upnp:album>
	const char *pszUpnpArtist;	// <upnp:artist>
	const char *pszUpnpGenre;	// <upnp:genre>
	const char *pszUpnpAlbumArtURI;	// <upnp:albumArtURI>
	const char *pszRes0;
	const char *pszRes0ProtocolInfo;
	const char *pszRes1;
	const char *pszRes1ProtocolInfo;
}GxBoxDMRURIMetaData;

// DMR AVTransport Callback (predefined)
typedef status_t(*GxBoxDMRPrepareCallback)(const char *pszURI,
											GxBoxDMRURIMetaData *pURIMetaData);			// R
typedef status_t(*GxBoxDMRGetPositionInfoCallback)(uint64_t *plCurrentMs,
											uint64_t *plTotalMs);						// R
typedef status_t(*GxBoxDMRStopCallback)();											// R
typedef status_t(*GxBoxDMRPlayCallback)();											// R
typedef status_t(*GxBoxDMRPauseCallback)();											// O
typedef status_t(*GxBoxDMRResumeCallback)();
typedef status_t(*GxBoxDMRSeekCallback)(uint64_t nMillisecond);						// R
typedef status_t(*GxBoxDMRSetPlayModeCallback)();									// O

// DMR RenderingControl Callback (predefined)
typedef int(*GxBoxDMRGetVolumeCallback)();
typedef status_t(*GxBoxDMRSetVolumeCallback)(const int nVolume);

typedef struct
{
	GxBoxDMRPrepareCallback				cbPrepareCallback;
	GxBoxDMRStopCallback				cbStopCallback;
	GxBoxDMRPlayCallback				cbPlayCallback;
	GxBoxDMRPauseCallback				cbPauseCallback;
	GxBoxDMRResumeCallback				cbResumeCallback;
	GxBoxDMRSeekCallback				cbSeekCallback;
	GxBoxDMRGetPositionInfoCallback		cbGetPositionInfoCallback;
	GxBoxDMRGetVolumeCallback 			cbGetVolumeCallback;
	GxBoxDMRSetVolumeCallback 			cbSetVolumeCallback;
}GxBoxDMRCallbacks;

status_t 
GxBox_SetDMRCallbacks(GxBoxDMRCallbacks *pCallbackSet);

status_t GxBox_StartDMR();
status_t GxBox_StopDMR();

__END_DECLS

#endif

