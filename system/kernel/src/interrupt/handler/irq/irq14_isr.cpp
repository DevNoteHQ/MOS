
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_14(CPU::State *state) {
		Console::Write("\nIRQ_14!");

		Assembler::IO::Ports::outb(0x20, 0x20);
	}
}