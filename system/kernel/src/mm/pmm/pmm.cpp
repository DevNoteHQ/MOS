
#include "pmm.hpp"

namespace PMM
{
	Allocator::Allocator(uint8_t AllocSize)
	{
		this->AllocSize = AllocSize;
		this->NextAlloc = &Allocator::Alloc;
	}

	void *Allocator::Alloc()
	{
		if (AllocSize != 3)
		{
			(this->*(this->NextAlloc))();
		}
	}

	void Allocator::Free(void *Addrress)
	{

	}

	void Allocator::InitFree()
	{
		
	}
}