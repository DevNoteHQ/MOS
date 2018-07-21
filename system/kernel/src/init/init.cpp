
#include "idt.hpp"
#include "gdt.hpp"
#include "tss.hpp"

#include <cpu/cpu.hpp>
#include <cpu/msr.hpp>
#include <cpuid/CPUID.hpp>
#include <driver/keyboard/ps2/keyboard.hpp>
#include <interrupt/init.hpp>
#include <utility/convert/convert.hpp>
#include <utility/base/string.hpp>
#include <mm/pmm/init.hpp>
#include <mm/vmm/init.hpp>
#include <mm/vmm/conv.hpp>
#include <mm/heap/heap.hpp>
#include <multiboot.hpp>
#include <syscall/syscall.hpp>
#include <video/console.hpp>

#include <common.hpp>

namespace System
{
	extern "C"
	{
		void Init(uint32_t magic, multiboot_t *multiboot)
		{
			multiboot = VMM::ToVMA_V(multiboot);
			VMM::Init();
			PMM::Init();
			Heap::Init();

			CPU::InitBSP();

			CPUID::GetCPUInfo();
			Console::Init();

			Interrupt::Init();

			IDT::Init();
			GDT::Init();
			TSS::Init();

			CPUID::GetCPUInfo();

			Driver::Keyboard::Init();
			Syscall::Init();

			asm volatile("sti");

			while (true)
			{
				asm volatile("hlt");
			}
		}
	}
}