
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void Fault0x17(CPU::State *state) {
		Console::Write("\nFAULT: Fault0x17!");
		asm volatile("hlt");
	}
}
