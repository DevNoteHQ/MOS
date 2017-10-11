
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/init.hpp>


__attribute__((interrupt)) void IRQ_02(CPU::State *state)
{
	//Text::Clear();
	Text::WriteLine("IRQ_02!");
}