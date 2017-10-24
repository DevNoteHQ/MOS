
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler
{
	void MachineCheck(CPU::State *state)
	{
		Console::Write("\nFAULT: Machine Check!");
		asm volatile("hlt");
	}
}
