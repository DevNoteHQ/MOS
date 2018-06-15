
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void Fault0x1D(CPU::State *state)
	{
		Console::Write("\nFAULT: Fault0x1D!");
		asm volatile("hlt");
	}
}
