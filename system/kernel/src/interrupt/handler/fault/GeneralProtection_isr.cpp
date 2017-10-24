
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void GeneralProtection(CPU::State *state)
	{
		Console::Write("\nFAULT: General Protection!");
		asm volatile("hlt");
	}
}
