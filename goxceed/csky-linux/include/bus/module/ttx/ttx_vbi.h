#ifndef COM_TTX_VBI_H
#define COM_TTX_VBI_H

//#include "stb_data_type.h"
#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

//*********************** �ṹ���� ****************************



//*********************** �Ĵ������� ***********************
/*#if (CHIP_GX6102||CHIP_GX3001||CHIP_GX6201)
//VPU VBI�Ĵ���

#define VBI_CTRL   *(volatile uint32_t*)(0x40005048)
#define VBI_ADDR   *(volatile uint32_t*)(0x4000504C)

//TV VBI�Ĵ���

#define VBI_TLX_CTRL1  *(volatile uint32_t*)(0x4000406c)
#define VBI_TLX_CTRL2  *(volatile uint32_t*)(0x40004070)

#else */

//VPU VBI�Ĵ���

#define VBI_CTRL        *(volatile uint32_t*)(0x40005054)
#define VBI_ADDR        *(volatile uint32_t*)(0x40005058)

//TV VBI�Ĵ���

#define VBI_TLX_CTRL1   *(volatile uint32_t*)(0x4000406c)
#define VBI_TLX_CTRL2   *(volatile uint32_t*)(0x40004070)
//#endif

typedef struct {
	uint32_t DATA[32][13];
} V_DATA_VPU;


typedef struct {
	volatile uint8_t *vbi_read_ptr;
	uint16_t vbi_len;
	uint8_t reset_en;
} VBI_READ_FLUG;


extern uint16_t VBI_BUFFER_PTR;

extern uint8_t  teletext_vbi_inistial(void);//��ʼ���⸴�ã���VPU���ݶ�ȡ��TV���ݶ�ȡ
extern uint8_t teletext_vbi_destroy(void);
extern void  teletext_vbi_copy(volatile uint8_t *,uint16_t);//��������

//extern AppErr_t ttx_filter_reset(void);

__END_DECLS

#endif

