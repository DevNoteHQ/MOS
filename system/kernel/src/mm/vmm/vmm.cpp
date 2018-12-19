
#include "vmm.hpp"
#include <mm/pmm/pmm.hpp>

namespace VMM
{
	Pool::Pool()
	{
		this->PML4T[511] = (uint64_t)&PML4T[0] | PG_PRESENT | PG_WRITABLE | PG_NO_EXEC;

	}

	Pool::~Pool()
	{
		//Free all Tables
	}

	void *Pool::Alloc(uint64_t Size, uint64_t Bitmap)
	{
		void *Addr = 0;
		//Alloc contiguous memory. 4K fist, then 2M, then 1G, the rest if needed 2M
	}

	void Pool::Alloc(uint64_t Size, void *Address, uint64_t Bitmap)
	{

	}

	void Pool::Map(uint64_t Size, void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{

	}

	void *Pool::Alloc4K(uint64_t Bitmap)
	{
		Pool::Alloc4K(this->Next4K, Bitmap);
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

	void Pool::Alloc4K(void *Address, uint64_t Bitmap)
	{
		Pool::Map4K(Address, PMM::Alloc4K.Alloc(), Bitmap);
	}

	void Pool::Map4K(void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{
		uint16_t PML4I = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		uint16_t PDPTI = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		uint16_t PDI = (((uint64_t)VirtAddress) >> 21) & 0x1FF;
		uint16_t PTI = (((uint64_t)VirtAddress) >> 12) & 0x1FF;

		uint64_t *PDPT = (uint64_t *)(((uint64_t)PML4T[PML4I]) & 0x3F);
		if ((PDPT == 0) || (((uint64_t)PML4T[PML4I] & 0x1) == 0))
		{
			PDPT = PMM::Alloc4K.Alloc();
			PML4T[PML4I] = (uint64_t)PDPT | Bitmap;
		}
		uint64_t *PD = (uint64_t *)(((uint64_t)PDPT[PDPTI]) & 0x3F);
		if ((PD == 0) || (((uint64_t)PDPT[PDPTI] & 0x1) == 0))
		{
			PD = PMM::Alloc4K.Alloc();
			PDPT[PDPTI] = (uint64_t)PD | Bitmap;
		}
		uint64_t *PT = (uint64_t *)(((uint64_t)PD[PDI]) & 0x3F);
		if ((PT == 0) || (((uint64_t)PD[PDI] & 0x1) == 0))
		{
			PT = PMM::Alloc4K.Alloc();
			PD[PDI] = (uint64_t)PT | Bitmap;
		}
		uint64_t *P = (uint64_t *)(((uint64_t)PT[PTI]) & 0x3F);
		if ((P == 0) || (((uint64_t)PT[PTI] & 0x1) == 0))
		{
			P = PhysAddress;
			PT[PTI] = (uint64_t)P | Bitmap;
		}
		else
		{
			//Throw error
		}
	}

	void *Pool::Alloc2M(uint64_t Bitmap)
	{
		Pool::Alloc2M(this->Next2M, Bitmap);
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

	void Pool::Alloc2M(void *Address, uint64_t Bitmap)
	{
		Pool::Map2M(Address, PMM::Alloc2M.Alloc(), Bitmap);
	}

	void Pool::Map2M(void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{
		uint16_t PML4I = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		uint16_t PDPTI = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		uint16_t PDI = (((uint64_t)VirtAddress) >> 21) & 0x1FF;

		uint64_t *PDPT = (uint64_t *)(((uint64_t)PML4T[PML4I]) & 0x3F);
		if ((PDPT == 0) || (((uint64_t)PML4T[PML4I] & 0x1) == 0))
		{
			PDPT = PMM::Alloc4K.Alloc();
			PML4T[PML4I] = (uint64_t)PDPT | Bitmap;
		}
		uint64_t *PD = (uint64_t *)(((uint64_t)PDPT[PDPTI]) & 0x3F);
		if ((PD == 0) || (((uint64_t)PDPT[PDPTI] & 0x1) == 0))
		{
			PD = PMM::Alloc4K.Alloc();
			PDPT[PDPTI] = (uint64_t)PD | Bitmap;
		}
		uint64_t *PT = (uint64_t *)(((uint64_t)PD[PDI]) & 0x3F);
		if ((PT == 0) || (((uint64_t)PD[PDI] & 0x1) == 0))
		{
			PT = PhysAddress;
			PD[PDI] = (uint64_t)PT | Bitmap | PG_BIG;
		}
		else
		{
			//Throw error
		}
	}

	void *Pool::Alloc1G(uint64_t Bitmap)
	{
		Pool::Alloc1G(this->Next1G, Bitmap);
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

	void Pool::Alloc1G(void *Address, uint64_t Bitmap)
	{
		Pool::Map1G(Address, PMM::Alloc1G.Alloc(), Bitmap);
	}

	void Pool::Map1G(void *VirtAddress, void *PhysAddress, uint64_t Bitmap)
	{
		uint16_t PML4I = (((uint64_t)VirtAddress) >> 39) & 0x1FF;
		uint16_t PDPTI = (((uint64_t)VirtAddress) >> 30) & 0x1FF;
		
		uint64_t *PDPT = (uint64_t *)(((uint64_t)PML4T[PML4I]) & 0x3F);
		if ((PDPT == 0) || (((uint64_t)PML4T[PML4I] & 0x1) == 0))
		{
			PDPT = PMM::Alloc4K.Alloc();
			PML4T[PML4I] = (uint64_t)PDPT | Bitmap;
		}
		uint64_t *PD = (uint64_t *)(((uint64_t)PDPT[PDPTI]) & 0x3F);
		if ((PD == 0) || (((uint64_t)PDPT[PDPTI] & 0x1) == 0))
		{
			PD = PhysAddress;
			PDPT[PDPTI] = (uint64_t)PD | Bitmap | PG_BIG;
		}
		else
		{
			//Throw error
		}
	}
}