
#ifndef MM_PMM_PMM_HPP
#define MM_PMM_PMM_HPP

namespace PMM
{
	void *Alloc(uint64_t size);
	void Free(void *addr);
}

#endif