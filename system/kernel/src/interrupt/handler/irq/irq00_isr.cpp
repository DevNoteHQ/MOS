
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>
#include <timer/pit.hpp>

namespace Interrupt::Handler {
	void IRQ_00(CPU::State *state) {
		Console::WriteLine("\nPIT-IRQ! ");
		if (Timer::PIT::Interrupt != 0) {
			Timer::PIT::Interrupt();
		}
		Assembler::IO::Ports::outb(0x20, 0x20);
	}
}