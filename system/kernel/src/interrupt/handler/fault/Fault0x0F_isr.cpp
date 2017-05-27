
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Fault0x0F(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Fault0x0F!");
}
