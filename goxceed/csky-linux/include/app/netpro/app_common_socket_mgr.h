#ifndef __SOCKET_MGR_H_
#define __SOCKET_MGR_H_
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ifaddrs.h>
#include "gxcore.h"
#include <unistd.h>
#include <fcntl.h> 

#include <errno.h> 
#include <netinet/tcp.h> 


#ifdef MIN
#undef MIN
#define MIN(x,y) ((x)<(y)? (x):(y))
#else
#define MIN(x,y) ((x)<(y)? (x):(y))
#endif

typedef enum{
 	NET_NONE,
	NET_UDP,
	NET_TCP,
	NET_RAW,
	NET_MAX
}NetProtocal;

typedef int (*writeBuffer)(void *fd, char *buffer, unsigned int length,int);

typedef struct socketParam_s
{
    char* destIpAddr;
    int port;
    bool isReuseAddr;
    NetProtocal protocal;
    writeBuffer func;
		int recvBufLen;//0 默认 大于0 修改
}socketParam_t;

typedef struct socketMgrProtocalOps_s
{
    int (*createSocketFd)(socketParam_t param, int *fd);
    int (*destroySocketFd)(int fd, socketParam_t *param);
    int (*readData)(int fd,char *buffer,int length,int*p_outError);
		int (*send)(int fd,char *buffer,int length,int*p_outError);
}socketMgrProtocalOps_t;

void* app_cmm_socketCreateSocketFd(socketParam_t socketParam);

int app_cmm_socketDestroySocketFd(void* fd);

void app_cmm_socketInitNet(void);

void app_cmm_socketDeinitNet(void);

int app_cmm_socketGetTimeoutCnt(void *fd);

void app_cmm_socketClearTimeoutCnt(void *fd);

int app_cmm_socketRegisterSocketProtocal(NetProtocal protocal, socketMgrProtocalOps_t *ops);

char *app_cmm_getConfigLocalNetworkName(void);

void app_cmm_getLocalIpAddr(in_addr_t *addr, char *ifa_name);
int  app_cmm_socket_send(void* fd,char*p_dta,int len,int *p_error);


#endif
