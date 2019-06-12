#ifndef __KERNELCALLS_H__
#define __KERNELCALLS_H__

#ifdef __cplusplus
extern "C" {
#endif
/****************************************************************/
//#define GX_DEBUG

#if (!defined(LINUX_OS) && !defined(ECOS_OS) && !defined(GXLOADER_OS))
#error "No defined OS"
#endif

#ifdef LINUX_OS
#	include <linux/kernel.h>
#	include <linux/slab.h>
#	include <linux/mm.h>
#	include <linux/ioport.h>
#	include <linux/errno.h>
#	include <linux/vmalloc.h>
#	include <asm/io.h>
#	include <asm/uaccess.h>
#	include <asm/cacheflush.h>
#	include <linux/memory.h>
#	include <linux/interrupt.h>
#	include <linux/delay.h>
#	include <linux/kthread.h>
#	include <asm/div64.h>
#	include <linux/version.h>
#	include <linux/list.h>
#	include <linux/proc_fs.h>
#	include <linux/proc_fs.h>
#	include <linux/time.h>

#	if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,28)
#		include <linux/semaphore.h>
#		include <asm/page.h>
#		include <linux/swab.h>
#	elif LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)
#		include <linux/semaphore.h>
#		include <linux/byteorder/swab.h>
#		include <asm-generic/page.h>
#	else
#		include <asm/semaphore.h>
#		include <linux/byteorder/swab.h>
#		include <asm-generic/page.h>
#	endif

#define MAX_KMALLOC_SIZE                    (128*1024 - 16)

#define gx_ioremap(offset,size)             ioremap(offset,size)
#define gx_iounmap(addr)                    iounmap((void *)(addr))

#define gx_request_mem_region(start,len)    request_mem_region(start,len,"av")
#define gx_release_mem_region(start,len)    release_mem_region(start,len)

#define gx_printf(fmt, args...)             printk(fmt, ##args)
#define gx_sprintf(buf, fmt, args...)       sprintf(buf, fmt, ##args)
#define gx_snprintf(buf, len, fmt, args...) snprintf(buf, len, fmt, ##args)
#define gx_sscanf(buf, fmt, args...)        sscanf(buf, fmt, ##args)

// memory
#define _malloc(size)                    kmalloc(size, GFP_KERNEL | __GFP_REPEAT);
#define _free(p)                         kfree(p)
#define _vmalloc(size)                   vmalloc(size)
#define _vfree(p)                        vfree(p)

extern void* gx_dma_alloc_coherent(void* dev, size_t size, void* dma_handle, int flag);
extern void  gx_dma_free_coherent(void* dev, size_t size, void* vaddr, void* dma_handle);
#define gx_dma_malloc(size)              gx_dma_alloc_coherent(NULL, size, NULL, GFP_DMA)
#define gx_dma_free(p, size)             gx_dma_free_coherent(NULL, size, p, NULL)

extern void* gx_dma_to_phys(void* dma_addr);
// virt/bus/phy/page conversion
#define gx_virt_to_phys(addr)            virt_to_phys((void *)addr)
#define gx_phys_to_virt(addr)            phys_to_virt(addr)

// time
#define gx_mdelay(n)                     mdelay((n))
#define gx_udelay(n)                     udelay(n)
#define gx_msleep(n)                     msleep((n))

int	gx_gettimeofday(struct timeval *tv, struct timezone *tz);
// spinlock
typedef spinlock_t gx_spin_lock_t;
#define gx_spin_lock_init(l)              spin_lock_init(l)
#define gx_spin_lock_bh(l)                spin_lock_bh(l)
#define gx_spin_unlock_bh(l)              spin_unlock_bh(l)
#define gx_spin_lock_irq(l)               spin_lock_irq(l)
#define gx_spin_lock(l)                   spin_lock(l)
#define gx_spin_unlock(l)                 spin_unlock(l)
#define gx_spin_lock_irqsave(l, f)        spin_lock_irqsave(l, f)
#define gx_spin_unlock_irqrestore(l, f)   spin_unlock_irqrestore(l, f)

// mutex lock
typedef struct mutex gx_mutex_t;
#define gx_mutex_init(m)                  mutex_init(m)
#define gx_mutex_lock(m)                  mutex_lock(m)
#define gx_mutex_unlock(m)                mutex_unlock(m)
#define gx_mutex_destroy(m)               mutex_destroy(m)

#define gx_mtc_decrypt(p)                (0)

typedef unsigned int gx_thread_id;

typedef int gx_thread_info;

typedef struct semaphore gx_sem_id;

typedef struct list_head  gxlist_head;

extern struct list_head *list_get(struct list_head *head);

#define GX_LIST_HEAD_INIT     LIST_HEAD_INIT
#define GX_LIST_HEAD          LIST_HEAD
#define GX_INIT_LIST_HEAD     INIT_LIST_HEAD

#define gxlist_add            list_add
#define gxlist_add_tail       list_add_tail
#define gxlist_del            list_del
#define gxlist_del_init       list_del_init
#define gxlist_empty          list_empty
#define gxlist_splice         list_splice
#define gxlist_get            list_get
#define gxlist_entry          list_entry
#define gxlist_for_each       list_for_each
#define gxlist_for_each_safe  list_for_each_safe
#define gxlist_for_each_entry list_for_each_entry
#define gxlist_for_each_entry_safe(pos, n, head, member)                           \
    for (pos = list_entry((head)->next, typeof(*pos), member),                     \
                        n = list_entry(pos->member.next, typeof(*pos), member);    \
                        &pos->member != (head);                                    \
                        pos = n, n = list_entry(n->member.next, typeof(*n), member))

#endif // end LINUX_OS

/****************************************************************/

#ifdef ECOS_OS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cyg/kernel/kapi.h>
#include <cyg/hal/hal_cache.h>
#include <cyg/hal/gxmtc.h>
//#include <cyg/posix/sys/time.h>
#include <sys/time.h>
#include <common/list.h>
#include <ctype.h>
#include <string.h>
#include <cyg/fs/compat.h>

#define PAGE_MAX   (1024)

#define PAGE_SHIFT (12)
#define MAX_KMALLOC_SIZE (0xffffffff)

#define gx_printf(fmt, args...)             printk(fmt, ##args)
#define gx_sprintf(buf, fmt, args...)       sprintf(buf, fmt, ##args)
#define gx_snprintf(buf, len, fmt, args...) sprintf(buf, fmt, ##args)
#define gx_sscanf(buf, fmt, args...)        sscanf(buf, fmt, ##args)

#define gx_ioremap(offset,size)          ioremap(offset)
#define gx_iounmap(addr)

#define gx_request_mem_region(start,len) request_mem_region(len)
#define gx_release_mem_region(start,len)

// memory
#define _malloc(size)                    malloc(size)
#define _free(p)                         free(p)
#define _vmalloc(size)                   malloc(size)
#define _vfree(p)                        free(p)

extern void* gx_dma_malloc(size_t size);
extern void  gx_dma_free(void*, size_t);
void* gx_dma_to_phys(void* addr);

extern cyg_uint32 hal_cached_to_phys(cyg_uint32 cached_addr);
extern cyg_uint32 hal_ioremap_cached(cyg_uint32 cached_addr);

#define gx_virt_to_phys(addr)            hal_cached_to_phys((cyg_uint32)(addr))
#define gx_phys_to_virt(addr)            hal_ioremap_cached((cyg_uint32 )(addr))

#define gx_mdelay(n)                     cyg_time_delay_us((n)*1000)
#define gx_udelay(n)                     cyg_time_delay_us(n)
#define gx_msleep(n)                     cyg_thread_delay(n>=10?n/10:1)
int	gx_gettimeofday(struct timeval *tv, struct timezone *tz);

// spinlock
typedef int gx_spin_lock_t;
#define gx_spin_lock_init(l)              do {} while(0)
#define gx_spin_lock_bh(l)                cyg_scheduler_lock()
#define gx_spin_unlock_bh(l)              cyg_scheduler_unlock()
#define gx_spin_lock_irq(l)               cyg_scheduler_lock()
#define gx_spin_lock(l)                   cyg_scheduler_lock()
#define gx_spin_unlock(l)                 cyg_scheduler_unlock()
#define gx_spin_lock_irqsave(l, f)        cyg_scheduler_lock()
#define gx_spin_unlock_irqrestore(l, f)   cyg_scheduler_unlock()

// mutex lock
typedef struct cyg_mutex_t gx_mutex_t;
#define gx_mutex_init(m)                  cyg_mutex_init(m)
#define gx_mutex_lock(m)                  cyg_mutex_lock(m)
#define gx_mutex_unlock(m)                cyg_mutex_unlock(m)
#define gx_mutex_destroy(m)               cyg_mutex_destroy(m)

#define gx_mtc_decrypt(p)                 gx_mtc_init((mtc_info *)(p))

#define do_div(a,b) a = (a)/(b)

/* is x a power of 2? */
#define is_power_of_2(x)	((x) != 0 && (((x) & ((x) - 1)) == 0))

typedef cyg_handle_t gx_thread_id;

typedef cyg_thread gx_thread_info;

typedef cyg_sem_t gx_sem_id;

extern void *ioremap(unsigned int offset);
extern void *request_mem_region(unsigned int len);
extern int test_bit (int nr, const volatile long unsigned int *);

extern cyg_uint32 hal_ioremap_cached(cyg_uint32 phy_addr);
extern cyg_uint32 hal_ioremap_uncached(cyg_uint32 phy_addr);
extern cyg_uint32 hal_uncached_map(cyg_uint32 addr);
extern cyg_uint32 hal_cached_map(cyg_uint32 addr);
typedef struct gxlist_head gxlist_head;

#endif // END ECOS_OS

/****************************************************************/
/****************************************************************/

#ifdef GXLOADER_OS

#ifndef NULL
#define NULL            ((void*)(0))
#endif

#ifndef size_t
#define size_t           unsigned int
#endif

struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

struct timezone {
	int	tz_minuteswest;	/* minutes west of Greenwich */
	int	tz_dsttime;	/* type of dst correction */
};

extern int isxdigit(int ch);
extern int islower(int ch);
extern int isdigit(int ch);
extern int toupper(int ch);
extern void *malloc(unsigned int size);
extern void free(void *ptr);
extern void *memset(void *s, int c, unsigned int count);
extern int printf(const char *fmt, ...);
extern void *memcpy(void *dest, const void *src, unsigned int count);
extern int sprintf(char *str, const char *format, ...);
extern int abs(int j);
extern size_t strlen(const char *s);
extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, size_t n);
extern char *strsep(char **s, const char *ct);

