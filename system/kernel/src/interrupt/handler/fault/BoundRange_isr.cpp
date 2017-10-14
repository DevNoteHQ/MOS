
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void BoundRange(CPU::State *state)
{
	Console::Write("\nFAULT: Bound Range!");
	asm volatile("hlt");
}
