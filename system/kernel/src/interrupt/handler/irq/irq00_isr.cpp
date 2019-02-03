
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>
#include <timer/pit.hpp>

namespace Interrupt::Handler
{
	void IRQ_00(CPU::State *state)
	{
		Console::Write("\nPIT-IRQ! ");
		if (Timer::PIT::Interrupt != 0)
		{
			Timer::PIT::Interrupt();
		}
		IO::outb(0x20, 0x20);
	}
}