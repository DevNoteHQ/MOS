
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler
{
	void Default(CPU::State *state)
	{
		Console::WriteLine("Default!");
		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}