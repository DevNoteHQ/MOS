
#include <terminal/text.h>

void interrupt(void)
{
	Text::Clear();
	Text::Simple::Write("Interrupt!");
}

void handler(void)
{

}