
#include "pmm.hpp"
#include "../vmm/vmm.hpp"

namespace PMM {
	Allocator Alloc4K(0, 0x1000, &NextAllocator4K);
	Allocator Alloc2M(1, 0x200000, &NextAllocator2M);
	Allocator Alloc1G(2, 0x40000000, &NextAllocator1G);
	
	// TODO: Test Free, complete Free

	Allocator::Allocator(uint8_t AllocIndex, uint32_t AllocSize, void (*NextAlloc)()) {
		this->AllocIndex = AllocIndex;
		this->AllocSize = AllocSize;
		this->End = 0x0;
		this->Pointer = 0x0;
		this->FreeStart = 0x0;
		this->FreePointer = 0x0;
		this->FreeEnd = 0x0;
		this->NextAlloc = NextAlloc;
	}

	uint64_t Allocator::Alloc() {
		uint64_t Address;
		if (this->FreePointer == this->FreeStart) {
			if (this->Pointer >= this->End) {
				NextAlloc();
			}
			Address = this->Pointer;
			this->Pointer += this->AllocSize;
		} else {
			if (this->FreePointer == this->FreeStart) {
				StackPointer *previousStack = this->FreeStart;
				this->FreeStart = this->FreeStart->previousStack;
				Address = *(this->FreePointer - 1);
				this->FreePointer -= 1;
				// VMM::Kernel.Free4K(previousStack);
			} else {
				Address = *(this->FreePointer - 1);
				this->FreePointer -= 1;
			}
		}
		return Address;
	}

	void Allocator::Free(uint64_t Address) {
		if (this->FreePointer >= this->FreeEnd) {
			StackPointer *previousStack = this->FreeStart;
			this->FreeStart = (StackPointer *) VMM::Kernel.Alloc4K(PG_PRESENT | PG_WRITABLE);
			this->FreeStart->previousStack = previousStack;
			this->FreeEnd = ((uint64_t) this->FreePointer) + 4096;
			if (this->FreeStart == 0x0) {
				this->FreeStart = (StackPointer *) this->FreePointer;
			}
		}
		*(this->FreePointer) = Address;
		this->FreePointer += 1;
	}

	void NextAllocator4K() {
		Alloc4K.Pointer = Alloc2M.Alloc();
		Alloc4K.End = (Alloc4K.Pointer + 512 * Alloc4K.AllocSize);
	}

	void NextAllocator2M() {
		Alloc2M.Pointer = Alloc1G.Alloc();
		Alloc2M.End = (Alloc2M.Pointer + 512 * Alloc2M.AllocSize);
	}

	void NextAllocator1G() {
		if (Alloc1G.End != 0x0) {
			Alloc1G.Pointer = 0x0;
			//TODO: Get the actual last address
			/* !!! Temporary !!! */ Alloc1G.End = (Alloc1G.Pointer + 4 * Alloc1G.AllocSize); /* !!! Temporary !!! */
		} else {
			//ALLERT!
		}
	}
}