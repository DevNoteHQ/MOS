
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler
{
	void IRQ_23(CPU::State *state)
	{
		Console::Write("\nIRQ_23!");

		IO::outb(0x20, 0x20);
	}
}