#ifndef __GXUPDATE_PROTOCOL_TS_H__
#define __GXUPDATE_PROTOCOL_TS_H__

#include "gxcore.h"
#include "gxupdate_stream.h"
#include <gxcore.h>
#include "module/frontend/gxfrontend_module.h"

__BEGIN_DECLS

#define GXUPDATE_PROTOCOL_TS_CONFIG     (1)
#define GXUPDATE_MAX_NUM_TS_OPEN        (1)

#define GXUPDATE_PROTOCOL_TS            ("ts update protocol")

typedef struct {
	uint32_t    demux_id;   /** TS������DEMUX�豸��*/
	GxFrontend  front_end;  /** TS���ǰ�˲���*/
	uint16_t    pid;        /** TS��PID*/
	uint8_t     table_id;   /** TS�� Section Table ID*/
} GxUpdate_TSInfo;


extern GxUpdate_ProtocolOps gxupdate_protocol_ts;

__END_DECLS

#endif
