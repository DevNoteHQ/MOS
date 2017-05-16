
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void Fault0x0F(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Fault0x0F!");
}
