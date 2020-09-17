
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_06(CPU::State *state) {
		Console::Write("\nIRQ_06!");

		IO::outb(0x20, 0x20);
	}
}