
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void PageFault(CPU::State *state)
	{
		Console::Write("\nFAULT: Page Fault!");
		asm volatile("hlt");
	}
}
