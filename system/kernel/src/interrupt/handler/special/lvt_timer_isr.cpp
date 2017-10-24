
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler
{
	void LVT_Timer(CPU::State *state)
	{
		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}