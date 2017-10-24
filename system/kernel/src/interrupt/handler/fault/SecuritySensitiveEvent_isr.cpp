
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void SecuritySensitiveEvent(CPU::State *state)
	{
		Console::Write("\nFAULT: Security-sensitive Event in Host!");
		asm volatile("hlt");
	}
}
