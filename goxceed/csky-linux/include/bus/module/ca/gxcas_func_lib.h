#ifndef __GXCAS_FUNC_LIB__
#define __GXCAS_FUNC_LIB__

#include "gxcore.h"

__BEGIN_DECLS

/*-------------------------------------------------------------------------
 * Function     : GxConvertMjdToYmd
 * Description  : convert Mjd date to year \ month \data mode
 *
 * Input        : Mjd--Mjd data
 * Output       : year--the actually year ,such as 2008
 *              : month
 *              : day
 *              : weekDay
 * Return       : none
 * ---------------------------------------------------------------------*/
extern void ConvertMjdToYmd( uint16_t mjd, uint16_t *year, uint8_t *month, uint8_t *day, uint8_t *weekDay );

/*-------------------------------------------------------------------------
 * Function     : GxConvertYmdToMjd
 * Description  : convert year\month\date mode to Mjd mode
 *
 * Input        : year--actually year sub 1900,such as 2008-1900=108
 *              : month
 *              : day
 * Output       : mjd-- the mjd mode date
 * Return       : none
 * ---------------------------------------------------------------------*/
extern void ConvertYmdToMjd( uint16_t *mjd, uint16_t year, uint8_t month, uint8_t day);


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  PmtParse
 *  Description:  Pmt解析到模板，用于获得pmt中CA相关到信息
 * =====================================================================================
 */

#define MAX_ECM_PID       (8)
#define MAX_ELEM_PER_ECM  (8)
struct pmt_ca_info {
	unsigned short  network_id; /* 原始网络ID */
	unsigned short  stream_id;  /* 当前TS流ID */
	unsigned short  service_id;
	unsigned short  pcr_pid;
	unsigned char   ecm_count;
	struct {
		unsigned short ecm_pid; /* 当前Ecm的PID*/
		unsigned short comp_count;
		unsigned short component_pid[MAX_ELEM_PER_ECM];
	} ecm[MAX_ECM_PID];
};

typedef bool (*CheckCaSystemID)(uint16_t cas_id);
extern void PmtParse(uint8_t* section, size_t Size,OUT struct pmt_ca_info* pcas_info,CheckCaSystemID check);

__END_DECLS

#endif

