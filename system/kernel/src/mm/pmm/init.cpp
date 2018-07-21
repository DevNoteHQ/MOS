
#include "init.hpp"

namespace PMM
{
	uint8_t *LastAllocAddress1G;

	Allocator Alloc1G(3);
	Allocator Alloc2M(2);
	Allocator Alloc4K(1);

	void *NextAllocator1G()
	{
		//TODO: Get the actual last address
		LastAllocAddress1G = 0xFFFFFFFF;
		return 0x0;
	}

	void Init()
	{

	}

	void InitFree()
	{

	}
}