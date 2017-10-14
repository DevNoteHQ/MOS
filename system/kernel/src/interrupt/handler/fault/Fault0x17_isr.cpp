
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void Fault0x17(CPU::State *state)
{
	Console::Write("\nFAULT: Fault0x17!");
	asm volatile("hlt");
}
