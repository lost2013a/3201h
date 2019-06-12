/*
 * =====================================================================================
 *
 *       Filename   gxcas_cas_register.hxx
 *
 *    Description:  头文件用于注册cas
 *
 *        Version:  1.0
 *        Created:  2012年3月28日 20时15分02秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangsy
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */

#ifndef __GXCAS_CAS_REGISTER_H__
#define __GXCAS_CAS_REGISTER_H__

#include "gxcas_register.hxx"

#define REGISTER_MGCA       cyg_cas_register_mgca               mgca        CYGBLD_ATTRIB_INIT_PRI(60110);;
#define REGISTER_MGCA42X    cyg_cas_register_mgca42x            mgca42x     CYGBLD_ATTRIB_INIT_PRI(60110);;
#define REGISTER_SUMAVISIONS    (cyg_cas_register_sumavisions        sumavisions);
#endif

