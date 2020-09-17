
#include "conv.hpp"

namespace VMM {
	void *ToVMA_V(void *addr) {
		uintptr_t iAddr = (uintptr_t)addr;
		iAddr += HVMA;
		return (void *)iAddr;
	}

	uintptr_t ToVMA_I(uintptr_t addr) {
		return addr + HVMA;
	}
}