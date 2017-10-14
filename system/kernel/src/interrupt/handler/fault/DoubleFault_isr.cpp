
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void DoubleFault(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT: Double Fault!");
	asm volatile("hlt");
}
