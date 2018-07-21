
#ifndef MM_PMM_INIT_HPP
#define MM_PMM_INIT_HPP

#include "pmm.hpp"

namespace PMM
{
	extern Allocator Alloc1G;
	extern Allocator Alloc2M;
	extern Allocator Alloc4K;

	void *NextAllocator1G();
	void Init();
}

#endif