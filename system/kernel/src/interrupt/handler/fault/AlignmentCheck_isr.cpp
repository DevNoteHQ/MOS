
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void AlignmentCheck(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT Alignment Check!");
	asm volatile("hlt");
}
