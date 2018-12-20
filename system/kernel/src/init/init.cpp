
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
#include <mm/pmm/pmm.hpp>
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

			VMM::KernelDirectory.Map2M(HVMA, 0x200000, PG_BIG | PG_PRESENT | PG_WRITABLE);
			uint64_t *PML4E = VMM::KernelDirectory.PML4T[510];
			uint64_t *PDPTE = *(uint64_t *)((uint64_t)PML4E & ~0xFFF);
			uint64_t *PDE = *(uint64_t *)((uint64_t)PDPTE & ~0xFFF);

			//Put in Information File or something like that
			uint64_t Start = (uint64_t)&_start;
			uint64_t End = (uint64_t)&_end;
			uint64_t KernelLengh = End - Start;
			char Test[70];
			Convert::ToString((uint64_t) PDE, Test, 16);
			Console::WriteLine(Test);

			asm volatile("sti");

			while (true)
			{
				asm volatile("hlt");
			}
		}
	}
}