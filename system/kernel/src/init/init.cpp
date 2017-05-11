
//Library Includes:



//Kernel Includes:

#include <sheduler/sheduler.h>
#include <memorymanagement/phy32.h>
#include <terminal/text.h>

#define CPU_COUNT 8

using namespace kernel;

void kernel_main(void)
{
	Text::init();
	Text::printf(" | Hello | ");
	
	sheduler CPU[CPU_COUNT];
	for(int i = 0; i < CPU_COUNT; i++)
	{
		CPU[i].init();
	}
}

extern "C"
{
	void init(void)
	{
		kernel_main();
	}
}