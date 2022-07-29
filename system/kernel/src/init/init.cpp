
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
#include <utility/convert/convert.hpp>
#include <utility/base/string.hpp>
#include <utility/system/info.hpp>
#include <scheduler/scheduler.hpp>
#include <syscall/syscall.hpp>
#include <timer/apit.hpp>
#include <timer/pit.hpp>
#include <video/console.hpp>

#include <common.hpp>

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

			char Test[70];
			Convert::ToString(System::Info::EndAddress, Test, 16);
			Console::WriteLine("EndAddress: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.Next4K, Test, 16);
			Console::WriteLine("Next4K: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.End4K, Test, 16);
			Console::WriteLine("End4K: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.Next2M, Test, 16);
			Console::WriteLine("Next2M: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.End2M, Test, 16);
			Console::WriteLine("End2M: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.Next1G, Test, 16);
			Console::WriteLine("Next1G: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.End1G, Test, 16);
			Console::WriteLine("End1G: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.Next512G, Test, 16);
			Console::WriteLine("Next512G: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) vmmAddresses.End512G, Test, 16);
			Console::WriteLine("End512G: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) VMM::GetRecursiveTableEntryAddress(511,510,0,0), Test, 16);
			Console::WriteLine("GetAddress: ");
			Console::WriteLine(Test);
			uint8_t *Stack = VMM::Kernel.Alloc4K(PG_PRESENT | PG_WRITABLE);
			Convert::ToString((uint64_t) Stack, Test, 16);
			Console::WriteLine("New Stack End: ");
			Console::WriteLine(Test);
			Convert::ToString((uint64_t) &Stack[4095], Test, 16);
			Console::WriteLine("New Stack Start: ");
			Console::WriteLine(Test);
			Scheduler::scheduler.init((uint64_t) &Stack[4095]);
			Timer::APIT::Delay(1000);

			while (true) {
				asm volatile("hlt");
			}
		}
	}
}