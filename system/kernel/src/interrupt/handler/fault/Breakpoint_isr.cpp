
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Breakpoint(CPU::State *state)
{
	Console::Write("\nFAULT: Breakpoint!");
	asm volatile("hlt");
}
