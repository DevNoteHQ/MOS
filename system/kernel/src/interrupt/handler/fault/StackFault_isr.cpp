
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void StackFault(CPU::State *state, uint64_t error)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Stack Fault!");
}
