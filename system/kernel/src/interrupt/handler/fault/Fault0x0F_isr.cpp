
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void Fault0x0F(CPU::State *state)
	{
		Console::Write("\nFAULT: Fault0x0F!");
		asm volatile("hlt");
	}
}
