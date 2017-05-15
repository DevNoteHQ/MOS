
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


__attribute__((interrupt)) void irq09(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("IRQ!");
}