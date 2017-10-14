
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x16(CPU::State *state)
{
	Console::Write("\nFAULT: Fault0x16!");
	asm volatile("hlt");
}
