
//Library Includes:



//Kernel Includes:

#include <scheduler/scheduler.hpp>
#include <mm/vmm.hpp>
#include <terminal/text.hpp>
#include <multiboot.hpp>
#include <init/idt.hpp>
#include <init/gdt.hpp>
#include <init/tss.hpp>
#include <cpu/msr.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>
#include <libMOS/convert/convert.hpp>
//#include <libMOS.hpp> //TODO: Get the link to the lib working

#define CPU_COUNT 8

namespace System
{
	void kernel_main(void)
	{
		uint64_t iInt = 150;
		char sZahl[20];
		Convert::OldToString(iInt, sZahl);
		Text::Write(sZahl);
		Text::Write(" Hello!");

		abort();

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
			abort();
			Paging::init();

			//multiboot = phy32_to_virt(multiboot);
			GDT::remake();
			IDT::init();
			//TSS::init();

			Text::init();

			Interrupt::APIC::init();

			//asm volatile("sti");
			kernel_main();
		}
	}
}