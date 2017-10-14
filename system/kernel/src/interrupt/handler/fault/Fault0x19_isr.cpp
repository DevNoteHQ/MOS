
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x19(CPU::State *state)
{
	Console::Write("\nFAULT: Fault0x19!");
	asm volatile("hlt");
}
