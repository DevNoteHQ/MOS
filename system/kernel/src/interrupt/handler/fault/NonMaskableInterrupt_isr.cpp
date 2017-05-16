
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void NonMaskableInterrupt(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Non Maskable Interrupt!");
}
