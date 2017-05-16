
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Overflow(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Overflow!");
}
