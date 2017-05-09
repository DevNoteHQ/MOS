
//Library Includes:

#include <stddef.h>
#include <stdint.h>

//Kernel Includes:

#include <sheduler/sheduler.h>
#include <memorymanagement/phy32.h>

#define VIDEO_BUFFER 0xB8000
#define CPU_COUNT 8

using namespace kernel;

void kernel_main(void)
{
	const char hw[] = "Hello World!";
    int i;
    char *video;
	video = (char *) aphy32_to_virt(VIDEO_BUFFER);
 
    // C-Strings haben ein Nullbyte als Abschluss
    for (i = 0; hw[i] != '\0'; i++) 
	{
 
        // Zeichen i in den Videospeicher kopieren
        video[i * 2] = hw[i];
 
        // 0x07 = Hellgrau auf Schwarz
        video[i * 2 + 1] = 0x07;
    }
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