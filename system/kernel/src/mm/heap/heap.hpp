
#ifndef MM_HEAP_HEAP_HPP
#define MM_HEAP_HEAP_HPP

#define HEAP_SIZE 262144 //8-Bytes
#define FREE_SIZE 16 //16-Bytes

#define HEAP_ADDRESS 0xFFFFFF0040000000

#define ALIGN2M 2097152 //Bytes

namespace Heap
{
	typedef struct
	{
		int Next; //Only for free Elements
		uint32_t Size;
	} HeapElement;

	typedef struct
	{
		HeapElement *First;
		HeapElement *Last;
	} HeapFreePointer;

	typedef struct HeapHeader
	{
		uint8_t *End;
		HeapFreePointer Free[FREE_SIZE];
	} HeapHeader;

	extern HeapHeader *InitHeap;

	void Init();

	void *Alloc(uint32_t size);
	void *Alloc(uint32_t size, HeapHeader *Header);
	void Free(void *addr);
	void Free(void *addr, HeapHeader *Header);
}

#endif