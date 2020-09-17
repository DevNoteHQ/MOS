
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void Fault0x1A(CPU::State *state) {
		Console::Write("\nFAULT: Fault0x1A!");
		asm volatile("hlt");
	}
}
