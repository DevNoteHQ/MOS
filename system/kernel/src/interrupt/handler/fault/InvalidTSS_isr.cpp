
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void InvalidTSS(CPU::State *state)
	{
		Console::Write("\nFAULT: Invalid TSS!");
		asm volatile("hlt");
	}
}
