#ifndef IO_HPP
#define IO_HPP

#include <stdint.h>

struct Data {
	Data() {
		size = 0;
		address = 0;
	}
	uint32_t size;
	uint32_t address;
};

struct MemInfo {
	uint32_t max_size;  // 定义的内存大小
	uint32_t phy_size;  // 实际分配的物理内存大不上
	uint32_t pack_size; // 压缩后的内存大小
};

class IO {
public:
	virtual ~IO() {}

	static IO *NewIO(uint32_t size);

	virtual uint32_t ReadAs(void *buffer, uint32_t len, uint32_t offset) = 0;
	virtual uint32_t WriteAs(void *buffer, uint32_t len, uint32_t offset) = 0;

	virtual Data AllocData(uint32_t size) = 0;
	virtual void FreeData(Data &d) = 0;
	virtual void GetInfo(MemInfo &info) = 0;
};

class Memory {
public:
	Memory(IO *io, Data b);
	~Memory();

	uint8_t *data;
	uint32_t size;
	uint8_t &operator[](int index);
private:
	Data d;
	IO *io;
};

#if 0
static void io_test() {
	IO *io = NewIO(4 * 1024 * 1024);
	Data b[100];

	for (int i =0; i < 100; i++) {
		b[i] = io->AllocData(128);
		Memory d(io, b[i]);
		sprintf((char*)d.data, "0x%x:%d", d.data, d.size);
	}

	for (int i =0; i < 100; i++) {
		Memory d(io, b[i]);
		printf("This: %s\n", d.data);
		for (int i=0; i < d.size; i++)
			printf("%c ", d[i]);
		printf("\n");
		io->FreeData(b[i]);
	}
}
#endif


#endif
