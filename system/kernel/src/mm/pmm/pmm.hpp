
#ifndef MM_PMM_PMM_HPP
#define MM_PMM_PMM_HPP

namespace PMM
{
	class Allocator
	{
	private:
		void *(Allocator::*NextAlloc)(void);
		void *FreeFirst;
		void *FreeLast;
		void *FreeEnd;
		uint8_t AllocSize;
	public:
		Allocator(uint8_t AllocSize);
		void *Alloc();
		void Free(void *Address);
		void InitFree();
	};
}

#endif