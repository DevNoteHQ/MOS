

#include "sheduler.h"

using namespace kernel;

void video (void)
{
	const char hw[] = "Hello World!";
		int i;
		char* video = (char*) 0xb8000;
		
		for(i = 0; hw[i] != '\0'; i++)
		{
			video[ i * 2] = hw[i];
			
			video[ i * 2 + 1] = 0x07;
		}
}

void kernel_main(void)
{
	video();
	while(true)
	{
		
	}
}

extern "C"
{
	void init(void)
	{
		kernel_main();
	}
}