#define PAGE_MAX   (1024)

#define PAGE_SHIFT (12)
#define MAX_KMALLOC_SIZE (0xffffffff)

#define gx_printf(fmt, args...)             printf(fmt, ##args)
#define gx_sprintf(buf, fmt, args...)       sprintf(buf, fmt, ##args)
#define gx_snprintf(buf, len, fmt, args...) sprintf(buf, fmt, ##args)

#define gx_ioremap(offset, size)            ioremap(offset)
#define gx_iounmap(addr)

#define gx_request_mem_region(start,len) request_mem_region(len)
#define gx_release_mem_region(start,len)

// memory
#define _malloc(size)                    malloc(size)
#define _free(p)                         free(p)
#define _vmalloc(size)                   malloc(size)
#define _vfree(p)                        free(p)

void* gx_dma_to_phys(void* addr);
unsigned int gx_virt_to_phys(unsigned int addr);
unsigned int gx_phys_to_virt(unsigned int addr);

#define gx_dma_malloc(size)              gx_page_malloc(size)
#define gx_dma_free(p,size)              gx_page_free(p,size)

int	gx_gettimeofday(struct timeval *tv, struct timezone *tz);

#define gx_mtc_decrypt(p)	(0)

#define do_div(a,b) a = (a)/(b)

