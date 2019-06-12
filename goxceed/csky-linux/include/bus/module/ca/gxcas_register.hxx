/*
 * =====================================================================================
 *
 *       Filename   gxcas_register.hxx
 *
 *    Description:  ͷ�ļ�����ע��cas
 *
 *        Version:  1.0
 *        Created:  2012��3��28�� 20ʱ15��02��
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhangsy
 *        Company:  Hangzhou Nationalchip Science&Technology Co.Ltd.
 *
 * =====================================================================================
 */

#ifndef __GXCAS_REGISTER_H__
#define __GXCAS_REGISTER_H__

extern "C" void gxcas_register_mgca(void);
extern "C" void gxcas_register_mgca42x(void);
extern "C" void gxcas_register_sumavisions(void);

class cyg_cas_register_mgca{
    public:
        cyg_cas_register_mgca(void)
        {
            gxcas_register_mgca();
        }
};

class cyg_cas_register_mgca42x{
    public:
        cyg_cas_register_mgca42x(void)
        {
            gxcas_register_mgca42x();
        }
};

class cyg_cas_register_sumavisions{
    public:
        cyg_cas_register_sumavisions(void)
        {
            gxcas_register_sumavisions();
        }
};



#endif

