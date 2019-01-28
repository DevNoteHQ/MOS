
#ifndef MM_HEAP_HEAP_HPP
#define MM_HEAP_HEAP_HPP

#define HEAP_SIZE 262144 //8-Bytes
#define FREE_SIZE 16 //16-Bytes

#define HEAP_ADDRESS 0xFFFFFE8000000000

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
	} HeapDynFreePointer;

	typedef struct
	{
		uint64_t *Next;
		uint64_t *End;
	} HeapStaHeader;

	typedef struct HeapDynHeader
	{
		uint8_t *End;
		HeapDynFreePointer Free[FREE_SIZE];
	} HeapDynHeader;

	extern HeapDynHeader *InitHeap;

	void Init();
	void KernelCreate(uint32_t size, HeapDynHeader *Header);
	void KernelCreate(uint32_t size, HeapStaHeader *Header);

	void *Alloc(uint32_t size);
	void *Alloc(uint32_t size, HeapDynHeader *Header);
	void *Alloc(uint32_t size, HeapStaHeader *Header);
	void Free(void *addr);
	void Free(void *addr, HeapDynHeader *Header);
	void Free(void *addr, HeapStaHeader *Header);
}

#endif