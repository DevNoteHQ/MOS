
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void InvalidOpcode(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Invalid Opcode!");
}
