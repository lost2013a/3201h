#ifndef __GXAV_STC_PROPERTYTYPES_H__
#define __GXAV_STC_PROPERTYTYPES_H__

typedef struct {
	unsigned int mode;
#define AVPTS_RECOVER     0
#define VPTS_RECOVER      1
#define APTS_RECOVER      2
#define PCR_RECOVER       3
#define PURE_APTS_RECOVER 4
#define NO_RECOVER        5
} GxSTCProperty_Config;

typedef struct {
	int freq_HZ;
} GxSTCProperty_TimeResolution;

typedef struct {
	unsigned long long time;
} GxSTCProperty_Time;

typedef struct {
	unsigned int integer;
	unsigned int decimal;
} GxSTCProperty_Speed;

typedef struct {
	int valule;
} GxSTCProperty_Adjust;

#endif /* __GXAV_STC_PROPERTYTYPES_H__ */

