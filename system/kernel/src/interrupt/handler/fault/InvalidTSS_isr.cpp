
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void InvalidTSS(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT: Invalid TSS!");
	asm volatile("hlt");
}
