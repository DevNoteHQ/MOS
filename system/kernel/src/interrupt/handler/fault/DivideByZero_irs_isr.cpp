
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void DivideByZero(CPU::State *state)
	{
		Console::Write("\nFAULT: Divide By Zero!");
		asm volatile("hlt");
	}
}