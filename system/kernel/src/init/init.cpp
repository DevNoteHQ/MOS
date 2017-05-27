
//Library Includes:

//#include <libMOS.hpp> //TODO: Get the link to the lib working

//Kernel Includes:

#include <scheduler/scheduler.hpp>
#include <mm/vmm.hpp>
#include <terminal/text.hpp>
#include <multiboot.hpp>
#include <cpu/msr.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>
#include <libMOS/convert/convert.hpp>

#include "idt.hpp"
#include "gdt.hpp"
#include "tss.hpp"

#define CPU_COUNT 8

namespace System
{
	void kernel_main()
	{
		Text::BackgroundColor(Color::Blue);
		Text::UpdateScreenColor();
		Text::WriteLine("Hello!");
		Text::WriteLine("Stinker!");

		scheduler CPUscheduler[CPU_COUNT];
		for (int i = 0; i < CPU_COUNT; i++)
		{
			CPUscheduler[i].init();
		}
		while (true)
		{
			asm volatile("hlt");
		}
	}

	extern "C"
	{
		void init(uint32_t magic, multiboot_t *multiboot)
		{
			Paging::init();
			multiboot = Paging::ToVMA_V(multiboot);

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