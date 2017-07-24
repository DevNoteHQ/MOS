
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Debug(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Debug!");
}
