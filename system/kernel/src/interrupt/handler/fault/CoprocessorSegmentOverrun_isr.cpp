
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void CoprocessorSegmentOverrun(CPU::State *state) {
		Console::Write("\nFAULT: Coporcessor Segment Overrun!");
		asm volatile("hlt");
	}
}
