
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void X87FloatingPoint(CPU::State *state)
	{
		Console::Write("\nFAULT: x87 Floating Point!");
		asm volatile("hlt");
	}
}
