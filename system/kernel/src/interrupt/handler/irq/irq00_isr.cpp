
#include <terminal/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>

__attribute__((interrupt)) void IRQ_00(CPU::State *state)
{
	Console::Write("\nPIT-IRQ!");

	IO::outb(0x20, 0x20);
}