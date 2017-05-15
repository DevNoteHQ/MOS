
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>

void DivideByZero(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Divide By Zero!");
}