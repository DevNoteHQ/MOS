
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void GeneralProtection(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT: General Protection!");
	asm volatile("hlt");
}
