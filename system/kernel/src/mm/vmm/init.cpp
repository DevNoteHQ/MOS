
#include "init.hpp"

#include <mm/pmm/pmm.hpp>

#define PLE  512

#define SIZE2M 0x000200000
#define SIZE1G 0x040000000

#define PG_ADDR_MASK	0xFFFFFFFFFF000

#define PL4P	0x7E00000 //Position of the global PML4T in LVMA (PL4P = 0x7E00000 + HVMA for position in HVMA)

#define ALIGN4K	4096 //Each entry has to be 4K aligned. Each entry is a uint64_t -> 8Bytes per Address -> PL4[1] = 8 + PL4[0] -> 8Bytes * 512 = 4096

namespace VMM
{
	//TODO:
	//Redo everything
	//Get Sections
	//PMM::Alloc every Section
	//VMM::Map everything allocated with required Flags
	
	void *AllocEnd = 0;
	Pool KernelDirectory;

	uint64_t PL4[PLE] __attribute__((aligned(ALIGN4K)));
	uint64_t PL3[PLE] __attribute__((aligned(ALIGN4K)));
	void Init()
	{
		while (AllocEnd < ((uint64_t) &_end & 0x7FFFFFFFFF) - 0x200000)
		{
			AllocEnd = PMM::Alloc2M.Alloc();
		}
		//Map it


		PL4[PLE - 1] = (((uint64_t) &PL4[0] - HVMA) | PG_WRITABLE | PG_PRESENT);
		PL4[PLE - 2] = (((uint64_t) &PL3[0] - HVMA) | PG_WRITABLE | PG_PRESENT);
		PL4[0] = (((uint64_t) &PL3[0] - HVMA) | PG_WRITABLE | PG_PRESENT);
		for (uint64_t i = 0; i < PLE; i++)
		{
			PL3[i] = (((uint64_t) i * SIZE1G) | PG_WRITABLE | PG_PRESENT | PG_BIG);
		}
		setCR3((uint64_t) &PL4[0] - HVMA);
		memset(PL4P, 0, ALIGN4K * 2);
	}
}