
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_00(CPU::State *state)
{
	Text::WriteLine("PIT-IRQ!");

	IO::outb(0x20, 0x20);
}