
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Overflow(CPU::State *state)
{
	Console::Write("\nFAULT: Overflow!");
	asm volatile("hlt");
}
