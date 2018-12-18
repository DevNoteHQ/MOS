
#ifndef MM_VMM_VMM_HPP
#define MM_VMM_VMM_HPP

#define PG_PRESENT		0x1
#define PG_WRITABLE		0x2
#define PG_USER			0x4
#define PG_BIG			0x80
#define PG_NO_EXEC		0x8000000000000000

namespace VMM
{
	class Pool
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
	public:
		uint64_t *PML4T[512];

		Pool();
		~Pool();

		void *Alloc(uint64_t Size, uint64_t Bitmap);
		void *Alloc(uint64_t Size, void *Address, uint64_t Bitmap);
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
	};
}

#endif