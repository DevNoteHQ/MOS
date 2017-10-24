
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void AlignmentCheck(CPU::State *state)
	{
		Console::Write("\nFAULT Alignment Check!");
		asm volatile("hlt");
	}
}
