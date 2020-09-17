
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

namespace Interrupt::Handler {
	void IRQ_13(CPU::State *state) {
		Console::Write("\nIRQ_13!");

		IO::outb(0x20, 0x20);
	}
}