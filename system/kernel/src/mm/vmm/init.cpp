
#include "init.hpp"

#include <mm/pmm/pmm.hpp>
#include <utility/system/info.hpp>

#define SIZE2M 0x000200000
#define SIZE1G 0x040000000

#define PG_ADDR_MASK	0xFFFFFFFFFF000

#define PL4P	0x7E00000 //Position of the global PML4T in LVMA (PL4P = 0x7E00000 + HVMA for position in HVMA)

#define ALIGN4K	0x1000 //Each entry has to be 4K aligned. Each entry is a uint64_t -> 8Bytes per Address -> 8Bytes * 512 = 4096

namespace VMM
{
	//TODO:
	//Redo everything
	//Get Sections
	//PMM::Alloc every Section
	//VMM::Map everything allocated with required Flags
	
	void *AllocEnd = 0;

	uint64_t *PDPT = 0;
	uint64_t *PD = 0;
	uint64_t *PT = 0;

	void ManualMap(uint64_t Start, uint64_t End, uint64_t *Table, uint64_t Bitmap)
	{
		for (uint64_t Addr = Start; Addr < End; Addr += 0x1000)
		{
			Table[(Addr & 0x1FFFFF) / 0x1000] = (((uint64_t)Addr - HVMA) | Bitmap);
		}
	}

	void Init()
	{
		while (AllocEnd < (System::Info::KernelSize + 0x100000 - 0x1000))
		{
			AllocEnd = PMM::Alloc4K.Alloc();
		}

		Kernel.InitKernelTable();
		PDPT = PMM::Alloc4K.Alloc();
		PD = PMM::Alloc4K.Alloc();
		PT = PMM::Alloc4K.Alloc();

		Kernel.PML4T[510] = (((uint64_t) PDPT) | PG_WRITABLE | PG_PRESENT);
		PDPT[0] = (((uint64_t) PD) | PG_WRITABLE | PG_PRESENT);
		PD[0] = (((uint64_t) PT) | PG_WRITABLE | PG_PRESENT);

		ManualMap(System::Info::BinStartAddress, System::Info::BinEndAddress, PT, (PG_PRESENT));
		ManualMap(System::Info::DataStartAddress, System::Info::DataEndAddress, PT, (PG_WRITABLE | PG_PRESENT | PG_NO_EXEC));
		ManualMap(System::Info::BSSStartAddress, System::Info::BSSEndAddress, PT, (PG_WRITABLE | PG_PRESENT));
		//Map BIOS, Redo later!
		ManualMap(HVMA, HVMA + 0x100000, PT, (PG_WRITABLE | PG_PRESENT));
		PT[(((uint64_t) Kernel.PML4T) & 0x1FFFFF) / 0x1000] = (((uint64_t)Kernel.PML4T - HVMA) | (PG_WRITABLE | PG_PRESENT));

		Kernel.LoadTable();
		//memset(PL4P + HVMA, 0, ALIGN4K * 2);
	}
}