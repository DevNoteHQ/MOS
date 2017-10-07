
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void lvt_timer(CPU::State *state)
{
	Text::WriteLine("TIMER!");
}