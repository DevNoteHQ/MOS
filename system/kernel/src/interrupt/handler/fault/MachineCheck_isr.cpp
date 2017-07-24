
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void MachineCheck(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("FAULT: Machine Check!");
}
