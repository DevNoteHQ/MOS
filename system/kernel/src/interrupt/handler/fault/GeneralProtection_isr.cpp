
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void GeneralProtection(CPU::State *state) {
		Console::Write("\nFAULT: General Protection! ");
		Console::Write(state->Error, 10);
		asm volatile("hlt");
	}
}
