
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void InvalidOpcode(CPU::State *state)
{
	Console::Write("\nFAULT: Invalid Opcode!");
	asm volatile("hlt");
}
