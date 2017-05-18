
#include <terminal/text.hpp>
#include <interrupt/handler/stubs.hpp>


void DeviceNotAvailable(CPU::State *state)
{
	//Text::Clear();
	Text::Simple::Write("FAULT: Device Not Available!");
}
