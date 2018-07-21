
#include "pmm.hpp"

namespace PMM
{
	uint8_t *LastAllocAddress1G;

	void *NextAllocator1G()
	{
		//TODO: Get the actual last address
		LastAllocAddress1G = 0xFFFFFFFF;
		return 0x0;
	}

	Allocator::Allocator(uint8_t AllocSize)
	{
		this->AllocSize = AllocSize;
		this->NextAlloc = &Allocator::Alloc;
	}

	void *Allocator::Alloc()
	{
		switch (AllocSize)
		{
		case 1: case 2:
			(this->*(this->NextAlloc))();
			break;
		case 3:
			NextAllocator1G();
			break;
		default:
			//abort
			break;
		}
	}

	void Allocator::Free(void *Addrress)
	{

	}

	void Allocator::InitFree()
	{
		
	}
}