/* is x a power of 2? */
#define is_power_of_2(x)	((x) != 0 && (((x) & ((x) - 1)) == 0))

typedef int gx_thread_id;

typedef int gx_thread_info;

typedef int gx_sem_id;

extern void mdelay(unsigned int msec);
extern void udelay(unsigned int usec);
extern void *ioremap(unsigned int offset);
extern void *request_mem_region(unsigned int len);
extern int test_bit (int nr, const volatile long unsigned int *);
extern void gx_rtc_delay_ms(int ms);
extern void gx_rtc_delay_us(int us);

#define gx_mdelay(n) gx_rtc_delay_ms(n)
#define gx_udelay(n) gx_rtc_delay_us(n)
#define gx_msleep(n) gx_rtc_delay_ms(n)

struct gxlist_head {
    struct gxlist_head *next, *prev;
};

#define GX_LIST_HEAD_INIT(name) { &(name), &(name) }

#define GX_LIST_HEAD(name) \
	struct gxlist_head name = GX_LIST_HEAD_INIT(name)

#define GX_INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

void gxlist_add     (struct gxlist_head *newnode, struct gxlist_head *head);
void gxlist_add_tail(struct gxlist_head *newnode, struct gxlist_head *head);
void gxlist_del     (struct gxlist_head *entry);
void gxlist_del_init(struct gxlist_head *entry);
int  gxlist_empty   (struct gxlist_head *head );
void gxlist_splice  (struct gxlist_head *list, struct gxlist_head *head);

