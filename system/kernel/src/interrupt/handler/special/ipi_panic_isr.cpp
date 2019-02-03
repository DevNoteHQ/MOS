
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/apic.hpp>

namespace Interrupt::Handler
{
	void IPI_Panic(CPU::State *state)
	{
		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}