
#ifndef MM_HEAP_HEAP_HPP
#define MM_HEAP_HEAP_HPP

namespace Heap
{
	void *Alloc(uint64_t size);
	void *Alloc(uint64_t size, uint32_t align);
	void Free(void *addr);
}

#endif