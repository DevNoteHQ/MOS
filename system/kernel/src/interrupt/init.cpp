
#include "init.hpp"
#include "handler/handler.hpp"

#include "apic.hpp"
#include "pic.hpp"

#include <cpuid/CPUID.hpp>

namespace Interrupt
{
	void Init()
	{
		Handler::SetDefault();
		PIC::Init();
		PIC::Activate();
		APIC::Init();
	}

	namespace IOAPIC
	{
		void Init()
		{
			PIC::Disable();
		}
	}
}