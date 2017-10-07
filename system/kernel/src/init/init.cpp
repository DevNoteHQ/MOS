
//Library Includes:

//#include <libMOS.hpp> //TODO: Get the link to the lib working

//Kernel Includes:

#include "idt.hpp"
#include "gdt.hpp"
#include "tss.hpp"

#include <cpu/msr.hpp>
#include <cpu/CPUID.hpp>
#include <libMOS/convert/convert.hpp>
#include <mm/vmm.hpp>
#include <multiboot.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>
#include <scheduler/scheduler.hpp>
#include <terminal/text.hpp>

#define CPU_COUNT 8

namespace System
{
	void kernel_main()
	{
		scheduler CPUscheduler[CPU_COUNT];
		for (int i = 0; i < CPU_COUNT; i++)
		{
			CPUscheduler[i].init();
		}
		while (true)
		{

		}
		asm volatile("hlt");
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

			CPUID::GetCPUInfo();
			Interrupt::APIC::init();
			CPUID::GetCPUInfo();
			CPUID::PasteCPUVendor();

			Text::WriteLine("--------------------------------------------------------------------------------");
			Text::WriteLine("----------------  Hello! This is MOS - Modern Operating System  ----------------");
			Text::WriteLine("--------------------------------------------------------------------------------");
			Text::WriteLine("");
			Text::Write("Something> ");

			//asm volatile("sti");

			kernel_main();
		}
	}
}