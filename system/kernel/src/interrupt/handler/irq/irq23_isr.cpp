
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


__attribute__((interrupt)) void irq23(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("IRQ!");
}