
//Library Includes:



//Kernel Includes:

#include <scheduler/scheduler.hpp>
#include <memorymanagement/phy32.hpp>
#include <terminal/text.hpp>
#include <multiboot.h>
#include <init/idt.hpp>
#include <init/msr.hpp>
#include <init/tss.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>

#define CPU_COUNT 8

void kernel_main(void)
{
	Text::Simple::Write("Hello Fault!");

	scheduler CPU[CPU_COUNT];
	for(int i = 0; i < CPU_COUNT; i++)
	{
		CPU[i].init();
	}
}

extern "C"
{
	void init()
	{
		IDT::init();

		Text::init();

		Interrupt::APIC::init();

		kernel_main();
	}
}