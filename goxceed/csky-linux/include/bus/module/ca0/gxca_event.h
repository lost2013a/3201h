#ifndef __GXCA_EVENT_H__
#define __GXCA_EVENT_H__

__BEGIN_DECLS

int GxCA_OnEvent(int key, const char* name, void* buf, size_t size);
int GxCA_OnEventNoWait(int key, const char* name, void* buf, size_t size);

__END_DECLS

#endif /*__GXCA_EVENT_H__*/
