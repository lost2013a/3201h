/*
 * =====================================================================================
 *
 *       Filename:  debug.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/27/2010 10:14:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhuzhg
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */

#ifndef DEBUG_H
#define DEBUG_H


#ifdef DEBUG
#  define BUG( ... )       printf( __VA_ARGS__ )
#  define LOG( ... )       printf( __VA_ARGS__ )
#  define DBG( ... )       printf( __VA_ARGS__ )
#else
#  define BUG( ... )   ((void)0)
#  define LOG( ... )   ((void)0)
#  define DBG( ... )   ((void)0)
#endif

#endif

