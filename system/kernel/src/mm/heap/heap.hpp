
#ifndef MM_HEAP_HEAP_HPP
#define MM_HEAP_HEAP_HPP

namespace Heap
{
	typedef struct
	{
		void *end;
		uint64_t gp; //General Purpose
	} __attribute__((__packed__)) HeapHeader;

	typedef struct
	{
		void *prev;
		void *next;
	} __attribute__((__packed__)) HeapElement;

	HeapHeader *KernelCreate(uint64_t size);
	HeapHeader *KernelCreate(uint64_t size, void *addr);

	HeapHeader *Create(uint64_t size);

	void *Alloc(uint64_t size);
	void *Alloc(uint64_t size, uint32_t align);
	void Free(void *addr);
}

#endif