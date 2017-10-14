
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void SegmentNotPresent(CPU::State *state, uint64_t error)
{
	Console::Write("\nFAULT: Segment Not Present!");
	asm volatile("hlt");
}
