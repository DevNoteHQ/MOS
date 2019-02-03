
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/apic.hpp>

namespace Interrupt::Handler
{
	void LVT_Error(CPU::State *state)
	{
		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}