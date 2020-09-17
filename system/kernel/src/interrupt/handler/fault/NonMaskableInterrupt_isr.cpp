
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void NonMaskableInterrupt(CPU::State *state) {
		Console::Write("\nFAULT: Non Maskable Interrupt!");
		asm volatile("hlt");
	}
}
