
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


__attribute__((interrupt)) void LVT_Error(CPU::State *state)
{
	Text::WriteLine("LVT_Error!");
}