struct gxlist_head *gxlist_get(struct gxlist_head *head);

#define gxlist_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define gxlist_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
			pos = pos->next)

#define gxlist_for_each_entry(pos, head, member)                        \
	for (pos = gxlist_entry((head)->next, typeof(*pos), member);        \
			&pos->member != (head);                                     \
			pos = gxlist_entry(pos->member.next, typeof(*pos), member))

#define gxlist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
			pos = n, n = pos->next)

#define gxlist_for_each_entry_safe(pos, n, head, member)               \
	for (pos = gxlist_entry((head)->next, typeof(*pos), member),       \
			n = gxlist_entry(pos->member.next, typeof(*pos), member);  \
			&pos->member != (head);                                    \
			pos = n, n = gxlist_entry(n->member.next, typeof(*n), member))

typedef struct gxlist_head gxlist_head;


// spinlock
typedef int gx_spin_lock_t;
#define gx_spin_lock_init(l)
#define gx_spin_lock_bh(l)
#define gx_spin_unlock_bh(l)
#define gx_spin_lock_irq(l)
#define gx_spin_lock(l)
#define gx_spin_unlock(l)
#define gx_spin_lock_irqsave(l, f)
#define gx_spin_unlock_irqrestore(l, f)

// mutex lock
typedef int gx_mutex_t;
extern int gx_mutex_init(int* m);
extern int gx_mutex_lock(int* m);
extern int gx_mutex_unlock(int* m);
extern int gx_mutex_destroy(int* m);

#endif // END GXLOADER_OS

/****************************************************************/
struct gx_meminfo {
#define NR_BANKS_MAX   (4)
	int nr_banks;

	struct gx_membank {
		unsigned long start;
		unsigned long size;
		int node;
	}bank[NR_BANKS_MAX];
};

typedef struct {
	unsigned char *key;
	unsigned int key_len;
	unsigned char *input;
	unsigned int input_len;
	unsigned char *output;
	unsigned char *cw_even;
	unsigned int cw_even_len;
	unsigned char *cw_odd;
	unsigned int cw_odd_len;
	unsigned int arithmetic;
	unsigned int ciphermode;
	unsigned int decryptsel;
} gx_mtc_info;

#define gx_meminfo_get(void)      gx_hole_info_get(void)
#define gx_fbinfo_get(void)       gx_fb_info_get(void)

//reg
#define gx_ioread32(addr)          (*(volatile int *)(addr))
#define gx_iowrite32(value, addr)  (*(volatile int *)(addr)=(value))
#define gx_clear_bit(nr, addr)     (*(volatile unsigned int *)addr) &= ~(1<<(nr))
#define gx_set_bit(nr, addr)       (*(volatile unsigned int *)addr) |= 1<<(nr)
#define gx_test_bit(nr, addr)      test_bit(nr,(const volatile long unsigned int *)addr)

// string
#define gx_memcpy                 memcpy
#define gx_memset(dest,v,len)     memset(dest,v,len)
#define gx_memcmp(dest,src,len)   memcmp(dest,src,len)
#define gx_strncpy(dest,src,len)  strncpy(dest,src,len)
#define gx_strcat(dest,src)       strcat(dest,src)
#define gx_strcpy(dest,src)       strcpy(dest,src)
#define gx_strlen(str)            strlen(str)

#ifdef GX_DEBUG
extern void dbgassert(const char *fcn, int line, const char *expr);
#define GXAV_ASSERT(e)           ((e) ? (void) 0 : dbgassert(__FUNCTION__, __LINE__, #e))
#define GXAV_DBGEV(fmt, args...) gx_printf(fmt, ##args)
#define GXAV_DBG(fmt, args...)   gx_printf(fmt, ##args)
#else
#define GXAV_ASSERT(e)           ((void)0)
#define GXAV_DBGEV(fmt, args...) ((void)0)
#define GXAV_DBG(fmt, args...)   ((void)0)
#endif

/************************************************************************************/
extern unsigned int gxcore_chip_probe(void);
extern struct gx_meminfo *gx_hole_info_get(void);
extern struct gx_meminfo_fb *gx_fb_info_get(void);
extern void *gx_sdc_memcpy(void *dst, const void *src, int len);

