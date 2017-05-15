
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


__attribute__((interrupt)) void irq0(struct cpu_state *state)
{
	//Text::Clear();
	Text::Simple::Write("IRQ!");
}