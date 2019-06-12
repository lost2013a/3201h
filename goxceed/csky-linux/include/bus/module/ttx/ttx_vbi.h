#ifndef COM_TTX_VBI_H
#define COM_TTX_VBI_H

//#include "stb_data_type.h"
#include "gxtype.h"
#include "gxcore.h"

__BEGIN_DECLS

//*********************** 结构声明 ****************************



//*********************** 寄存器声明 ***********************
/*#if (CHIP_GX6102||CHIP_GX3001||CHIP_GX6201)
//VPU VBI寄存器

#define VBI_CTRL   *(volatile uint32_t*)(0x40005048)
#define VBI_ADDR   *(volatile uint32_t*)(0x4000504C)

//TV VBI寄存器

#define VBI_TLX_CTRL1  *(volatile uint32_t*)(0x4000406c)
#define VBI_TLX_CTRL2  *(volatile uint32_t*)(0x40004070)

#else */

//VPU VBI寄存器

#define VBI_CTRL        *(volatile uint32_t*)(0x40005054)
#define VBI_ADDR        *(volatile uint32_t*)(0x40005058)

//TV VBI寄存器

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

extern uint8_t  teletext_vbi_inistial(void);//初始化解复用，和VPU数据读取，TV数据读取
extern uint8_t teletext_vbi_destroy(void);
extern void  teletext_vbi_copy(volatile uint8_t *,uint16_t);//拷贝数据

//extern AppErr_t ttx_filter_reset(void);

__END_DECLS

#endif

