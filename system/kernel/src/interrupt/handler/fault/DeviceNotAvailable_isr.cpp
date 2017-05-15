
#include <terminal/text.h>
#include <interrupt/handler/stubs.h>


void DeviceNotAvailable(CPU::State *state)
{
	Text::Clear();
	Text::Simple::Write("FAULT: Device Not Available!");
}
