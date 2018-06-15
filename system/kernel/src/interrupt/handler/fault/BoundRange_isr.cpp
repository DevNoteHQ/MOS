
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void BoundRange(CPU::State *state)
	{
		Console::Write("\nFAULT: Bound Range!");
		asm volatile("hlt");
	}
}
