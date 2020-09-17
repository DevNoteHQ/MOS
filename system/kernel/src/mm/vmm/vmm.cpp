
#include "vmm.hpp"
#include <mm/pmm/pmm.hpp>

//TODO: Finish second GetAddress
//TODO: Add Free, add UpdateNextAddress, test Alloc-Next-Methods

//Idea: On loading new Process, switch to kernel, map the kernel, then switch to new Table and VMM::Alloc the space required

namespace VMM {
	KernelTable Kernel;

	Table::Table() {
		uint64_t PhysicalAddress = PMM::Alloc4K.Alloc();
		this->PML4T = PhysicalAddress + HVMA;
		Map4K(this->PML4T, PhysicalAddress, (PG_PRESENT | PG_WRITABLE));
		memset(PML4T, 0, 4096);
		this->PML4T[511] = PhysicalAddress | PG_PRESENT | PG_WRITABLE;
		uint64_t *KernelEntry = GetAddress(511, 511, 511, 510);
		this->PML4T[510] = *KernelEntry;
	}

	Table::~Table() {
		//Free all Tables
	}

	KernelTable::KernelTable() {

	}

	KernelTable::~KernelTable() {

	}

	void KernelTable::InitKernelTable() {
		uint64_t PhysicalAddress = PMM::Alloc4K.Alloc();
		this->PML4T = PhysicalAddress + HVMA; //Map it later
		memset(PML4T, 0, 4096);
		this->PML4T[511] = PhysicalAddress | PG_PRESENT | PG_WRITABLE;
	}

	void KernelTable::Check(uint64_t *Entry, uint64_t Bitmap) {
		if ((*Entry == 0) || (((*Entry) & 0x1) == 0)) {
			*Entry = PMM::Alloc4K.Alloc() | Bitmap;
			void *NextEntry = (uint64_t)Entry << 9;
			memset(NextEntry, 0, 4096);
		}
	}

	void KernelTable::Check(uint64_t *Entry, uint64_t PhysAddress, uint64_t Bitmap) {
		if ((*Entry == 0) || (((*Entry) & 0x1) == 0)) {
			*Entry = PhysAddress | Bitmap;
		} else {
			//Throw error
		}
	}

	void *KernelTable::Alloc(uint64_t Size, uint64_t Bitmap) {
		void *Addr = 0;
		//Alloc contiguous memory. 4K fist, then 2M, then 1G, the rest if needed 2M
	}

	void KernelTable::Alloc(uint64_t Size, void *Address, uint64_t Bitmap) {

	}

