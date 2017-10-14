
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x0F(CPU::State *state)
{
	Console::Write("\nFAULT: Fault0x0F!");
	asm volatile("hlt");
}
