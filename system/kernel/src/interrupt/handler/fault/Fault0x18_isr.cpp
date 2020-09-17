
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void Fault0x18(CPU::State *state) {
		Console::Write("\nFAULT: Fault0x18!");
		asm volatile("hlt");
	}
}
