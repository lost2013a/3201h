/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SHORT_SMOOTHING_BUFFER_DES_H__
#define __SHORT_SMOOTHING_BUFFER_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*short_smoothing_buffer 0x61 ������*/
typedef struct
{
	uint32_t descriptor_tag:8;
	uint32_t descriptor_length:8;
	uint32_t sb_size:2;
	uint32_t sb_leak_rate:6;
	uint32_t reserved:8;

	uint8_t * DVB_reserved;
}GxSubsystemSiParseShortSmoothingDes;//̫�鷳�ˣ�Ҳû�����ã���ʱ��д

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

