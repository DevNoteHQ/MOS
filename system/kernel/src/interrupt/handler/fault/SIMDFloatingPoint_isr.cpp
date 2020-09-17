
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void SIMDFloatingPoint(CPU::State *state) {
		Console::Write("\nFAULT: SIMD Floating Point!");
		asm volatile("hlt");
	}
}
