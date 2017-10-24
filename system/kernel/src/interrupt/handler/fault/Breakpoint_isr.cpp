
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void Breakpoint(CPU::State *state)
	{
		Console::Write("\nFAULT: Breakpoint!");
		asm volatile("hlt");
	}
}
