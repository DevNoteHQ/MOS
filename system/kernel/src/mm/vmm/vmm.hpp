
#ifndef MM_VMM_VMM_HPP
#define MM_VMM_VMM_HPP

#define PG_PRESENT		(1 << 0)	//Page Present
#define PG_WRITABLE		(1 << 1)	//Page Read/Write (Write if 1)
#define PG_USER			(1 << 2)	//Page User/Kernelmode (1 is Usermode, 0 is Kernelmode)
#define PG_PWT			(1 << 3)	//Page Write Through
#define PG_PCD			(1 << 4)	//Page Cache Disable
#define PG_ACCESSED		(1 << 5)	//Page Accessed
#define PG_DIRTY		(1 << 6)	//Page Written to
#define PG_BIG			(1 << 7)	//Table entry refers to a Page for 2M and 1G Pages
#define PG_PAT4K		(1 << 7)	//PAT for 4K Pages
#define PG_GLOBAL		(1 << 8)	//Translation is global
#define PG_PAT			(1 << 12)	//PAT for 2M and 1G Pages

#define PG_NO_EXEC		0x8000000000000000

#define PG_FILTER_TABLE	(~(PG_NO_EXEC | 0xFFF))		//Filter for Page Tables and 4K Page Entries
#define PG_FILTER_PAGE	(~(PG_NO_EXEC | 0x1FFF))	//Filter for 2M and 1G Pages

#define ADDRESS_ADDITIVE	0xFFFF000000000000 //For Addresses with Bit 47 = 1

#define Size4K8B	0x200
#define Size4K		0x1000
#define Size2M8B	0x40000
#define Size2M		0x200000
#define Size1G8B	0x8000000
#define Size1G		0x40000000
#define Size512G8B	0x1000000000
#define Size512G	0x8000000000


namespace VMM
{
	class KernelTable
	{
	private:
		uint64_t *Next4K;
		uint64_t *End4K;
		uint64_t *Next2M;
		uint64_t *End2M;
		uint64_t *Next1G;
		uint64_t *End1G;
		uint64_t *Next512G;
		uint64_t *End512G;

		void Check(uint64_t *Entry, uint64_t Bitmap);
		void CheckPage(uint64_t *Entry, void *PhysAddress, uint64_t Bitmap);
	public:
		uint64_t *PML4T;

		void InitKernelTable();

		void *Alloc(uint64_t Size, uint64_t Bitmap);
		void Alloc(uint64_t Size, void *Address, uint64_t Bitmap);
		void Map(uint64_t Size, void *VirtAddress, void *PhysAddress, uint64_t Bitmap);
		void *Alloc4K(uint64_t Bitmap);
		void Alloc4K(void *Address, uint64_t Bitmap);
		void Map4K(void *VirtAddress, void *PhysAddress, uint64_t Bitmap);
		void *Alloc2M(uint64_t Bitmap);
		void Alloc2M(void *Address, uint64_t Bitmap);
		void Map2M(void *VirtAddress, void *PhysAddress, uint64_t Bitmap);
		void *Alloc1G(uint64_t Bitmap);
		void Alloc1G(void *Address, uint64_t Bitmap);
		void Map1G(void *VirtAddress, void *PhysAddress, uint64_t Bitmap);

		void LoadTable();
	};

	class Table : public KernelTable
	{
	public:
		Table();
		~Table();
	};

	extern "C" void setCR3(uint64_t PL4);

	void *GetAddress(uint16_t PML4I, uint16_t PDPTI, uint16_t PDI, uint16_t PTI);
	extern KernelTable Kernel;
}

#endif