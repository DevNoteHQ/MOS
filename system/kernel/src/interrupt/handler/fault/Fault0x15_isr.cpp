
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Fault0x15(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Fault0x15!");
}
