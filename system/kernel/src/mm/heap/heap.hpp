
#ifndef MM_HEAP_HEAP_HPP
#define MM_HEAP_HEAP_HPP

#define HEAP_SIZE 262144 //8-Bytes
#define STACK_SIZE 32 //8-Bytes

namespace Heap
{
	typedef struct HeapDynHeader
	{
		struct HeapDynHeader *Next;
		uint8_t *End;
		uint64_t Stack[STACK_SIZE];
	} HeapDynHeader;

	typedef struct
	{
		int Next; //Only for free Elements
		uint32_t Size;
	} HeapElement;

	typedef struct
	{
		HeapElement *First;
		HeapElement *Last;
	} HeapStackPointer;

	typedef struct
	{
		uint64_t *Next;
		uint64_t *End;
		uint64_t Bitmap;
	} HeapStaHeader;

	extern HeapDynHeader *InitHeap;

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