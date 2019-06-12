
#ifndef __GXAV_DESCRAMBLER_PROPERTYTYPES_H__
#define __GXAV_DESCRAMBLER_PROPERTYTYPES_H__

#define  DESC_ALLOC_BY_ORDER     (1)//alloc id from empty id
#define  DESC_ALLOC_BY_SPECAIL   (2)//alloc id from user

typedef struct {
	int m_flag;
	int m_desc_id;
} GxDescrambler_Desc;

typedef struct {
	int m_desc_id;
	int m_slot_id;
	int m_is_link;
} GxDescrambler_Link;

typedef struct {
	int m_desc_count;
	int m_desc_status;
} GxDescrambler_Status;

#endif /* __GXAV_DESCRAMBLER_PROPERTYTYPES_H__ */
