
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void Fault0x16(CPU::State *state) {
		Console::Write("\nFAULT: Fault0x16!");
		asm volatile("hlt");
	}
}