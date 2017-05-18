
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>

void DivideByZero(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: Divide By Zero!");
}