
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Debug(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Debug!");
}
