
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void DoubleFault(CPU::State *state, uint64_t error)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Double Fault!");
}
