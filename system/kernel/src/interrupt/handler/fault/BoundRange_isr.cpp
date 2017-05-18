
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void BoundRange(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: Bound Range!");
}
