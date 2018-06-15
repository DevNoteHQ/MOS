
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void Virtualization(CPU::State *state)
	{
		Console::Write("\nFAULT: Fault0x14!");
		asm volatile("hlt");
	}
}
