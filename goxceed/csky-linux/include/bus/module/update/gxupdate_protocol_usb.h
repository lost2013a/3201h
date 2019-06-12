#ifndef __GXUPDATE_USB_H__
#define __GXUPDATE_USB_H__

#include "gxupdate_stream.h"
#include "gxcore.h"

__BEGIN_DECLS

#define GXUPDATE_PROTOCOL_USB               "usb update protocol"
#define GXUPDATE_MAX_NUM_USB_OPEN           (1)
#define GXUPDATE_MAX_FILE_PATH_LENGTH       (256)

#define GXUPDATE_USB_SELECT_TERMINAL_TYPE   (0)
#define GXUPDATE_SELECT_FILE_NAME           (1)
#define GXUPDATE_USB_SET_CRC                (2)

typedef struct {
	GxUpdate_Terminal       type;
} GxUpdate_ConfigUsbTerminalType;

typedef struct {
	char    file[GXUPDATE_MAX_FILE_PATH_LENGTH];
} GxUpdate_SelectUsbFile;


extern GxUpdate_ProtocolOps gxupdate_protocol_usb;

__END_DECLS

#endif
