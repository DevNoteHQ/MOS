
//Library Includes:



//Kernel Includes:

#include <sheduler/sheduler.h>
#include <memorymanagement/phy32.h>
#include <terminal/text.h>
#include <multiboot.h>
#include <init/gdt.h>
#include <init/cpu.h>

#define CPU_COUNT 8

using namespace kernel;

void kernel_main(void)
{
	cpu::bsp_init();

	gdt::init();
	Text::init();
	for (int iC; iC < 15; iC++)
	{
		Text::Write(" | Hello | ");
	}
	
	sheduler CPU[CPU_COUNT];
	for(int i = 0; i < CPU_COUNT; i++)
	{
		CPU[i].init();
	}
}

extern "C"
{
	void init(uint32_t magic, multiboot_t *multiboot)
	{
		multiboot = phy32_to_virt(multiboot);
		kernel_main();
	}
}