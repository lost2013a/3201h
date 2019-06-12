#ifndef _AVCORE_H_
#define _AVCORE_H_

#include "kernelcalls.h"
#include "gxav_common.h"
#include "sdc_cache.h"

#define GXAV_MAX_MODULE          16
#define GXAV_MAX_IRQ             64
#define GXAV_MAX_CHANNEL         32 //depend on the bits of unsigned int type
#define GXAV_MAX_IO_CHANNEL		 256
#define GXAV_MAX_HANDLE          64

#define gxav_module_getdev(module)  \
	((module && (module)->inode) ? (module)->inode->dev : NULL)
#define gxav_module_getops(module)  \
	((module && (module)->inode) ? (module)->inode->interface : NULL)
#define gxav_handle_getdev(handle) \
	((handle && (handle)->module && (handle)->module->inode) ? (handle)->module->inode->dev : NULL)
#define gxav_device_getmod(dev, module_id) \
	(((module_id) >=0 && (module_id < GXAV_MAX_HANDLE)) ? (dev)->modules_handle[module_id]->module : NULL)

#define gxav_module_inc(module) do { module->refcount++; module->inode->refcount++; } while(0);
#define gxav_module_dec(module) do { module->refcount--; module->inode->refcount--; } while(0);

#ifdef __cplusplus
extern "C"{
#endif

struct gxav_module_ops;
struct gxav_device_ops;
struct gxav_channel_ops;
struct gxav_module;
struct gxav_device;

enum gxav_irq_mode {
	GXAV_IRQ_FAST    = (1<<0),
	GXAV_IRQ_NORMAL
};

enum gxav_irq_step {
	GXAV_ISR_ENTRY  = (0),
	GXAV_DSR_ENTRY  = (1)
};

struct gxav_module_inode {
	struct gxav_module         **module;
	int                        count;
	int                        event_status;
	struct gxav_device         *dev;
	struct gxav_module_ops     *interface;
	unsigned int               event_mask;
	void                       *priv;
	void                       *wq;
	void                       *lock;
	unsigned int               refcount;
};

struct gxav_module {
	enum gxav_module_type      module_type;
	int                        module_id;
	int                        sub;
	unsigned int               event_mask;
	struct gxav_channel        *in_channel[GXAV_MAX_IO_CHANNEL];
	struct gxav_channel        *out_channel[GXAV_MAX_IO_CHANNEL];

	struct gxav_module_inode   *inode;
	unsigned int               refcount;
};

struct gxav_module_handle {
	int                        handle;
	struct gxav_module         *module;
};

typedef struct gxav_module_inode *(*irq_callback) (struct gxav_module_inode *inode, int irq);

struct irq_handler {
	struct gxav_module_inode   *inode;
	irq_callback               irq_func;
	int                        irq_mode;
};

struct gxav_irq {
	struct irq_handler         *irq_entry;
	int                        irq_count;
	int                        active;
};

struct gxav_device {
	int                        id;
	int                        active;

	int                        sdc_module_id;
	struct gxav_module_inode   modules_inode[GXAV_MAX_MODULE];
	struct gxav_module_handle  *modules_handle[GXAV_MAX_HANDLE];
	struct gxav_irq            irq_list[GXAV_MAX_IRQ];

	struct gxav_device_ops     *interface;
	struct gxav_device         *next, *prev;

	void                       *priv;
	int                        refcount;

	char*                      profile;

	gx_spin_lock_t             spin_lock;
};

struct gxav_channel {
	unsigned int               in;
	unsigned int               in_pos;

	unsigned int               out;
	unsigned int               out_pos;

	struct gxav_cache          cache_r;
	struct gxav_cache          cache_w;
	unsigned int               cache_size;

	unsigned int               size;
	unsigned char              *buffer;
	unsigned int               start_addr;
	unsigned int               last_start_addr;
	unsigned int               ptstimes; // pts sync used

	signed char                flag;
	signed char                channel_id; // 0 - 63
	signed char                pts_channel_id;

	unsigned int               almost_empty_gate;
	unsigned int               almost_full_gate;

	GxAvChannelType            type;

	unsigned char              *pts_buffer;
	unsigned int               pts_size;
	unsigned int               pts_pos;

	int                        inpin_id;
	int                        (*incallback)(unsigned int id,unsigned int len, unsigned int overflow, void *data);
	void                       *indata;

	int                        outpin_id;
	int                        (*outcallback)(unsigned int id,unsigned int len, unsigned int underflow, void *data);
	void                       *outdata;

	int                        malloced;
	struct gxav_device*        dev;
};

struct gxav_sdc {
	struct gxav_channel        channel[GXAV_MAX_CHANNEL];
	unsigned int               sdc_status;
	unsigned int               channel_status;
};

struct gxav_device_ops {
	int (*init)         (struct gxav_device *dev);
	int (*cleanup)      (struct gxav_device *dev);
	int (*open)         (struct gxav_device *dev);
	int (*close)        (struct gxav_device *dev);
	int (*set_property) (struct gxav_device *dev, int module_id, int property_id, void *property, int size);
	int (*get_property) (struct gxav_device *dev, int module_id, int property_id, void *property, int size);
	int (*write_ctrlinfo)(struct gxav_device *dev, int module_id, void *ctrl_info, int ctrl_size);
};

struct gxav_module_ops {
	enum gxav_module_type module_type;
	int                   irqs[GXAV_MAX_IRQ];
	int                   irq_flags[GXAV_MAX_IRQ];
	unsigned int          count;
	unsigned int          event_mask;
	void*                 priv;

	int (*init)           (struct gxav_device *dev, struct gxav_module_inode *inode);
	int (*cleanup)        (struct gxav_device *dev, struct gxav_module_inode *inode);
	int (*open)           (struct gxav_module *moudle);
	int (*close)          (struct gxav_module *moudle);

	int (*set_property)   (struct gxav_module *module, int property_id, void *property, int size);
	int (*get_property)   (struct gxav_module *module, int property_id, void *property, int size);
	int (*write_ctrlinfo) (struct gxav_module *module, void *ctrl_info, int ctrl_size);
	struct gxav_module_inode *(*interrupt[GXAV_MAX_IRQ])(struct gxav_module_inode *inode, int irq);
};

struct gxav_channel_ops {
	int ( *apply)        ( struct gxav_channel *channel, GxAvChannelType type);
	int ( *free)         ( struct gxav_channel *channel, GxAvChannelType type);
	int ( *gate_set)     ( struct gxav_channel *channel, void *info);
	int ( *pts_set)      ( struct gxav_channel *channel, unsigned int start_addr, int pts);
	int ( *inc)          ( struct gxav_channel *channel, int len);
	int ( *dec)          ( struct gxav_channel *channel, int len);
	int ( *length_get)   ( struct gxav_channel *channel);
	int ( *cap_get)      ( struct gxav_channel *channel);
	int ( *freesize_get) ( struct gxav_channel *channel);
	int ( *pts_length)   ( struct gxav_channel *channel);
	int ( *reset)        ( struct gxav_channel *channel);
	int ( *rollback)     ( struct gxav_channel *channel);
	int ( *collation)    ( struct gxav_channel *channel);
};

int chip_register(struct gxav_device *dev);
struct gxav_device *gxav_devices_setup(char* profile);
void gxav_devices_cleanup(void);

int  gxav_device_open                  (struct gxav_device *dev);
int  gxav_device_release_modules       (struct gxav_device *dev);
int  gxav_device_close                 (struct gxav_device *dev);
void gxav_device_spin_lock             (struct gxav_device *dev);
void gxav_device_spin_unlock           (struct gxav_device *dev);
unsigned long gxav_device_spin_lock_irqsave(struct gxav_device *dev);
void gxav_device_spin_unlock_irqrestore(struct gxav_device *dev, unsigned long flag);

struct gxav_module_inode *gxav_device_interrupt_entry(struct gxav_device *dev, int irq, int isr_dsr);

int gxav_module_register         (struct gxav_device *dev, struct gxav_module_ops *module);
int gxav_module_unregister       (struct gxav_device *dev, struct gxav_module_ops *module);
int gxav_module_open             (struct gxav_device *dev, enum  gxav_module_type module_type, int sub);
int gxav_module_close            (struct gxav_device *dev, int module_id);
int gxav_module_inode_set_event  (struct gxav_module_inode *inode, unsigned int event_mask);
int gxav_module_inode_clear_event(struct gxav_module_inode *inode, unsigned int event_mask);
int gxav_module_set_property     (struct gxav_device *dev, int module_id, int property_id, void *property, int size);
int gxav_module_get_property     (struct gxav_device *dev, int module_id, int property_id, void *property, int size);
int gxav_module_write_ctrlinfo   (struct gxav_device *dev, int module_id, void* ctrl_info, int ctrl_size);
int gxav_module_link             (struct gxav_device *dev, int module_id, int dir, int pin_id, struct gxav_channel *channel);
int gxav_module_unlink           (struct gxav_device *dev, int module_id, struct gxav_channel *channel);

struct gxav_channel *gxav_channel_apply(struct gxav_device *dev, void* buffer, unsigned int len, GxAvChannelType type);
int gxav_channel_free            (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_reset           (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_rollback        (struct gxav_device *dev, struct gxav_channel *channel, int size);
int gxav_channel_hw2cache        (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_gate_set        (struct gxav_device *dev, struct gxav_channel *channel, void *info);
int gxav_channel_put             (struct gxav_device *dev, struct gxav_channel *channel, \
                                                   void *(*copy)(void *, const void *, int), \
                                                   unsigned char *data, unsigned int len, int pts);
int gxav_channel_put_pts         (struct gxav_device *dev, struct gxav_channel *channel,int pts);
int gxav_channel_get             (struct gxav_device *dev, struct gxav_channel *channel, \
                                                   void *(*copy)(void *, const void *, int), \
                                                   unsigned char *data, unsigned int len, int peek);
int gxav_channel_id_get          (struct gxav_channel *channel);
int gxav_channel_pts_id_get      (struct gxav_channel *channel);
int gxav_channel_collation       (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_freesize_get    (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_length_get      (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_cap_get         (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_pts_length      (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_flag_get        (struct gxav_device *dev, struct gxav_channel *channel);
int gxav_channel_flag_set        (struct gxav_device *dev, struct gxav_channel *channel, int flag);
int gxav_channel_type_get        (struct gxav_device *dev, struct gxav_channel *channel);
struct gxav_channel *gxav_channel_get_channel(struct gxav_device *dev,unsigned char channel_id);

int gxav_channel_get_phys        (struct gxav_channel *channel, \
                                             unsigned int *start_addr, unsigned int *end_addr, unsigned char *buf_id);

int gxav_channel_get_ptsbuffer   (struct gxav_channel *channel, \
                                             unsigned int *start_addr, unsigned int *end_addr, unsigned char *buf_id);

void gxav_sdc_free_all(struct gxav_module *module);

int  gxav_set_sync_params(GxAvSyncParams *sync);

#ifdef __cplusplus
}
#endif

#endif