/* DMA Cache Coherency
 * ===================
 *
 * gx_dcache_inv_range(start, end)
 *
 *      Invalidate (discard) the specified virtual address range.
 *      May not write back any entries.  If 'start' or 'end'
 *      are not cache line aligned, those lines must be written
 *      back.
 *      - start  - virtual start address
 *      - end    - virtual end address
 *
 * gx_dcache_clean_range(start, end)
 *
 *      Clean (write back) the specified virtual address range.
 *      - start  - virtual start address
 *      - end    - virtual end address
 *
 * gx_dcache_flush_range(start, end)
 *
 *      Clean and invalidate the specified virtual address range.
 *      - start  - virtual start address
 *      - end    - virtual end address
 */

#ifndef LINUX_OS
enum dma_data_direction {
	DMA_BIDIRECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
};
#endif


// CACHE
void *kcache_create(const char *, size_t, size_t);
void kcache_destroy(void*);
void *kcache_alloc(void*, size_t);
void kcache_free(void*, void *);

//　不建议直接使用下列三个函数，后续将删除，使用　gx_cache_sync, 与 Linux 一致
extern void gx_dcache_inv_range(unsigned int start, unsigned int end);
extern void gx_dcache_clean_range(unsigned int start, unsigned int end);
extern void gx_dcache_flush_range(unsigned int start, unsigned int end);

extern void gx_cache_sync(const void *start, unsigned int size, int direction);

extern void gx_interrupt_disable(void);
extern void gx_interrupt_enable(void);
extern void gx_interrupt_mask(unsigned int vector);
extern void gx_interrupt_unmask(unsigned int vector);

extern void *gx_realloc(void *mem_address, unsigned int old_size, unsigned int new_size);

extern unsigned char *gx_page_malloc(unsigned long size);
extern void gx_page_free(unsigned char * p, unsigned long size);

extern int gx_copy_to_user  (void *to, const void *from, unsigned int n);
extern int gx_copy_from_user(void *to, const void *from, unsigned int n);

extern int gx_wait_event(void *module, unsigned int event_mask, int timeout_us);
extern int gx_wake_event(void *module, unsigned int event);

struct gx_i2c_msg {
	unsigned short addr;
	unsigned short flags;
#define GX_I2C_M_TEN          0x0010
#define GX_I2C_M_RD           0x0001
#define GX_I2C_M_NOSTART      0x4000
#define GX_I2C_M_REV_DIR_ADDR 0x2000
#define GX_I2C_M_IGNORE_NAK   0x1000
#define GX_I2C_M_NO_RD_ACK    0x0800
#define GX_I2C_M_RECV_LEN     0x0400
	unsigned short len;
	unsigned char *buf;
};

extern void *gx_i2c_open(unsigned int id);
extern int gx_i2c_set(void *dev, unsigned int busid, unsigned int chip_addr, unsigned int address_width, int send_noack, int send_stop);
extern int gx_i2c_tx(void *dev, unsigned int reg_address, const unsigned char *tx_data, unsigned int count);
extern int gx_i2c_rx(void *dev, unsigned int reg_address, unsigned char *rx_data, unsigned int count);
extern int gx_i2c_transfer(void *dev, struct gx_i2c_msg *msgs, int num);
extern int gx_i2c_close(void *dev);
extern int gx_i2c_clk_conf(void *dev, unsigned int clk_value);

extern unsigned long long gx_tick_start(int timeout_ms);
extern int gx_tick_end(unsigned long long ms);

extern int gx_thread_create(const char *thread_name, gx_thread_id *thread_id,
		void(*entry_func)(void *), void *arg,
		void *stack_base,
		unsigned int stack_size,
		unsigned int priority,
		gx_thread_info *thread_info);
extern int gx_thread_delete (gx_thread_id thread_id);
extern int gx_thread_should_stop(void);
extern int gx_thread_delay(unsigned int millisecond);

extern int gx_sem_create(gx_sem_id *sem_id, unsigned int sem_init_val);
extern int gx_sem_delete(gx_sem_id *sem_id);
extern int gx_sem_post  (gx_sem_id *sem_id);
extern int gx_sem_wait  (gx_sem_id *sem_id);
extern int gx_sem_wait_timeout (gx_sem_id *sem_id,long timeout);
extern int gx_sem_trywait  (gx_sem_id *sem_id);

