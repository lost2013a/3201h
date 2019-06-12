
#ifndef MINIDB_HPP
#define MINIDB_HPP

#include <stdint.h>

namespace GoXceed {

class ICursor {
public:
	virtual ~ICursor() {}
	virtual void *GetRaw(uint32_t *size) = 0;
	virtual bool Next() = 0;
	virtual bool First() = 0;
	virtual bool Eof() = 0;
	virtual uint32_t Key() = 0;
};

class IDB {
public:
	virtual ~IDB() {};
	static IDB *New();
	static void Delete(IDB *db);

	virtual void Sync() = 0;
	virtual uint32_t Count() = 0;
	virtual bool Clear() = 0;
	virtual bool Open(const char *db_name) = 0;
	virtual void Close() = 0;
	virtual void *Get(const uint32_t key, uint32_t *size) = 0;
	virtual bool Set(const uint32_t key, const void *value, int size) = 0;
	virtual bool Remove(const uint32_t key) = 0;
	virtual ICursor *CreateCursor() = 0;
};

}

#endif

