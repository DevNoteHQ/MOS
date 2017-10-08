
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
#include <interrupt/init.hpp>
#include <scheduler/scheduler.hpp>
#include <terminal/text.hpp>

#define CPU_COUNT 8

namespace System
{
	namespace Kernel
	{
		void Main()
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
	}

	extern "C"
	{
		void Init(uint32_t magic, multiboot_t *multiboot)
		{
			Paging::Init();
			multiboot = Paging::ToVMA_V(multiboot);

			GDT::Remake();
			IDT::Init();
			//TSS::Init();

			Text::Init();

			CPUID::GetCPUInfo();
			Interrupt::Init();
			CPUID::GetCPUInfo();

			Text::WriteLine("--------------------------------------------------------------------------------");
			Text::WriteLine("----------------  Hello! This is MOS - Modern Operating System  ----------------");
			Text::WriteLine("--------------------------------------------------------------------------------");
			Text::WriteLine("");
			Text::Write("Something> ");

			//asm volatile("sti");

			Kernel::Main();
		}
	}
}