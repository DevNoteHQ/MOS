
#ifndef MM_VMM_VMM_HPP
#define MM_VMM_VMM_HPP

namespace VMM
{
	class Pool
	{
	private:
		uint8_t *Next4K;
		uint8_t *Next2M;
		uint8_t *Next1G;
		uint8_t *Next512G;
	public:
		uint8_t *PML4T[512];

		void *Alloc(uint64_t Size);
		void *Alloc(uint64_t Size, void *Address);
		void *Map(uint64_t Size, void *VirtAddress, void *PhysAddress);
		void *Alloc4K();
		void *Alloc4K(void *Address);
		void *Map4K(void *VirtAddress, void *PhysAddress);
		void *Alloc2M();
		void *Alloc2M(void *Address);
		void *Map2M(void *VirtAddress, void *PhysAddress);
		void *Alloc1G();
		void *Alloc1G(void *Address);
		void *Map1G(void *VirtAddress, void *PhysAddress);
		void *Alloc512G();
		void *Alloc512G(void *Addresss);
		void *Map512G(void *VirtAddress, void *PhysAddress);
	};
}

#endif