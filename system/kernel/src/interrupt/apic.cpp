
#include "apic.hpp"
#include "common.hpp"

#include <cpu/msr.hpp>
#include <cpuid/CPUID.hpp>
#include <mm/pmm/pmm.hpp>
#include <mm/vmm/vmm.hpp>

namespace Interrupt::APIC
{
	bool X2APIC = true;
	uint32_t *MMIO;

	void Write(size_t reg, uint64_t val)
	{
		if (X2APIC == true)
		{
			msr_write(MSR_X2APIC_MMIO + reg, val);
		}
		else
		{
			MMIO[reg * 4] = val;
		}
	}

	uint64_t Read(size_t reg)
	{
		if (X2APIC == true)
		{
			return msr_read(MSR_X2APIC_MMIO + reg);
		}
		else
		{
			return MMIO[reg * 4];
		}
	}

	void Init()
	{
		if (!(CPUID::CPUID_0[1][2] & CPUID::EAX1::ECX_x2APIC))
		{
			X2APIC = false;
			uint64_t BaseAddr = PMM::Alloc4K.Alloc();
			MMIO = (uint32_t *) (BaseAddr + HVMA);
			VMM::Kernel.Map4K(BaseAddr + HVMA, BaseAddr, PG_PRESENT | PG_WRITABLE);
			uint64_t Base = (msr_read(MSR_APIC_BASE) & APIC_BASE_BSP) | BaseAddr | APIC_BASE_ENABLED;
			msr_write(MSR_APIC_BASE, Base);
		}
		else
		{
			uint64_t Base = (msr_read(MSR_APIC_BASE) & APIC_BASE_BSP) | APIC_BASE_ENABLED | APIC_BASE_X2_MODE;
			msr_write(MSR_APIC_BASE, Base);
		}

		//Set the Spurious Interrupt Vector Register
		Write(APIC_SVR, SVR_ENABLED | SPURIOUS);
		//Set the Task Priority Register
		Write(APIC_TPR, 0);
		//Clear Errors
		Write(APIC_ESR, 0);
		//Set the Local Vector Table Registers
		Write(APIC_TIMER_DCR, 1);
		Write(APIC_LVT_TIMER, LVT_TIMER | LVT_TIMER_PERIODIC);
		Write(APIC_TIMER_ICR, 0xFFFFFFFF);
		Write(APIC_LVT_ERROR, LVT_TYPE_FIXED | LVT_ERROR);

		//Send EOI
		Write(APIC_EOI, 0);
	}
}