#ifndef __GXAV_AUDIORECV_PROPERTYTYPES_H__
#define __GXAV_AUDIORECV_PROPERTYTYPES_H__

typedef enum {
	SAMPLE_FRE_44KDOT1HZ = 0,
	SAMPLE_FRE_48KHZ,
	SAMPLE_FRE_32KHZ
} GxAudioReceiverProperty_SampleFre;

typedef enum {
	AUDIO_RECEIVER_ADC         = 0,
	AUDIO_RECEIVER_AC97        = 1,
	AUDIO_RECEIVER_PARALLEL    = 2
} GxAudioReceiverProperty_Type;

typedef struct{
	GxAudioReceiverProperty_Type  type;
} GxAudioReceiverProperty_Input;

typedef struct{
	GxAudioReceiverProperty_SampleFre samplefre;
	unsigned int bitwidth;
	unsigned int channelnum;
} GxAudioReceiverProperty_Config;

typedef struct{
	unsigned int state;

#define AUDIORECV_RUNNING 0
#define AUDIORECV_STOPED  1

} GxAudioReceiverProperty_State;

#endif /* __GXAV_AUDIORECV_PROPERTYTYPES_H__ */

