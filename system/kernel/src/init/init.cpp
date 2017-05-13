
//Library Includes:



//Kernel Includes:

#include <scheduler/scheduler.h>
#include <memorymanagement/phy32.h>
#include <terminal/text.h>
#include <multiboot.h>
#include <init/gdt.h>
#include <init/cpu.h>
#include <init/idt.h>

#define CPU_COUNT 8

void kernel_main(void)
{
	CPU::init();

	GDT::init();
	TSS::init();
	IDT::init();

	Text::init();
	for (int iC; iC < 250; iC++)
	{
		Text::Simple::Write(" | Hello | ");
	}
	
	scheduler CPU[CPU_COUNT];
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