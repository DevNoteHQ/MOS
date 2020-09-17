
#ifndef MM_PMM_PMM_HPP
#define MM_PMM_PMM_HPP

namespace PMM {

	typedef struct StackPointer {
		StackPointer *previousStack;
	}
	class Allocator {
	private:
		uint8_t AllocIndex;
		StackPointer *FreeStart;
		uint64_t *FreePointer;
		uint64_t *FreeEnd;
	public:
		uint8_t *Pointer;
		uint8_t *End;
		uint32_t AllocSize;

		void (*NextAlloc)();

		Allocator(uint8_t AllocIndex, uint32_t AllocSize, void (*NextAlloc)());
		uint64_t Alloc();
		void Free(uint64_t Address);
	};
	
	void NextAllocator4K();
	void NextAllocator2M();
	void NextAllocator1G();

	extern Allocator Alloc1G;
	extern Allocator Alloc2M;
	extern Allocator Alloc4K;
}

#endif