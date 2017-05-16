
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Fault0x1B(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Fault0x1B!");
}
