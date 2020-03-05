
#include "idt.hpp"
#include "gdt.hpp"
#include "tss.hpp"

#include <cpu/cpu.hpp>
#include <cpu/msr.hpp>
#include <cpuid/CPUID.hpp>
#include <driver/keyboard/ps2/keyboard.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>
#include <mm/pmm/pmm.hpp>
#include <mm/vmm/init.hpp>
#include <mm/vmm/conv.hpp>
#include <mm/heap/heap.hpp>
#include <multiboot.hpp>
#include <utility/convert/convert.hpp>
#include <utility/base/string.hpp>
#include <utility/system/info.hpp>
#include <scheduler/init.hpp>
#include <syscall/syscall.hpp>
#include <timer/apit.hpp>
#include <timer/pit.hpp>
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

			IDT::Init();
			GDT::Init();
			TSS::Init();

			CPUID::GetCPUInfo();
			Interrupt::Init();
			
			Driver::Keyboard::Init();
			Syscall::Init();

			asm volatile("sti");

			Scheduler::Init();

			char Test[70];
			register char* StackPointer asm ("rsp");
			uint64_t *PML4T = VMM::GetAddress(511,511,511,509);
			VMM::AddressIndexes AI;
			AI = VMM::GetAddress(System::Info::StackStartAddress);
			uint64_t *Address = VMM::GetAddress(511, 510, 1, 0);
			Convert::ToString((uint64_t) Timer::APIT::Ticks10ms, Test, 16);
			Console::WriteLine(Test);
			char Test2[] = "Hello World! This is a tutorial for Alexandra!";
			Console::WriteLine(Test2);

			while (true)
			{
				asm volatile("hlt");
			}
		}
	}
}