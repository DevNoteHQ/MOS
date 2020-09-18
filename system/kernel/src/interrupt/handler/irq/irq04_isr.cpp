
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_04(CPU::State *state) {
		Console::Write("\nIRQ_04!");

		Assembler::IO::Ports::outb(0x20, 0x20);
	}
}