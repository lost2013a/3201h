/**
 * @file gxca_demux.h
 * @author zhangsy
 * @brief demux module interface
 * @defgroup ca_module CA Module
 */
 /*@{*/
#ifndef __GX_CA_DEMUX_H__
#define __GX_CA_DEMUX_H__

#include "gxtype.h"
#include "gxcore.h"
#include "gxcas.h"

__BEGIN_DECLS


/**
* @brief    init Demux
* @param []	void
* @return   int  >= 0, sucess.<0 failure
* @note	it support max 64 channel & filter. It can be called only once;
*/
int GxDemux_Init(void);

/**
* @brief	Destroy Demux
* @param []	void
* @return   int  >= 0, sucess.<0 failure
* @note	    must be called after GxDemux_Init()
*/
int GxDemux_Destroy(void);

/**
* @brief    allocate slot(pid channel)
* @param []	DemuxID :demux id .0~1 is valid
* @param	PID :the pid value that need channel
* @return   handle == E_INVALID_HANDLE failure;or sucess
*/
handle_t GxDemux_ChannelAllocate(uint32_t DemuxID,uint16_t PID);

/**
* @brief        release a slot(pid channel)
* @param []	    Channel :handle of channel, get via "GxDemux_ChannelAllocate()";
* @return       int  >= 0, sucess.<0 failure
* @note		    function will release all filter under the channel;
*/
int GxDemux_ChannelFree(handle_t Channel);

/**
* @brief    set pid
* @param []	Channel :handle of channel, get via "GxDemux_ChannelAllocate()";
* @param []	pid :value of pid;
* @param []	RepeatFlag :if filter data non stop;0,if get one section, channel will stop and wait to be restart
* @return   int  >= 0, sucess.<0 failure
*/
int GxDemux_ChannelSetPID(handle_t Channel,  uint16_t pid,bool RepeatFlag);

/**
* @brief	enable channel
* @param []	Channel :handle of channel, get via "GxDemux_ChannelAllocate()";
* @return   int  >= 0, sucess.<0 failure
*/
int GxDemux_ChannelEnable(handle_t Channel);

/**
* @brief	disable channel
* @param []	Channel :handle of channel, get via "GxDemux_ChannelAllocate()";
* @return   int  >= 0, sucess.<0 failure
*/
int GxDemux_ChannelDisable(handle_t  Channel);

/**
* @brief	get channel that bind by the pid
* @param []	Channel :handle of channel, get via "GxDemux_ChannelAllocate()";
* @return   handle == E_INVALID_HANDLE failure;or sucess
*/
handle_t GxDemux_ChannelGetByPid(uint32_t DemuxID , uint16_t pid);

/**
* @brief	allocate a filter and tie up with the channel
* @param []	Channel :handle of channel, get via "GxDemux_ChannelAllocate()";
* @return   handle == E_INVALID_HANDLE failure;or sucess
*/
handle_t GxDemux_FilterAllocate(handle_t Channel);

/**
* @brief	get channel's pid via handle of filter
* @param []	Filter :handle of filter, get via "GxDemux_FilterAllocate()";
* @param [out] pid :the value of pid
* @return      int  >= 0, sucess.<0 failure
*/
int GxDemux_FilterGetPID(handle_t Filter,OUT int16_t *pid);


/**
* @brief	release a filter
* @param []	Filter :handle of filter, get via "GxDemux_FilterAllocate()";
* @return      int  >= 0, sucess.<0 failure
*/
int GxDemux_FilterFree(handle_t  Filter);

/**
* @brief	set up  a filter
* @param []	Filter :handle of filter, get via "GxDemux_FilterAllocate()";
* @param [in] Match :value need to be match when filter running
* @param [in] Mask : mask value
* @param [] Depth : number of match, filter depth
* @param [] Equal : if false, just when the version number is not same as (match[5]&0x3e)>>1 & mask[5],
				  filter can get data. it will not affect to other byte of match.
* @param [] CRCFlag : if open crc verify
* @return      int  >= 0, sucess.<0 failure
*/
int GxDemux_FilterSetup(handle_t Filter,
		IN const uint8_t *Match,
		IN const uint8_t *Mask,
		bool Equal,
		bool CRCFlag,
		bool SWFilter,
		size_t Depth);


/**
* @brief	enable filter
* @param []	Filter :handle of channel, get via "GxDemux_FilterAllocate()";
* @return      int  >= 0, sucess.<0 failure
*/
int GxDemux_FilterEnable(handle_t Filter);

/**
* @brief	disable filter
* @param []	Filter :handle of channel, get via "GxDemux_FilterAllocate()";
* @return      int  >= 0, sucess.<0 failure
*/
int GxDemux_FilterDisable(handle_t Filter);

/**
* @brief	query if filter have get data and copy data to buffer
* @param[]	Filter :handle of channel, get via "GxDemux_FilterAllocate()";
* @param[out] Buffer :buffer used to save section data.The data may be more than one section
			but will be multiples of section length.U must split it via compare section length.
* @param[]	BufferSize: size of the buffer that use to save data.
* @param[out] Datalen: size of data have read.

* @return      int  >= 0, sucess, will return *DataLen.<0 failure
*/
int GxDemux_QueryAndGetData(handle_t Filter,
		OUT uint8_t *Buffer,
		uint32_t  BufferSize,
		OUT uint32_t *Datalen);

__END_DECLS

#endif
/*@}*/

