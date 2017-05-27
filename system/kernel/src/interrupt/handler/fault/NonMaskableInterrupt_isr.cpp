
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void NonMaskableInterrupt(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Non Maskable Interrupt!");
}
