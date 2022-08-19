
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
#include <mm/vmm/vmm.hpp>
#include <mm/heap/heap.hpp>
#include <multiboot.hpp>
#include <scheduler/scheduler.hpp>
#include <syscall/syscall.hpp>
#include <timer/apit.hpp>
#include <timer/pit.hpp>

#include <common.hpp>

#include <utility/base/string.hpp>
#include <utility/system/info.hpp>

#include <video/console.hpp>

namespace System {
	extern "C" {
		void Init(uint32_t magic, multiboot_t *multiboot) {
			multiboot = VMM::ToVMA_V(multiboot);

			VMM::VMMAddresses vmmAddresses = VMM::Init();
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

			Timer::APIT::Calibrate();

			Console::WriteLine("EndAddress: ");
			Console::WriteLine(System::Info::EndAddress, 16);
			Console::WriteLine("Next4K: ");
			Console::WriteLine(vmmAddresses.Next4K, 16);
			Console::WriteLine("End4K: ");
			Console::WriteLine(vmmAddresses.End4K, 16);
			Console::WriteLine("Next2M: ");
			Console::WriteLine(vmmAddresses.Next2M, 16);
			Console::WriteLine("End2M: ");
			Console::WriteLine(vmmAddresses.End2M, 16);
			Console::WriteLine("Next1G: ");
			Console::WriteLine(vmmAddresses.Next1G, 16);
			Console::WriteLine("End1G: ");
			Console::WriteLine(vmmAddresses.End1G, 16);
			Console::WriteLine("Next512G: ");
			Console::WriteLine(vmmAddresses.Next512G, 16);
			Console::WriteLine("End512G: ");
			Console::WriteLine(vmmAddresses.End512G, 16);
			Console::WriteLine("GetAddress: ");
			Console::WriteLine(VMM::GetRecursiveTableEntryAddress(511,510,0,0), 16);
			uint8_t *Stack = VMM::Kernel.Alloc4K(PG_PRESENT | PG_WRITABLE);
			Console::WriteLine("New Stack End: ");
			Console::WriteLine(Stack, 16);
			Console::WriteLine("New Stack Start: ");
			Console::WriteLine(&Stack[4095], 16);
			Scheduler::scheduler.init((uint64_t) &Stack[4095]);
			Console::WriteLine(STD::String("test"));
			Timer::APIT::Delay(1000);

			while (true) {
				asm volatile("hlt");
			}
		}
	}
}