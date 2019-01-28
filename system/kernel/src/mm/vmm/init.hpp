
#ifndef MM_VMM_INIT_HPP
#define MM_VMM_INIT_HPP

#include "vmm.hpp"

namespace VMM
{
	void Init();

	extern uint64_t *PDPT;
	extern uint64_t *PD;
	extern uint64_t *PT;
}

#endif