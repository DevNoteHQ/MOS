
#ifndef MM_PMM_PMM_HPP
#define MM_PMM_PMM_HPP

namespace PMM
{
	class Allocator
	{
	private:
		uint8_t AllocIndex;
	public:
		uint8_t *Pointer;
		uint8_t *End;
		uint8_t *FreeStart;
		uint8_t **FreePointer;
		uint8_t *FreeEnd;
		uint32_t AllocSize;

		void (*NextAlloc)();

		Allocator(uint8_t AllocIndex, uint32_t AllocSize, void (*NextAlloc)());
		void *Alloc();
		void Free(void *Address);
	};
	
	void Init();
	void NextAllocator4K();
	void NextAllocator2M();
	void NextAllocator1G();

	extern Allocator Alloc1G;
	extern Allocator Alloc2M;
	extern Allocator Alloc4K;
}

#endif