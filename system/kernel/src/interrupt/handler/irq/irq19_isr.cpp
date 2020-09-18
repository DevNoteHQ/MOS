
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_19(CPU::State *state) {
		Console::Write("\nIRQ_19!");

		Assembler::IO::Ports::outb(0x20, 0x20);
	}
}