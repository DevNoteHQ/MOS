
#include "vmm.hpp"
#include <mm/pmm/pmm.hpp>
#include <utility/system/info.hpp>
#include <video/console.hpp>

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
		uint64_t *KernelEntry = GetRecursiveTableEntryAddress(511, 511, 511, 510);
		this->PML4T[510] = *KernelEntry;
	}

	Table::~Table() {
		//Free all Tables
	}

	KernelTable::KernelTable() {

	}

	KernelTable::~KernelTable() {

	}

	VMMAddresses KernelTable::updateState() {
		uint16_t filled4KTables = (System::Info::EndAddress - HVMA) / Size2M;
		uint16_t filled2MTables = (System::Info::EndAddress - HVMA) / Size1G;
		uint16_t filled1GTables = (System::Info::EndAddress - HVMA) / Size512G;
		this->Next4K = System::Info::EndAddress + Size4K;
		this->End4K = (uint64_t *)(HVMA + filled4KTables * Size2M + Size2M);
		this->Next2M = (uint64_t *)(HVMA + filled2MTables * Size1G + Size2M);
		this->End2M = (uint64_t *)(HVMA + filled2MTables * Size1G + Size1G);
		this->Next1G = (uint64_t *)(HVMA + filled1GTables * Size512G + Size1G);
		this->End1G = (uint64_t *)(HVMA + filled1GTables * Size512G + Size512G);
		this->Next512G = (uint64_t *)(HVMA + filled1GTables * Size512G + Size512G);
		this->End512G = (uint64_t *)(HVMA + filled1GTables * Size512G + Size512G);
		return { this->Next4K, this->End4K, this->Next2M, this->End2M, this->Next1G, this->End1G, this->Next512G, this->End512G };
	}

	void KernelTable::InitKernelTable() {
		uint64_t PhysicalAddress = PMM::Alloc4K.Alloc();
		this->PML4T = PhysicalAddress + HVMA; //Map it later
		memset(PML4T, 0, 4096);
		this->PML4T[511] = PhysicalAddress | PG_PRESENT | PG_WRITABLE;
	}

	void KernelTable::CreateNewTableEntryIfEntryNotExisting(uint64_t *Entry, uint64_t Bitmap) {
		if ((*Entry == 0) || (((*Entry) & 0x1) == 0)) {
			*Entry = PMM::Alloc4K.Alloc() | Bitmap;
			void *NextEntry = (uint64_t)Entry << 9;
			memset(NextEntry, 0, 4096);
		}
	}

	void KernelTable::AssignPhysicalAddressIfEntryNotExisting(uint64_t *Entry, uint64_t PhysAddress, uint64_t Bitmap) {
		if ((*Entry == 0) || (((*Entry) & 0x1) == 0)) {
			*Entry = PhysAddress | Bitmap;
		} else {
			//Throw error
			Console::WriteLine("Error");
		}
	}

	void KernelTable::Get512GPageFor1GAllocator() {
		//Unlikely to happen
		if (this->Next512G >= this->End512G) {
			//Throw error
			Console::WriteLine("Error");
		} else {
			this->Next1G = this->Next512G;
			this->End1G = this->Next1G + Size512G8B;
			this->Next512G += Size512G8B;
		}
	}

	void KernelTable::Get1GPageFor2MAllocator() {
		if (this->Next1G >= this->End1G) {
			this->Get512GPageFor1GAllocator();
		}
		this->Next2M = this->Next1G;
		this->End2M = this->Next2M + Size1G8B;
		this->Next1G += Size1G8B;
	}

	void KernelTable::Get2MPageFor4KAllocator() {
		if (this->Next2M >= this->End2M) {
			this->Get1GPageFor2MAllocator();
		}
		this->Next4K = this->Next2M;
		this->End4K = this->Next4K + Size2M8B;
		this->Next2M += Size2M8B;
	}

	void *KernelTable::Alloc1G(uint64_t Bitmap) {
		KernelTable::Alloc1G(this->Next1G, Bitmap);
		if (this->Next1G >= this->End1G) {
			this->Get512GPageFor1GAllocator();
		}
		uint64_t *Addr = this->Next1G;
		this->Next1G += Size1G8B;
		return Addr;
	}

	void *KernelTable::Alloc(uint64_t Size, uint64_t Bitmap) {
		uint64_t AvailableSpace4K = (((uint64_t) this->End4K) - (((uint64_t) this->Next4K)));
		uint64_t AvailableSpace2M = (((uint64_t) this->End2M) - (((uint64_t) this->Next2M)));
		uint64_t AvailableSpace1G = (((uint64_t) this->End1G) - (((uint64_t) this->Next1G))) + (((uint64_t) this->End512G) - (((uint64_t) this->Next512G)));

		bool Assign4KAddress = Size >= Size4K && AvailableSpace4K > 0;
		AllocSpace Space = this->Alloc4KPart(Size, Bitmap, AvailableSpace4K);

		bool Assign2MAddress = !Assign4KAddress && Space.RemainingSize >= Size2M && AvailableSpace2M > 0;
		if (Assign2MAddress == true) {
			Space = this->Alloc2MPart(Space.RemainingSize, Bitmap, AvailableSpace2M);
		} else {
			Space.RemainingSize = this->Alloc2MPart(Space.RemainingSize, Bitmap, AvailableSpace2M).RemainingSize;
		}

		bool Assign1GAddress = !Assign2MAddress && Space.RemainingSize >= Size1G && AvailableSpace1G > 0;
		if (Assign1GAddress == true) {
			Space = this->Alloc1GPart(Space.RemainingSize, Bitmap, AvailableSpace1G);
		} else {
			Space.RemainingSize = this->Alloc1GPart(Space.RemainingSize, Bitmap, AvailableSpace1G).RemainingSize;
		}

		uint64_t AvailableSpace2MRemaining = (((uint64_t) this->End2M) - (((uint64_t) this->Next2M)));
		uint64_t AvailableSpace4KRemaining = (((uint64_t) this->End4K) - (((uint64_t) this->Next4K)));

		Space.RemainingSize = this->Alloc2MPart(Space.RemainingSize, Bitmap, AvailableSpace2MRemaining).RemainingSize;
		Space.RemainingSize = this->Alloc4KPart(Space.RemainingSize, Bitmap, AvailableSpace4KRemaining).RemainingSize;

		return Space.Addr;
	}

	AllocSpace KernelTable::Alloc4KPart(uint64_t Size, uint64_t Bitmap, uint64_t AvailableSpace4K) {
		uint64_t RequiredPages4K = 0;
		if (Size > AvailableSpace4K) {
			RequiredPages4K = AvailableSpace4K / Size4K;
		} else {
			RequiredPages4K = Size / Size4K + (Size % Size4K > 0);
		}
		return this->Alloc4KPartForRequiredSpace(Size, Bitmap, RequiredPages4K);
	}

	AllocSpace KernelTable::Alloc4KPartForRequiredSpace(uint64_t Size, uint64_t Bitmap, uint64_t RequiredPages4K) {
		void *Addr = this->Alloc4K(Bitmap);
		for (int i = RequiredPages4K - 1; i > 0; i--) {
			this->Alloc4K(Bitmap);
		}
		int64_t RemainingSize = Size - RequiredPages4K * Size4K;
		return { Addr, RemainingSize };
	}

	AllocSpace KernelTable::Alloc2MPart(uint64_t Size, uint64_t Bitmap, uint64_t AvailableSpace2M) {
		uint64_t RequiredPages2M = 0;
		if (Size > AvailableSpace2M) {
			RequiredPages2M = AvailableSpace2M / Size2M;
		} else {
			RequiredPages2M = Size / Size2M + (Size % Size2M > 255);
		}
		return this->Alloc4KPartForRequiredSpace(Size, Bitmap, RequiredPages2M);
	}

	AllocSpace KernelTable::Alloc2MPartForRequiredSpace(uint64_t Size, uint64_t Bitmap, uint64_t RequiredPages2M) {
		void *Addr = this->Alloc2M(Bitmap);
		for (int i = RequiredPages2M - 1; i > 0; i--) {
			this->Alloc2M(Bitmap);
		}
		int64_t RemainingSize = Size - RequiredPages2M * Size2M;
		return { Addr, RemainingSize };
	}

	AllocSpace KernelTable::Alloc1GPart(uint64_t Size, uint64_t Bitmap, uint64_t AvailableSpace1G) {
		uint64_t RequiredPages1G = 0;
		if (Size > AvailableSpace1G) {
			RequiredPages1G = AvailableSpace1G / Size1G;
		} else {
			RequiredPages1G = Size / Size1G + (Size % Size1G > 255);
		}
		return this->Alloc4KPartForRequiredSpace(Size, Bitmap, RequiredPages1G);
	}

	AllocSpace KernelTable::Alloc1GPartForRequiredSpace(uint64_t Size, uint64_t Bitmap, uint64_t RequiredPages1G) {
		void *Addr = this->Alloc1G(Bitmap);
		for (int i = RequiredPages1G - 1; i > 0; i--) {
			this->Alloc1G(Bitmap);
		}
		int64_t RemainingSize = Size - RequiredPages1G * Size1G;
		return { Addr, RemainingSize };
	}

	void *KernelTable::Alloc4K(uint64_t Bitmap) {
		KernelTable::Alloc4K(this->Next4K, Bitmap);
		if (this->Next4K >= this->End4K) {
			this->Get2MPageFor4KAllocator();
		}
		uint64_t *Addr = this->Next4K;
		this->Next4K += Size4K8B;
		return Addr;
	}

	void KernelTable::Alloc4K(void *Address, uint64_t Bitmap) {
		KernelTable::Map4K(Address, PMM::Alloc4K.Alloc(), Bitmap);
	}

	void KernelTable::Map4K(void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {
		AddressIndices AI;
		AI = GetIndicesFromAddress(VirtAddress);

		uint64_t *PML4 = GetRecursiveTableEntryAddress(511, 511, 511, AI.PML4);
		CreateNewTableEntryIfEntryNotExisting(PML4, Bitmap);

		uint64_t *PDPT = GetRecursiveTableEntryAddress(511, 511, AI.PML4, AI.PDPT);
		CreateNewTableEntryIfEntryNotExisting(PDPT, Bitmap);

		uint64_t *PD = GetRecursiveTableEntryAddress(511, AI.PML4, AI.PDPT, AI.PD);
		CreateNewTableEntryIfEntryNotExisting(PD, Bitmap);

		uint64_t *PT = GetRecursiveTableEntryAddress(AI.PML4, AI.PDPT, AI.PD, AI.PT);
		AssignPhysicalAddressIfEntryNotExisting(PT, PhysAddress, Bitmap);
	}

	void *KernelTable::Alloc2M(uint64_t Bitmap) {
		KernelTable::Alloc2M(this->Next2M, Bitmap);
		if (this->Next2M >= this->End2M) {
			this->Get1GPageFor2MAllocator();
		}
		uint64_t *Addr = this->Next2M;
		this->Next2M += Size2M8B;
		return Addr;
	}

	void KernelTable::Alloc2M(void *Address, uint64_t Bitmap) {
		KernelTable::Map2M(Address, PMM::Alloc2M.Alloc(), Bitmap);
	}

	void KernelTable::Map2M(void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {
		AddressIndices AI;
		AI = GetIndicesFromAddress(VirtAddress);

		uint64_t *PML4 = GetRecursiveTableEntryAddress(511, 511, 511, AI.PML4);
		CreateNewTableEntryIfEntryNotExisting(PML4, Bitmap);

		uint64_t *PDPT = GetRecursiveTableEntryAddress(511, 511, AI.PML4, AI.PDPT);
		CreateNewTableEntryIfEntryNotExisting(PDPT, Bitmap);

		uint64_t *PD = GetRecursiveTableEntryAddress(511, AI.PML4, AI.PDPT, AI.PD);
		AssignPhysicalAddressIfEntryNotExisting(PD, PhysAddress, (Bitmap | PG_BIG));
	}

	void KernelTable::Alloc1G(void *Address, uint64_t Bitmap) {
		KernelTable::Map1G(Address, PMM::Alloc1G.Alloc(), Bitmap);
	}

	void KernelTable::Map1G(void *VirtAddress, uint64_t PhysAddress, uint64_t Bitmap) {
		AddressIndices AI;
		AI = GetIndicesFromAddress(VirtAddress);

		uint64_t *PML4 = GetRecursiveTableEntryAddress(511, 511, 511, AI.PML4);
		CreateNewTableEntryIfEntryNotExisting(PML4, Bitmap);

		uint64_t *PDPT = GetRecursiveTableEntryAddress(511, 511, AI.PML4, AI.PDPT);
		AssignPhysicalAddressIfEntryNotExisting(PDPT, PhysAddress, (Bitmap | PG_BIG));
	}

	void KernelTable::LoadTable() {
		setCR3((uint64_t)&this->PML4T[0] - HVMA);
	}

	uint64_t *GetRecursiveTableEntryAddress(uint16_t PML4, uint16_t PDPT, uint16_t PD, uint16_t PT) {
		return (uint64_t *)(ADDRESS_ADDITIVE | (511 << 39) | (PML4 << 30) | (PDPT << 21) | (PD << 12) | (PT << 3));
	}

	void *GetAddressFromIndices(AddressIndices addressIndexes) {
		return (uint64_t *)(ADDRESS_ADDITIVE | (511 << 39) | (addressIndexes.PML4 << 30) | (addressIndexes.PDPT << 21) | (addressIndexes.PD << 12) | (addressIndexes.PT << 3));
	}

	AddressIndices GetIndicesFromAddress(void *VirtAddress) {
		AddressIndices AI;
		AI.PML4 = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		AI.PDPT = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		AI.PD = (((uint64_t)VirtAddress) >> 21) & 0x1FF;
		AI.PT = (((uint64_t)VirtAddress) >> 12) & 0x1FF;
		return AI;
	}
}