
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void NonMaskableInterrupt(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Non Maskable Interrupt!");
}
