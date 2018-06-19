
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <utility/convert/convert.hpp>

namespace Interrupt::Handler
{
	void GeneralProtection(CPU::State *state)
	{
		Console::Write("\nFAULT: General Protection! ");
		char cTest[64];
		Convert::ToString(state->iError, cTest);
		Console::Write(cTest);
		asm volatile("hlt");
	}
}
