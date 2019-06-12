/*
 * =====================================================================================
 *
 *       Filename:  shell.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2011年04月11日 10时29分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */

#ifndef SHELL_H
#define SHELL_H

#include <cyg/infra/cyg_type.h>

typedef int (*cmd_func)(int argc, char **argv);

struct shell_command {
	char *cmd;
	cmd_func func;
	char *helpbrief;
};

#ifdef __cplusplus
extern "C" {
#endif

void register_shell_cmd(const char *cmd, cmd_func func, const char *help);
void shell(void);

#ifdef __cplusplus
}
#endif

#define SHELL(cmd_str, func_, help_)                                        \
	int func_(int argc, char **argv);                                   \
	class shell_class_##cmd_str {                                       \
		public:                                                     \
			shell_class_##cmd_str(void) {                       \
				register_shell_cmd(#cmd_str, func_, help_); \
			}                                                   \
	};                                                                  \
	shell_class_##cmd_str shell_##cmd_str CYGBLD_ATTRIB_INIT_PRI(60113) 

#define __commanddata __attribute__ ((__section__ (".data.commands")))

#define COMMAND(cmd_, func_, help_) \
	int func_(int argc, char **argv); \
	struct shell_command __commanddata shell_cmd ## cmd_ = {#cmd_, func_, help_}

extern struct shell_command __commands_begin;
extern struct shell_command __commands_end;

#endif


