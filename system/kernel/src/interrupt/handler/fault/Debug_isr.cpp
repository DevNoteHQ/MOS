
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Debug(CPU::State *state)
{
	Console::Write("\nFAULT: Debug!");
	asm volatile("hlt");
}
