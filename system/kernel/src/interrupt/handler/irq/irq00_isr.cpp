
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler
{
	void IRQ_00(CPU::State *state)
	{
		Console::Write("\nPIT-IRQ! ");
		IO::outb(0x20, 0x20);
	}
}