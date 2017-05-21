
//Library Includes:



//Kernel Includes:

#include <scheduler/scheduler.hpp>
#include <mm/vmm.hpp>
#include <terminal/text.hpp>
#include <multiboot.h>
#include <init/idt.hpp>
#include <init/gdt.hpp>
#include <init/tss.hpp>
#include <cpu/msr.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>
//#include <libMOS.hpp> TODO: Get the link to the lib working

#define CPU_COUNT 8

namespace main
{
	void kernel_main(void)
	{
		for (int i; i < 300; i++)
		{
			Text::Write("Hello! ");
		}

		scheduler CPUscheduler[CPU_COUNT];
		for (int i = 0; i < CPU_COUNT; i++)
		{
			CPUscheduler[i].init();
		}
		while (true)
		{

		}
	}

	extern "C"
	{
		void init(uint32_t magic, multiboot_t *multiboot)
		{
			//multiboot = phy32_to_virt(multiboot);
			GDT::remake();
			IDT::init();
			//TSS::init();

			Paging::init();

			Text::init();

			Interrupt::APIC::init();

			//asm volatile("sti");
			kernel_main();
		}
	}
}