
#include <interrupt/init.hpp>
#include <cpu/CPUID.hpp>

namespace Interrupt
{
	namespace APIC
	{
		bool check()
		{
			uint32_t eax, edx;
			cpuid(1, eax, unused, unused, edx);
			return edx & CPUID::EAX1::EDX_APIC;
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