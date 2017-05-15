
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void MachineCheck(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Machine Check!");
}
