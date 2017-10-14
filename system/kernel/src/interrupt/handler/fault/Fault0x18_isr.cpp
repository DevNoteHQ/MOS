
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x18(CPU::State *state)
{
	Console::Write("\nFAULT: Fault0x18!");
	asm volatile("hlt");
}
