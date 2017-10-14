
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void MachineCheck(CPU::State *state)
{
	Console::Write("\nFAULT: Machine Check!");
	asm volatile("hlt");
}
