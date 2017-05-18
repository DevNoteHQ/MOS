
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void StackFault(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: Stack Fault!");
}
