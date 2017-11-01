
#ifndef MM_HEAP_HEAP_HPP
#define MM_HEAP_HEAP_HPP

#define HEAP_SIZE 262144 //8-Bytes
#define STACK_SIZE 32 //8-Bytes

namespace Heap
{
	typedef struct HeapElement
	{
		struct HeapElement *next; //Only for free Elements
		uint64_t size;
	} HeapElement;

	typedef struct
	{
		HeapElement *First;
		HeapElement *Last;
	} HeapStackPointer;

	typedef struct
	{
		uint64_t *End;
		HeapStackPointer *Stack; //General Purpose
	} HeapDynHeader;

	typedef struct
	{
		uint64_t *End;
		uint64_t *Bitmap;
	} HeapStaHeader;

	extern HeapDynHeader *InitHeap;

	HeapDynHeader *KernelCreate(uint64_t size);

	void *Alloc(uint64_t size);
	void *Alloc(uint64_t size, HeapDynHeader *Header);
	void Free(void *addr);
}

#endif