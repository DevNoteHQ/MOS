
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void Debug(CPU::State *state)
	{
		Console::Write("\nFAULT: Debug!");
		asm volatile("hlt");
	}
}
