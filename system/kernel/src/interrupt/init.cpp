
#include <interrupt/init.h>
#include <cpu/CPUID.h>

namespace Interrupt
{
	namespace APIC
	{
		bool check()
		{
			uint32_t eax, edx;
			CPUID::get(1, &eax, &unused, &unused, &edx);
			return edx & CPUID::F1::EDX_APIC;
		}

		void init(void)
		{
			if (!check()) abort();

		}
	}
	namespace IOAPIC
	{
		void init(void)
		{

		}
	}
}