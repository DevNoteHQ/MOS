
#include "vmm.hpp"
#include <mm/pmm/pmm.hpp>

//TODO: Add Unmap

//Idea: On loading new Process, switch to kernel, map the kernel, then switch to new Table and VMM::Alloc the space required

namespace VMM
{
	Table::Table()
	{
		/*
		this->PML4T = (PMM::Alloc4K.Alloc() + HVMA);

		this->PML4T[511] = (uint64_t)&PML4T[0] - HVMA | PG_PRESENT | PG_WRITABLE;
		uint64_t *KernelEntry = GetAddress(511, 511, 511, 510);
		this->PML4T[510] = *KernelEntry;
		*/
	}

	KernelTable::KernelTable()
	{
		this->PML4T = (PMM::Alloc4K.Alloc() + HVMA); //Map it later
		this->PML4T[511] = (uint64_t)&PML4T[0] - HVMA | PG_PRESENT | PG_WRITABLE;
	}

	KernelTable::~KernelTable()
	{
		//Never gonna happen :D
	}

	Table::~Table()
	{
		//Free all Tables
	}

	void Table::Check(uint64_t *Entry, uint64_t Bitmap)
	{
		if ((*Entry == 0) || (((*Entry) & 0x1) == 0))
		{
			*Entry = (uint64_t)PMM::Alloc4K.Alloc() | Bitmap;
		}
	}

	void Table::CheckPage(uint64_t *Entry, void *PhysAddress, uint64_t Bitmap)
	{
		if ((*Entry == 0) || (((*Entry) & 0x1) == 0))
		{
			*Entry = (uint64_t) PhysAddress | Bitmap;
		}
		else
		{
			//Throw error
		}
	}

	void *Table::Alloc(uint64_t Size, uint64_t Bitmap)
	{
		void *Addr = 0;
		//Alloc contiguous memory. 4K fist, then 2M, then 1G, the rest if needed 2M
	}

	void Table::Alloc(uint64_t Size, void *Address, uint64_t Bitmap)
	{

	}

	void Table::Map(uint64_t Size, void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{

	}

	void *Table::Alloc4K(uint64_t Bitmap)
	{
		Table::Alloc4K(this->Next4K, Bitmap);
		if (this->Next4K >= this->End4K)
		{
			if (this->Next2M >= this->End2M)
			{
				if (this->Next1G >= this->End1G)
				{
					//Unlikely to happen
					if (this->Next512G >= this->End512G)
					{
						//Throw error
					}
					else
					{
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

	void Table::Alloc4K(void *Address, uint64_t Bitmap)
	{
		Table::Map4K(Address, PMM::Alloc4K.Alloc(), Bitmap);
	}

	void Table::Map4K(void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{
		uint16_t PML4I = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		uint16_t PDPTI = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		uint16_t PDI = (((uint64_t)VirtAddress) >> 21) & 0x1FF;
		uint16_t PTI = (((uint64_t)VirtAddress) >> 12) & 0x1FF;

		uint64_t *PML4E = GetAddress(511, 511, 511, PML4I);
		Check(PML4E, Bitmap);

		uint64_t *PDPTE = GetAddress(511, 511, PML4I, PDPTI);
		Check(PDPTE, Bitmap);

		uint64_t *PDE = GetAddress(511, PML4I, PDPTI, PDI);
		Check(PDE, Bitmap);

		uint64_t *PTE = GetAddress(PML4I, PDPTI, PDI, PTI);
		CheckPage(PTE, PhysAddress, Bitmap);
	}

	void *Table::Alloc2M(uint64_t Bitmap)
	{
		Table::Alloc2M(this->Next2M, Bitmap);
		if (this->Next2M >= this->End2M)
		{
			if (this->Next1G >= this->End1G)
			{
				//Unlikely to happen
				if (this->Next512G >= this->End512G)
				{
					//Throw error
				}
				else
				{
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

	void Table::Alloc2M(void *Address, uint64_t Bitmap)
	{
		Table::Map2M(Address, PMM::Alloc2M.Alloc(), Bitmap);
	}

	void Table::Map2M(void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{
		uint16_t PML4I = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		uint16_t PDPTI = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		uint16_t PDI = (((uint64_t)VirtAddress) >> 21) & 0x1FF;

		uint64_t *PML4E = GetAddress(511, 511, 511, PML4I);
		Check(PML4E, Bitmap);

		uint64_t *PDPTE = GetAddress(511, 511, PML4I, PDPTI);
		Check(PDPTE, Bitmap);

		uint64_t *PDE = GetAddress(511, PML4I, PDPTI, PDI);
		CheckPage(PDE, PhysAddress, (Bitmap | PG_BIG));
	}

	void *Table::Alloc1G(uint64_t Bitmap)
	{
		Table::Alloc1G(this->Next1G, Bitmap);
		if (this->Next1G >= this->End1G)
		{
			//Unlikely to happen
			if (this->Next512G >= this->End512G)
			{
				//Throw error
			}
			else
			{
				this->Next1G = this->Next512G;
				this->End1G = this->Next1G + Size512G8B;
				this->Next512G += Size512G8B;
			}
		}
		uint64_t *Addr = this->Next1G;
		this->Next1G += Size1G8B;
		return Addr;
	}

	void Table::Alloc1G(void *Address, uint64_t Bitmap)
	{
		Table::Map1G(Address, PMM::Alloc1G.Alloc(), Bitmap);
	}

	void Table::Map1G(void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{
		uint16_t PML4I = (((uint64_t)VirtAddress) >> 39) & 511;
		uint16_t PDPTI = (((uint64_t)VirtAddress) >> 30) & 511;

		uint64_t *PML4E = GetAddress(511, 511, 511, PML4I);
		Check(PML4E, Bitmap);

		uint64_t *PDPTE = GetAddress(511, 511, PML4I, PDPTI);
		CheckPage(PDPTE, PhysAddress, (Bitmap | PG_BIG));
	}

	void Table::LoadTable()
	{
		setCR3((uint64_t)&this->PML4T[0] - HVMA);
	}

	void *GetAddress(uint16_t PML4I, uint16_t PDPTI, uint16_t PDI, uint16_t PTI)
	{
		return (uint64_t *)(ADDRESS_ADDITIVE | (511 << 39) | (PML4I << 30) | (PDPTI << 21) | (PDI << 12) | (PTI << 3));
	}
}