
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_15(CPU::State *state) {
		Console::Write("\nIRQ_15!");

		Assembler::IO::Ports::outb(0x20, 0x20);
	}
}