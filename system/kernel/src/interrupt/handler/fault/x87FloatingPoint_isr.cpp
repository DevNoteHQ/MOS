
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void x87FloatingPoint(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: x87 Floating Point!");
}
