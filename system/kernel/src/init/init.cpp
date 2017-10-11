
//Library Includes:

//#include <libMOS.hpp> //TODO: Get the link to the lib working

//Kernel Includes:

#include "idt.hpp"
#include "gdt.hpp"
#include "tss.hpp"

#include <cpu/msr.hpp>
#include <cpu/CPUID.hpp>

#include <driver/keyboard/ps2/keyboard.hpp>

#include <libMOS/convert/convert.hpp>

#include <mm/vmm.hpp>

#include <multiboot.hpp>
#include <interrupt/init.hpp>
#include <terminal/text.hpp>

#define CPU_COUNT 8

namespace System
{
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

			Text::WriteLine("--------------------------------------------------------------------------------");
			Text::WriteLine("----------------  Hello! This is MOS - Modern Operating System  ----------------");
			Text::WriteLine("--------------------------------------------------------------------------------");
			Text::WriteLine("");
			Text::Write("Something> ");

			CPUID::GetCPUInfo();
			Interrupt::Init();
			CPUID::GetCPUInfo();

			asm volatile("sti");

			Driver::Keyboard::Init();

			while (true)
			{

			}

			asm volatile("hlt");
		}
	}
}