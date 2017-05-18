
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void DoubleFault(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: Double Fault!");
}
