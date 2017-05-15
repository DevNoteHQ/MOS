
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void NonMaskableInterrupt(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Non Maskable Interrupt!");
}
