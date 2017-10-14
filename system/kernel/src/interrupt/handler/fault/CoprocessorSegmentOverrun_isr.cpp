
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void CoprocessorSegmentOverrun(CPU::State *state)
{
	Console::Write("\nFAULT: Coporcessor Segment Overrun!");
	asm volatile("hlt");
}
