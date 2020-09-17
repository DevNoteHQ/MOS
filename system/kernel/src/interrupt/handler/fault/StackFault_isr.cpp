
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void StackFault(CPU::State *state) {
		Console::Write("\nFAULT: Stack Fault!");
		asm volatile("hlt");
	}
}
