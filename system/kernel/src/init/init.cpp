
//Library Includes:

//#include <libMOS.hpp> //TODO: Get the link to the lib working

//Kernel Includes:

#include "idt.hpp"
#include "gdt.hpp"
#include "tss.hpp"

#include <cpu/msr.hpp>
#include <cpu/CPUID.hpp>
#include <driver/keyboard/ps2/keyboard.hpp>
#include <interrupt/init.hpp>
#include <keys/keys.hpp>
#include <libMOS/convert/convert.hpp>
#include <mm/vmm.hpp>
#include <multiboot.hpp>
#include <terminal/console.hpp>
#include <terminal/shell.hpp>

#include <common.hpp>

namespace System
{
	extern "C"
	{
		void Init(uint32_t magic, multiboot_t *multiboot)
		{
			Paging::Init();
			multiboot = Paging::ToVMA_V(multiboot);

			CPUID::GetCPUInfo();
			Console::Init();

			IDT::Init();
			GDT::Init();
			TSS::Init();

			Interrupt::Init();
			CPUID::GetCPUInfo();

			Driver::Keyboard::Init();
			Keys::Init();

			Shell::Init();

			char cAddress[70];
			Convert::ToString(&_end, cAddress, 2);
			Shell::WriteLine(cAddress);

			asm volatile("sti");

			while (true)
			{
				asm volatile("hlt");
			}
		}
	}
}