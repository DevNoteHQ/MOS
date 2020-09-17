
#include "cpu.hpp"
#include "msr.hpp"


namespace CPU {
	CPU BSP;

	void InitBSP() {
		memset(&BSP, 0, sizeof(BSP));
		BSP.self = &BSP;
		BSP.IsBSP = true;
		msr_write(MSR_GS_BASE, (uint64_t) &BSP);
		msr_write(MSR_GS_KERNEL_BASE, (uint64_t) &BSP);
	}
}

