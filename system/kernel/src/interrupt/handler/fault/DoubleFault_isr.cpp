
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void DoubleFault(CPU::State *state)
	{
		Console::Write("\nFAULT: Double Fault!");
		asm volatile("hlt");
	}
}
