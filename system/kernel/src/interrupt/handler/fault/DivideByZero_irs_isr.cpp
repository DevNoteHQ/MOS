
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void DivideByZero(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Divide By Zero!");
}