
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void Overflow(CPU::State *state) {
		Console::Write("\nFAULT: Overflow!");
		asm volatile("hlt");
	}
}
