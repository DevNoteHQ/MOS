
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_18(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ_18!");
}