/*
 * Generic RTC interface.
 * This version contains the part of the user interface to the Real Time Clock
 * service. It is used with both the legacy mc146818 and also  EFI
 * Struct rtc_time and first 12 ioctl by Paul Gortmaker, 1996 - separated out
 * from <linux/mc146818rtc.h> to this file for 2.4 kernels.
 *
 * Copyright (C) 1999 Hewlett-Packard Co.
 * Copyright (C) 1999 Stephane Eranian <eranian@hpl.hp.com>
 */
#ifndef _GXCORE_OS_RTC_H_
#define _GXCORE_OS_RTC_H_

/*
 * The struct used to pass data via the following ioctl. Similar to the
 * struct tm in <time.h>, but it needs to be here so that the kernel
 * source is self contained, allowing cross-compiles, etc. etc.
 */

struct rtc_time {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
};

void GxCore_RtcSetTime(struct rtc_time *tm);
void GXCore_RtcGetTime(struct rtc_time *tm);

#endif /* _LINUX_RTC_H_ */
