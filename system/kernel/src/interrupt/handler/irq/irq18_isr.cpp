
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_18(CPU::State *state) {
		Console::Write("\nIRQ_18!");

		Assembler::IO::Ports::outb(0x20, 0x20);
	}
}