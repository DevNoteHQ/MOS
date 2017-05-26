
#include <mm/vmm.hpp>
#include <common.hpp>

#define PL2E  512 //512 --> 512 * 2MB Pages per PL3 Entry --> 512 * 16 * 2MB Pages per Process
#define PL3E  32  //32  --> 32 GB max per process
#define PL3KE 512 //512 --> 512 GB address space for the kernel
#define PL4E  512 //512 --> PID of the running process --> 512 processes possible without adding another PML4T

#define SIZE2M 0x000200000
#define SIZE1G 0x040000000

#define PG_PRESENT		0x1
#define PG_WRITABLE		0x2
#define PG_USER			0x4
#define PG_BIG			0x80
#define PG_NO_EXEC		0x8000000000000000
#define PG_ADDR_MASK	0xFFFFFFFFFF000

#define HVMA 0xFFFFFF0000000000 //HVMA = Higher Virtual Memory Address

#define PL4P	0x7E00000 //Position of the global PML4T in LVMA (PL4P = 0x7E00000 + HVMA for position in HVMA)

#define ALIGN	512 //Each entry has to be 4K aligned. Each entry is a uint64_t -> 8Bytes per Address -> PL4[1] = 8 + PL4[0] -> 8Bytes * 512 = 4096

namespace Paging
{
	uint64_t *PL4 = PL4P;
	uint64_t *PL3 = PL4P + 8 * ALIGN; //The address has to be 4K aligned --> set it with 8 * ALIGN
	void init(void)
	{
		PL4[PL4E - 1] = (((uint64_t) PL4) | PG_WRITABLE | PG_PRESENT);
		PL4[PL4E - 2] = (((uint64_t) PL3) | PG_WRITABLE | PG_PRESENT);
		PL4[0] = (((uint64_t) PL3) | PG_WRITABLE | PG_PRESENT);
		for (uint64_t i = 0; i < 512; i++)
		{
			PL3[i] = (((uint64_t) i * SIZE1G) | PG_WRITABLE | PG_PRESENT | PG_BIG);
		}
		SetCR3((uint64_t) PL4);
	}
	
	void *ToVMA_V(void *addr)
	{
		uintptr_t iAddr = (uintptr_t)addr;
		iAddr += HVMA;
		return (void *)iAddr;
	}

	uintptr_t ToVMA_I(uintptr_t addr)
	{
		return addr + HVMA;
	}
}

//TODO: Setup Lower Half and Higher Half --> switch to Higher Half --> delete Lower Half Page entry