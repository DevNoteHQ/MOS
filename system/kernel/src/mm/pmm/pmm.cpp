
#include "pmm.hpp"

namespace PMM
{
	uint8_t *LastAllocAddress1G;

	Allocator Alloc4K(0, 0x1000, NextAllocator4K);
	Allocator Alloc2M(1, 0x200000, NextAllocator2M);
	Allocator Alloc1G(2, 0x40000000, NextAllocator1G);
	
	Allocator::Allocator(uint8_t AllocIndex, uint32_t AllocSize, void (*NextAlloc)())
	{
		this->AllocIndex = AllocIndex;
		this->AllocSize = AllocSize;
		this->End = 0x0;
		this->Pointer = 0x0;
		this->FreeStart = 0x0;
		this->FreePointer = 0x0;
		this->FreeEnd = 0x0;
		this->NextAlloc = NextAlloc;
	}

	void *Allocator::Alloc()
	{
		void* Address;
		if (this->FreePointer == this->FreeStart)
		{
			Address = this->Pointer;
			if (this->Pointer >= this->End)
			{
				NextAlloc[this->AllocIndex]();
			}
			else
			{
				this->Pointer += this->AllocSize;
			}
		}
		else
		{
			Address = *(this->FreePointer - 0x8);
			this->FreePointer -= 0x8;
		}
		return Address;
	}

	void Allocator::Free(void *Address)
	{
		if (this->FreeStart == 0x0)
		{
			//this->FreeStart = VMM::Alloc4K(Pool);
			//this->FreePointer = this->FreeStart;
			//this->FreeEnd = this->FreePointer + 511 * 4096;
		}
		if (this->FreePointer >= this->FreeEnd)
		{
			//this->FreePointer = VMM::Alloc4K(Pool);
			//this->FreeEnd = this->FreePointer + 511 * 4096;
		}
		*(this->FreePointer) = Address;
		this->FreePointer += 0x8;
	}
	
	void Init()
	{

	}

	void NextAllocator4K()
	{
		Alloc4K.Pointer = Alloc2M.Alloc();
		Alloc4K.End = (Alloc4K.Pointer + 511 * Alloc4K.AllocSize);
	}

	void NextAllocator2M()
	{
		Alloc2M.Pointer = Alloc1G.Alloc();
		Alloc2M.End = (Alloc2M.Pointer + 511 * Alloc2M.AllocSize);
	}

	void NextAllocator1G()
	{
		if (Alloc1G.End != 0x0)
		{
			Alloc1G.Pointer = 0x0;
			//TODO: Get the actual last address
			Alloc1G.End = (Alloc1G.Pointer + 3 * Alloc1G.AllocSize);
		}
		else
		{
			//ALLERT!
		}
	}
}