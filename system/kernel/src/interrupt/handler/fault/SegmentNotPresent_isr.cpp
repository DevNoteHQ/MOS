
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void SegmentNotPresent(CPU::State *state)
	{
		Console::Write("\nFAULT: Segment Not Present!");
		asm volatile("hlt");
	}
}
