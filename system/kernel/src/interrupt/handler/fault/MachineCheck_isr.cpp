
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void MachineCheck(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Machine Check!");
}
