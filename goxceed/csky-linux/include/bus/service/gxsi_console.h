#ifndef __GX_SI_CONSOLE_H__
#define __GX_SI_CONSOLE_H__

#include "gxbus.h"
#include "gxcore.h"
#include "gxsi.h"

#define MAX_SI_CONSOLE_COUNT     (32)

//0:upgrade, other: not upgrade

typedef enum {
	NIT_TABLE = 0,
	PMT_TABLE,
	SDT_TABLE,
	PAT_TABLE
} GxConsole_TableType;

typedef enum {
	NO_CHANGE  = 0,
	NIT_CHANGE,
	PMT_CHANGE,
	SDT_CHANGE,
	PAT_CHANGE,
	UPGRADE_CHANGE
} GxConsole_ChangeType;

typedef int32_t (*GXCONSOLE_UPGRADE_CBK)(GxConsole_TableType type, uint8_t *section, int32_t section_len, void *priv);

typedef struct {
	GxConsole_TableType   type;
	GxSiFilter            filter;
	uint8_t               check_version;
	uint8_t               version;
	void                  *priv; //需要用户自己定义结构体，配置自己需要的升级参数
	GXCONSOLE_UPGRADE_CBK cbk;
} GxConsole_Check;

typedef struct {
	int32_t           ts_src;
	int32_t           dmx_id;
	uint16_t          count;
	GxConsole_Check   param[MAX_SI_CONSOLE_COUNT];
} GxConsole_Config;

typedef struct {
	GxConsole_ChangeType  type;
	uint8_t               version;
	void                  *priv;
} GxConsole_Change;

typedef GxConsole_Config GxMsgProperty_SiConsoleConfig;
typedef GxConsole_Change GxMsgProperty_SiConsoleChange;

extern GxServiceClass si_console_service;
#endif /* __GX_SI_CONSOLE_H__ */
