
#include "init.hpp"
#include "heap.hpp"

namespace Heap
{
	void Init()
	{
		InitHeap = (HeapDynHeader *) &_end; //Reserves Memory for Heap.
		HeapStackPointer *Stack = (HeapStackPointer *)(InitHeap + 1); //Reserves Memory for pseudo-stack.
		uint64_t HeapEnd = ((uint64_t) InitHeap) + HEAP_SIZE * 8;
		uint64_t Rest = HeapEnd % (HEAP_SIZE * 8);
		HeapEnd += (HEAP_SIZE * 8) - Rest - 1;
		uint64_t Size = HeapEnd - ((uint64_t) InitHeap) + 1;
		memset(InitHeap, 0, Size);
		InitHeap->End = (uint64_t *) HeapEnd; //Points to the end of the Heap.
		InitHeap->Stack = Stack; //Points to the "Stack".

		Stack[0].First = (HeapElement *)(&Stack[STACK_SIZE / 2]); //Always points to the highest, not allocated Memory Address.
	}
}