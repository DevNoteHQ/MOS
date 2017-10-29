
#ifndef MM_VMM_INIT_HPP
#define MM_VMM_INIT_HPP

namespace VMM
{
	extern uint64_t *PL4;
	extern uint64_t *PL3;
	void Init();
	extern "C" void setCR3(uint64_t PL4);
	void *ToVMA_V(void *addr);
	uintptr_t ToVMA_I(uintptr_t addr);
}

#endif