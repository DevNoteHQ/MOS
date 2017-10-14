
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x1F(CPU::State *state)
{
	Console::Write("\nFAULT: Fault0x1F!");
	asm volatile("hlt");
}
