
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler
{
	void IPI_Tlb(CPU::State *state)
	{
		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}