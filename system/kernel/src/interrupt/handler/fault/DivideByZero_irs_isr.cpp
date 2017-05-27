
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>

void DivideByZero(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Divide By Zero!");
}