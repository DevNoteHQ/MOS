
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void InvalidOpcode(CPU::State *state)
	{
		Console::Write("\nFAULT: Invalid Opcode!");
		asm volatile("hlt");
	}
}
