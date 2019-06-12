#ifndef __GX_PLAYER__VOD_H__
#define __GX_PLAYER__VOD_H__

typedef struct{
	unsigned int frequency;
	unsigned int symborate;
	unsigned int qam_mode;
	union{
		unsigned int serviceid;
		unsigned int pmtpid;
		struct{
			unsigned int u32VideoPid;
			unsigned int u32AudioPid;
			unsigned int u32PcrPid;
			unsigned int u32EmmPid;
			unsigned int u32AudioEcmPid;
			unsigned int u32VideoEcmPid;
		}PidParam;
	}VodParam;
}PlayerVodPlayParam;

typedef struct{
	unsigned int u32VideoPid;
	unsigned int u32AudioPid;
	unsigned int u32PcrPid;
	unsigned int videofmt;
	unsigned int audiofmt;
}PlayerVodInfo;

typedef enum
{
	PLAYER_VOD_GET_ARECODE,  //info为int类型
	PLAYER_VOD_GET_USERID,
	PLAYER_VOD_GET_PRODUCTID,
}PlayerVodCommand;

typedef struct {
	int  (*play_by_pid)  (PlayerVodPlayParam param, int flags_sync);
	int  (*play_by_serviceid)  (PlayerVodPlayParam param, int flags_sync);
	int  (*play_by_pmtid) (PlayerVodPlayParam param, int flags_sync);
	int  (*pause)  (int flags_sync);
	int  (*resume) (int flags_sync);
	int  (*stop)  (int clear, int flags_sync);
	int  (*seek) (int flags_sync);
	int  (*get_info)(PlayerVodInfo* info);
	int  (*get_info_by_pmtid)(PlayerVodPlayParam param, PlayerVodInfo* info);
	int  (*get_play_info)(int cmd, void* info);
}PlayerVodOption;

extern void GxPlayer_Register_VOD_Options(PlayerVodOption* opt);
extern void GxPlayer_unRegister_Vod_Options(void);
extern status_t GxPlayer_MediaVodPlay(const char* name, const char* srcurl, int64_t start, void* cb);
extern status_t GxPlayer_MediaVodStop(const char* name);
extern status_t GxPlayer_MediaVodSeek(const char* name, int64_t time, SeekFlag flag);
extern status_t GxPlayer_MediaVodPause(const char* name);
extern status_t GxPlayer_MediaVodResume(const char* name);
extern status_t GxPlayer_MediaVodSpeed(const char* name, float speed);
extern status_t GxPlayer_MediaVodGetTime(const char* name, int64_t* start, int64_t* position, int64_t* duration);
extern status_t GxPlayer_MediaVodDvbPause(const char* name);
extern status_t GxPlayer_MediaVodDvbResume(const char* name, int clear_data);
extern status_t GxPlayer_MediaVodDvbSeek(const char* name, int64_t seek_time, SeekFlag flag);

#endif

