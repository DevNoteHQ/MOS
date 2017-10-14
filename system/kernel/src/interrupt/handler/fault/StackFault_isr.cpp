
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void StackFault(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT: Stack Fault!");
	asm volatile("hlt");
}