	void KernelTable::Map(uint64_t Size, void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {

	}

	void *KernelTable::Alloc4K(uint64_t Bitmap) {
		KernelTable::Alloc4K(this->Next4K, Bitmap);
		if (this->Next4K >= this->End4K) {
			if (this->Next2M >= this->End2M) {
				if (this->Next1G >= this->End1G) {
					//Unlikely to happen
					if (this->Next512G >= this->End512G) {
						//Throw error
					} else {
						this->Next1G = this->Next512G;
						this->End1G = this->Next1G + Size512G8B;
						this->Next512G += Size512G8B;
					}
				}
				this->Next2M = this->Next1G;
				this->End2M = this->Next2M + Size1G8B;
				this->Next1G += Size1G8B;
			}
			this->Next4K = this->Next2M;
			this->End4K = this->Next4K + Size2M8B;
			this->Next2M += Size2M8B;
		}
		uint64_t *Addr = this->Next4K;
		this->Next4K += Size4K8B;
		return Addr;
	}

	void KernelTable::Alloc4K(void *Address, uint64_t Bitmap) {
		KernelTable::Map4K(Address, PMM::Alloc4K.Alloc(), Bitmap);
	}

	void KernelTable::Map4K(void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {
		AddressIndexes AI;
		AI = GetAddress(VirtAddress);

		uint64_t *PML4 = GetAddress(511, 511, 511, AI.PML4);
		Check(PML4, Bitmap);

		uint64_t *PDPT = GetAddress(511, 511, AI.PML4, AI.PDPT);
		Check(PDPT, Bitmap);

		uint64_t *PD = GetAddress(511, AI.PML4, AI.PDPT, AI.PD);
		Check(PD, Bitmap);

		uint64_t *PT = GetAddress(AI.PML4, AI.PDPT, AI.PD, AI.PT);
		Check(PT, PhysAddress, Bitmap);
	}

	void *KernelTable::Alloc2M(uint64_t Bitmap) {
		KernelTable::Alloc2M(this->Next2M, Bitmap);
		if (this->Next2M >= this->End2M) {
			if (this->Next1G >= this->End1G) {
				//Unlikely to happen
				if (this->Next512G >= this->End512G) {
					//Throw error
				} else {
					this->Next1G = this->Next512G;
					this->End1G = this->Next1G + Size512G8B;
					this->Next512G += Size512G8B;
				}
			}
			this->Next2M = this->Next1G;
			this->End2M = this->Next2M + Size1G8B;
			this->Next1G += Size1G8B;
		}
		uint64_t *Addr = this->Next2M;
		this->Next2M += Size2M8B;
		return Addr;
	}

	void KernelTable::Alloc2M(void *Address, uint64_t Bitmap) {
		KernelTable::Map2M(Address, PMM::Alloc2M.Alloc(), Bitmap);
	}

	void KernelTable::Map2M(void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {
		AddressIndexes AI;
		AI = GetAddress(VirtAddress);

		uint64_t *PML4 = GetAddress(511, 511, 511, AI.PML4);
		Check(PML4, Bitmap);

		uint64_t *PDPT = GetAddress(511, 511, AI.PML4, AI.PDPT);
		Check(PDPT, Bitmap);

		uint64_t *PD = GetAddress(511, AI.PML4, AI.PDPT, AI.PD);
		Check(PD, PhysAddress, (Bitmap | PG_BIG));
	}

	void *KernelTable::Alloc1G(uint64_t Bitmap) {
		KernelTable::Alloc1G(this->Next1G, Bitmap);
		if (this->Next1G >= this->End1G) {
			//Unlikely to happen
			if (this->Next512G >= this->End512G) {
				//Throw error
			} else {
				this->Next1G = this->Next512G;
				this->End1G = this->Next1G + Size512G8B;
				this->Next512G += Size512G8B;
			}
		}
		uint64_t *Addr = this->Next1G;
		this->Next1G += Size1G8B;
		return Addr;
	}

	void KernelTable::Alloc1G(void *Address, uint64_t Bitmap) {
		KernelTable::Map1G(Address, PMM::Alloc1G.Alloc(), Bitmap);
	}

	void KernelTable::Map1G(void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {
		AddressIndexes AI;
		AI = GetAddress(VirtAddress);

		uint64_t *PML4 = GetAddress(511, 511, 511, AI.PML4);
		Check(PML4, Bitmap);

		uint64_t *PDPT = GetAddress(511, 511, AI.PML4, AI.PDPT);
		Check(PDPT, PhysAddress, (Bitmap | PG_BIG));
	}

	void KernelTable::LoadTable() {
		setCR3((uint64_t)&this->PML4T[0] - HVMA);
	}

	void *GetAddress(uint16_t PML4, uint16_t PDPT, uint16_t PD, uint16_t PT) {
		return (uint64_t *)(ADDRESS_ADDITIVE | (511 << 39) | (PML4 << 30) | (PDPT << 21) | (PD << 12) | (PT << 3));
	}

	AddressIndexes GetAddress(void *VirtAddress) {
		AddressIndexes AI;
		AI.PML4 = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		AI.PDPT = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		AI.PD = (((uint64_t)VirtAddress) >> 21) & 0x1FF;
		AI.PT = (((uint64_t)VirtAddress) >> 12) & 0x1FF;
		return AI;
	}
}