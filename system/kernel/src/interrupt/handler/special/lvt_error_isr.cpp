
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void lvt_error(CPU::State *state)
{
	Text::WriteLine("LVT_Error!");
}