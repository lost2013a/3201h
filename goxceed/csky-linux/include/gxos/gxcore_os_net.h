#ifndef GXCORE_OS_NETWORK
#define GXCORE_OS_NETWORK

#include "gxtype.h"
#include <common/byteswap.h>
#include "gxcore_version.h"

#define closesocket	close
#define SOCKET	int32_t
#define INVALID_SOCKET	-1
#define SOCKET_ERROR	-1

#ifdef __cplusplus
extern "C"{
#endif

/* Initialize/Cleanup the network API
   GxCore must be initialized before calls to functions in this library,
   because this library uses utility functions from the GxCore library.
*/
extern int GxCore_Net_Init(void);
extern void GxCore_Net_Quit(void);

/***********************************************************************/
/* IPv4 hostname resolution API                                        */
/***********************************************************************/

typedef struct {
	uint32_t host;			/* 32-bit IPv4 host address */
	uint16_t port;			/* 16-bit protocol port */
} IPaddress;

/* Resolve a host name and port to an IP address in network form.
   If the function succeeds, it will return 0.
   If the host couldn't be resolved, the host portion of the returned
   address will be INADDR_NONE, and the function will return -1.
   If 'host' is NULL, the resolved host will be set to INADDR_ANY.
 */
#ifndef INADDR_ANY
#define INADDR_ANY		0x00000000
#endif
#ifndef INADDR_NONE
#define INADDR_NONE		0xFFFFFFFF
#endif
#ifndef INADDR_BROADCAST
#define INADDR_BROADCAST	0xFFFFFFFF
#endif
extern int GxCore_ResolveHost(IPaddress *address, const char *host, uint16_t port);

/* Resolve an ip address to a host name in canonical form.
   If the ip couldn't be resolved, this function returns NULL,
   otherwise a pointer to a static buffer containing the hostname
   is returned.  Note that this function is not thread-safe.
*/
extern const char * GxCore_ResolveIP(IPaddress *ip);


/***********************************************************************/
/* TCP network API                                                     */
/***********************************************************************/
struct _TCPsocket {
	int ready;
	SOCKET channel;
	IPaddress remoteAddress;
	IPaddress localAddress;
	int sflag;
};

typedef struct _TCPsocket *TCPsocket;

/* Open a TCP network socket
   If ip.host is INADDR_NONE or INADDR_ANY, this creates a local server
   socket on the given port, otherwise a TCP connection to the remote
   host and port is attempted. The address passed in should already be
   swapped to network byte order (addresses returned from 
   GxCore_ResolveHost() are already in the correct form).
   The newly created socket is returned, or NULL if there was an error.
*/
extern TCPsocket GxCore_TCP_Open(IPaddress *ip);

/* Accept an incoming connection on the given server socket.
   The newly created socket is returned, or NULL if there was an error.
*/
extern TCPsocket GxCore_TCP_Accept(TCPsocket server);

/* Get the IP address of the remote system associated with the socket.
   If the socket is a server socket, this function returns NULL.
*/
extern IPaddress * GxCore_TCP_GetPeerAddress(TCPsocket sock);

/* Send 'len' bytes of 'data' over the non-server socket 'sock'
   This function returns the actual amount of data sent.  If the return value
   is less than the amount of data sent, then either the remote connection was
   closed, or an unknown socket error occurred.
*/
extern int GxCore_TCP_Send(TCPsocket sock, const void *data,	int len);

/* Receive up to 'maxlen' bytes of data over the non-server socket 'sock',
   and store them in the buffer pointed to by 'data'.
   This function returns the actual amount of data received.  If the return
   value is less than or equal to zero, then either the remote connection was
   closed, or an unknown socket error occurred.
*/
extern int GxCore_TCP_Recv(TCPsocket sock, void *data, int maxlen);

/* Close a TCP network socket */
extern void GxCore_TCP_Close(TCPsocket sock);


/***********************************************************************/
/* UDP network API                                                     */
/***********************************************************************/

/* The maximum channels on a a UDP socket */
#define GxCoreNET_MAX_UDPCHANNELS	32
/* The maximum addresses bound to a single UDP socket channel */
#define GxCoreNET_MAX_UDPADDRESSES	4

struct UDP_channel {
	int numbound;
	IPaddress address[GxCoreNET_MAX_UDPADDRESSES];
};

struct _UDPsocket {
	int ready;
	SOCKET channel;
	IPaddress address;
 	struct UDP_channel binding[GxCoreNET_MAX_UDPCHANNELS];
};

typedef struct _UDPsocket *UDPsocket;
typedef struct {
	int channel;		/* The src/dst channel of the packet */
	uint8_t *data;		/* The packet data */
	int len;		/* The length of the packet data */
	int maxlen;		/* The size of the data buffer */
	int status;		/* packet status after sending */
	IPaddress address;		/* The source/dest address of an incoming/outgoing packet */
} UDPpacket;

/* Allocate/resize/free a single UDP packet 'size' bytes long.
   The new packet is returned, or NULL if the function ran out of memory.
 */
extern UDPpacket * GxCore_AllocPacket(int size);
extern int GxCore_ResizePacket(UDPpacket *packet, int newsize);
extern void GxCore_FreePacket(UDPpacket *packet);

/* Allocate/Free a UDP packet vector (array of packets) of 'howmany' packets,
   each 'size' bytes long.
   A pointer to the first packet in the array is returned, or NULL if the
   function ran out of memory.
 */
extern UDPpacket ** GxCore_AllocPacketV(int howmany, int size);
extern void GxCore_FreePacketV(UDPpacket **packetV);


/* Open a UDP network socket
   If 'port' is non-zero, the UDP socket is bound to a local port.
   The 'port' should be given in native byte order, but is used
   internally in network (big endian) byte order, in addresses, etc.
   This allows other systems to send to this socket via a known port.
*/
extern UDPsocket GxCore_UDP_Open(uint16_t port);

/* Bind the address 'address' to the requested channel on the UDP socket.
   If the channel is -1, then the first unbound channel will be bound with
   the given address as it's primary address.
   If the channel is already bound, this new address will be added to the
   list of valid source addresses for packets arriving on the channel.
   If the channel is not already bound, then the address becomes the primary
   address, to which all outbound packets on the channel are sent.
   This function returns the channel which was bound, or -1 on error.
*/
extern int GxCore_UDP_Bind(UDPsocket sock, int channel, IPaddress *address);

/* Unbind all addresses from the given channel */
extern void GxCore_UDP_Unbind(UDPsocket sock, int channel);

/* Get the primary IP address of the remote system associated with the 
   socket and channel.  If the channel is -1, then the primary IP port
   of the UDP socket is returned -- this is only meaningful for sockets
   opened with a specific port.
   If the channel is not bound and not -1, this function returns NULL.
 */
extern IPaddress * GxCore_UDP_GetPeerAddress(UDPsocket sock, int channel);

/* Send a vector of packets to the the channels specified within the packet.
   If the channel specified in the packet is -1, the packet will be sent to
   the address in the 'src' member of the packet.
   Each packet will be updated with the status of the packet after it has 
   been sent, -1 if the packet send failed.
   This function returns the number of packets sent.
*/
extern int GxCore_UDP_SendV(UDPsocket sock, UDPpacket **packets, int npackets);

/* Send a single packet to the specified channel.
   If the channel specified in the packet is -1, the packet will be sent to
   the address in the 'src' member of the packet.
   The packet will be updated with the status of the packet after it has
   been sent.
   This function returns 1 if the packet was sent, or 0 on error.

   NOTE:
   The maximum size of the packet is limited by the MTU (Maximum Transfer Unit)
   of the transport medium.  It can be as low as 250 bytes for some PPP links,
   and as high as 1500 bytes for ethernet.
*/
extern int GxCore_UDP_Send(UDPsocket sock, int channel, UDPpacket *packet);

/* Receive a vector of pending packets from the UDP socket.
   The returned packets contain the source address and the channel they arrived
   on.  If they did not arrive on a bound channel, the the channel will be set
   to -1.
   The channels are checked in highest to lowest order, so if an address is
   bound to multiple channels, the highest channel with the source address
   bound will be returned.
   This function returns the number of packets read from the network, or -1
   on error.  This function does not block, so can return 0 packets pending.
*/
extern int GxCore_UDP_RecvV(UDPsocket sock, UDPpacket **packets);

/* Receive a single packet from the UDP socket.
   The returned packet contains the source address and the channel it arrived
   on.  If it did not arrive on a bound channel, the the channel will be set
   to -1.
   The channels are checked in highest to lowest order, so if an address is
   bound to multiple channels, the highest channel with the source address
   bound will be returned.
   This function returns the number of packets read from the network, or -1
   on error.  This function does not block, so can return 0 packets pending.
*/
extern int GxCore_UDP_Recv(UDPsocket sock, UDPpacket *packet);

/* Close a UDP network socket */
extern void GxCore_UDP_Close(UDPsocket sock);


/***********************************************************************/
/* Hooks for checking sockets for available data                       */
/***********************************************************************/

/* The select() API for network sockets */
struct GxCore_Socket {
	int ready;
	SOCKET channel;
};

struct _GxCore_SocketSet {
	int numsockets;
	int maxsockets;
	struct GxCore_Socket **sockets;
};

typedef struct _GxCore_SocketSet *GxCore_SocketSet;

/* Any network socket can be safely cast to this socket type */
typedef struct {
	int ready;
} *GxCore_GenericSocket;

/* Allocate a socket set for use with GxCore_CheckSockets()
   This returns a socket set for up to 'maxsockets' sockets, or NULL if
   the function ran out of memory.
 */
extern GxCore_SocketSet GxCore_AllocSocketSet(int maxsockets);

/* Add a socket to a set of sockets to be checked for available data */
#define GxCore_TCP_AddSocket(set, sock) \
			GxCore_AddSocket(set, (GxCore_GenericSocket)sock)
#define GxCore_UDP_AddSocket(set, sock) \
			GxCore_AddSocket(set, (GxCore_GenericSocket)sock)
extern int GxCore_AddSocket(GxCore_SocketSet set, GxCore_GenericSocket sock);

/* Remove a socket from a set of sockets to be checked for available data */
#define GxCore_TCP_DelSocket(set, sock) \
			GxCore_DelSocket(set, (GxCore_GenericSocket)sock)
#define GxCore_UDP_DelSocket(set, sock) \
			GxCore_DelSocket(set, (GxCore_GenericSocket)sock)
extern int GxCore_DelSocket(GxCore_SocketSet set, GxCore_GenericSocket sock);

/* This function checks to see if data is available for reading on the
   given set of sockets.  If 'timeout' is 0, it performs a quick poll,
   otherwise the function returns when either data is available for
   reading, or the timeout in milliseconds has elapsed, which ever occurs
   first.  This function returns the number of sockets ready for reading, 
   or -1 if there was an error with the select() system call.
*/
extern int GxCore_CheckSockets(GxCore_SocketSet set, uint32_t timeout);

/* After calling GxCore_CheckSockets(), you can use this function on a
   socket that was in the socket set, to find out if data is available
   for reading.
*/
#define GxCore_SocketReady(sock) \
		((sock != NULL) && ((GxCore_GenericSocket)sock)->ready)

/* Free a set of sockets allocated by GxCore_NetAllocSocketSet() */
extern void GxCore_FreeSocketSet(GxCore_SocketSet set);


/***********************************************************************/
/* Platform-independent data conversion functions                      */
/***********************************************************************/

/* Write a 16/32 bit value to network packet buffer */
extern void GxCore_Write16(uint16_t value, void *area);
extern void GxCore_Write32(uint32_t value, void *area);

/* Read a 16/32 bit value from network packet buffer */
extern uint16_t GxCore_Read16(void *area);
extern uint32_t GxCore_Read32(void *area);

/***********************************************************************/
/* Error reporting functions                                           */
/***********************************************************************/

/* I'm eventually going to try to disentangle GxCore from GxCore, thus making
   GxCore an independent X-platform networking toolkit.  Not today though....

extern no_parse_DECLSPEC void GxCoreCALL GxCore_SetError(const char *fmt, ...);
extern no_parse_DECLSPEC char * GxCoreCALL GxCore_GetError(void);
*/


/* Inline macro functions to read/write network data */

/* Warning, some systems have data access alignment restrictions */
#if defined(sparc) || defined(mips)
#define GxCore_DATA_ALIGNED	1
#endif
#ifndef GxCore_DATA_ALIGNED
#define GxCore_DATA_ALIGNED	0
#endif

/* Write a 16 bit value to network packet buffer */
#if !GxCore_DATA_ALIGNED
#define GxCore_Write16(value, areap)	\
	(*(uint16_t *)(areap) = GxSwapBE16(value))
#else
#if GxCore_BYTEORDER == GxCore_BIG_ENDIAN
#define GxCore_Write16(value, areap)	\
do 					\
{					\
	uint8_t *area = (uint8_t *)(areap);	\
	area[0] = (value >>  8) & 0xFF;	\
	area[1] =  value        & 0xFF;	\
} while ( 0 )
#else
#define GxCore_Write16(value, areap)	\
do 					\
{					\
	uint8_t *area = (uint8_t *)(areap);	\
	area[1] = (value >>  8) & 0xFF;	\
	area[0] =  value        & 0xFF;	\
} while ( 0 )
#endif
#endif /* !GxCore_DATA_ALIGNED */

/* Write a 32 bit value to network packet buffer */
#if !GxCore_DATA_ALIGNED
#define GxCore_Write32(value, areap) 	\
	*(uint32_t *)(areap) = GxSwapBE32(value);
#else
#if GxCore_BYTEORDER == GxCore_BIG_ENDIAN
#define GxCore_Write32(value, areap) 	\
do					\
{					\
	uint8_t *area = (uint8_t *)(areap);	\
	area[0] = (value >> 24) & 0xFF;	\
	area[1] = (value >> 16) & 0xFF;	\
	area[2] = (value >>  8) & 0xFF;	\
	area[3] =  value       & 0xFF;	\
} while ( 0 )
#else
#define GxCore_Write32(value, areap) 	\
do					\
{					\
	uint8_t *area = (uint8_t *)(areap);	\
	area[3] = (value >> 24) & 0xFF;	\
	area[2] = (value >> 16) & 0xFF;	\
	area[1] = (value >>  8) & 0xFF;	\
	area[0] =  value       & 0xFF;	\
} while ( 0 )
#endif
#endif /* !GxCore_DATA_ALIGNED */

/* Read a 16 bit value from network packet buffer */
#if !GxCore_DATA_ALIGNED
#define GxCore_Read16(areap) 		\
	(GxSwapBE16(*(uint16_t *)(areap)))
#else
#if GxCore_BYTEORDER == GxCore_BIG_ENDIAN
#define GxCore_Read16(areap) 		\
	((((uint8_t *)areap)[0] <<  8) | ((uint8_t *)areap)[1] <<  0)
#else
#define GxCore_Read16(areap) 		\
	((((uint8_t *)areap)[1] <<  8) | ((uint8_t *)areap)[0] <<  0)
#endif
#endif /* !GxCore_DATA_ALIGNED */

/* Read a 32 bit value from network packet buffer */
#if !GxCore_DATA_ALIGNED
#define GxCore_Read32(areap) 		\
	(GxSwapBE32(*(uint32_t *)(areap)))
#else
#if GxCore_BYTEORDER == GxCore_BIG_ENDIAN
#define GxCore_Read32(areap) 		\
	((((uint8_t *)areap)[0] << 24) | (((uint8_t *)areap)[1] << 16) | \
	 (((uint8_t *)areap)[2] <<  8) |  ((uint8_t *)areap)[3] <<  0)
#else
#define GxCore_Read32(areap) 		\
	((((uint8_t *)areap)[3] << 24) | (((uint8_t *)areap)[2] << 16) | \
	 (((uint8_t *)areap)[1] <<  8) |  ((uint8_t *)areap)[0] <<  0)
#endif
#endif /* !GxCore_DATA_ALIGNED */

#ifdef __cplusplus
}
#endif

#endif