extern int gx_queue_create(unsigned int queue_depth, unsigned int data_size);
extern int gx_queue_delete (int queue_id);
extern int gx_queue_get(int queue_id, char *data, unsigned int size, int timeout);
extern int gx_queue_put(int queue_id, char *data, unsigned int size);

extern int gx_alarm_create (unsigned int *handle,void (*alarmfn)(unsigned int,unsigned int),unsigned int millisecond);
extern int gx_alarm_delete (unsigned int *handle);
extern int gx_alarm_enable (unsigned int *handle);
extern int gx_alarm_disable(unsigned int *handle);

extern unsigned long long gx_tick_start(int timeout_ms);
extern int gx_tick_end(unsigned long long ms);
extern unsigned long long gx_current_tick(void);

extern int gx_otp_read(unsigned char *buf, int start_offset, int len);
extern int gx_gpio_setlevel(unsigned long gpio, unsigned long value) ;

extern unsigned int gx_uncached_map(unsigned int addr);
extern unsigned int gx_cached_map(unsigned int addr);

#ifdef MEMORY_DEBUG

#ifdef LINUX_OS
void *gxav_malloc_debug(const char *file, int line, size_t size);
void *gxav_mallocz_debug(const char *file, int line, size_t size);
void  gxav_free_debug(const char *file, int line, void *ptr);
void  gxav_memory_show_debug(int nofree_only);
void  gxav_memory_check_debug(void);

#define gx_malloc(size)              gxav_malloc_debug(__FILE__, __LINE__, size)
#define gx_mallocz(size)             gxav_mallocz_debug(__FILE__, __LINE__, size)
#define gx_free(ptr)                 gxav_free_debug(__FILE__, __LINE__, ptr)
#define gx_memory_check()            gxav_memory_check_debug()
#define gx_memory_show(stat)         gxav_memory_show_debug(stat)
#define gx_vmalloc(size)             _vmalloc(size)
#define gx_vfree(ptr, size)          _vfree(ptr)
#endif

#ifdef ECOS_OS
void *gxav_malloc_debug(const char *file, int line, size_t size);
void *gxav_mallocz_debug(const char *file, int line, size_t size);
void  gxav_free_debug(const char *file, int line, void *ptr);
void  gxav_memory_show_debug(int nofree_only);
void  gxav_memory_check_debug(void);

#define gx_malloc(size)              gxav_malloc_debug(__FILE__, __LINE__, size)
#define gx_mallocz(size)             gxav_mallocz_debug(__FILE__, __LINE__, size)
#define gx_free(ptr)                 gxav_free_debug(__FILE__, __LINE__, ptr)
#define gx_memory_check()            gxav_memory_check_debug()
#define gx_memory_show(stat)         gxav_memory_show_debug(stat)
#define gx_vmalloc(size)             gx_malloc(size)
#define gx_vfree(ptr, size)          gx_free(ptr)
#endif

#ifdef GXLOADER_OS
void *gxav_malloc_debug(const char *file, int line, size_t size);
void *gxav_mallocz_debug(const char *file, int line, size_t size);
void  gxav_free_debug(const char *file, int line, void *ptr);
void  gxav_memory_show_debug(int nofree_only);
void  gxav_memory_check_debug(void);

#define gx_malloc(size)              gxav_malloc_debug(__FILE__, __LINE__, size)
#define gx_mallocz(size)             gxav_mallocz_debug(__FILE__, __LINE__, size)
#define gx_free(ptr)                 gxav_free_debug(__FILE__, __LINE__, ptr)
#define gx_memory_check()            gxav_memory_check_debug()
#define gx_memory_show(stat)         gxav_memory_show_debug(stat)
#define gx_vmalloc(size)             gx_malloc(size)
#define gx_vfree(ptr, size)          gx_free(ptr)
#endif

#else

void *gxav_malloc_release(size_t size);
void *gxav_mallocz_release(size_t size);
void  gxav_free_release(void *ptr);

#define gx_malloc(size)              gxav_malloc_release(size)
#define gx_mallocz(size)             gxav_mallocz_release(size)
#define gx_free(ptr)                 gxav_free_release(ptr)
#define gx_memory_check()
#define gx_memory_show(stat)
#define gx_vmalloc(size)             _vmalloc(size)
#define gx_vfree(ptr, size)          _vfree(ptr)

#endif

/*******************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __KERNELCALLS_H__

