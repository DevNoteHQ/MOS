
#include "init.hpp"
#include "heap.hpp"

namespace Heap
{
	void Init()
	{
		InitHeap = (HeapDynHeader *) &_end; //Reserves Memory for Heap.
		InitHeap->Next = 0;
		HeapStackPointer *Stack = (HeapStackPointer *) &InitHeap->Stack[0];
		uint64_t HeapEnd = ((uint64_t) InitHeap) + HEAP_SIZE * 8;
		uint64_t Rest = HeapEnd % (HEAP_SIZE * 8);
		HeapEnd += (HEAP_SIZE * 8) - Rest - 1;
		uint64_t Size = HeapEnd - ((uint64_t) InitHeap) + 1;
		memset(InitHeap, 0, Size);
		InitHeap->End = (uint8_t *) HeapEnd; //Points to the end of the Heap.

		Stack[0].First = (HeapElement *)(&Stack[STACK_SIZE / 2]); //Always points to the highest, not allocated Memory Address.
	}
}