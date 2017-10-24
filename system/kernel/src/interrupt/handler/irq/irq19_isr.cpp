
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler
{
	void IRQ_19(CPU::State *state)
	{
		Console::Write("\nIRQ_19!");

		IO::outb(0x20, 0x20);
	}
}