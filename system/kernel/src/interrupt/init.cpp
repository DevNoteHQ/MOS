
#include "init.hpp"
#include "common.hpp"

#include <cpu/CPUID.hpp>
#include <cpu/msr.hpp>
#include <libMOS/convert/convert.hpp>
#include <terminal/text.hpp>

namespace Interrupt
{
	void Init()
	{
		if (!(CPUID::CPUID_0[1][3] & CPUID::EAX1::EDX_APIC))
		{
			PIC::Init();
			PIC::Activate();
		}
		else
		{
#ifndef FORCE_PIC
			PIC::Init();
			PIC::Disable();
			APIC::Init();
#else
			PIC::Init();
			PIC::Activate();
#endif
		}
	}

	namespace PIC
	{
		void Init()
		{
			Text::WriteLine("Initialising PIC...");

			//Master-PIC
			IO::outb(PIC1, ICW1_INIT);
			IO::outb(PIC1_DATA, IRQ00);
			IO::outb(PIC1_DATA, 0x4);
			IO::outb(PIC1_DATA, ICW1_ICW4);
			//Slave-PIC
			IO::outb(PIC2, ICW1_INIT);
			IO::outb(PIC2_DATA, IRQ08);
			IO::outb(PIC2_DATA, 0x2);
			IO::outb(PIC2_DATA, ICW1_ICW4);

			//Set PIT in One-Shot Mode
			//IO::outb(0x43, 0x30);
		}

		void Activate()
		{
			Text::WriteLine("Activating PIC...");

			//Alle IRQs aktivieren
			IO::outb(PIC1_DATA, 0x0);
			IO::outb(PIC2_DATA, 0x0);
		}

		void Disable()
		{
			Text::WriteLine("Disabling PIC...");

			//Alle IRQs aktivieren
			IO::outb(PIC1_DATA, 0xFF);
			IO::outb(PIC2_DATA, 0xFF);
		}
	}

	namespace APIC
	{
		bool bX2APIC = true;

		void Write(size_t reg, uint64_t val)
		{
			if (bX2APIC == true)
				msr_write(MSR_X2APIC_MMIO + reg, val);
			else
			{
				//apic_mmio[reg * 4] = val;
			}
		}

		void Init()
		{
			Text::WriteLine("Initialising APIC...");
			if (!(CPUID::CPUID_0[1][2] & CPUID::EAX1::ECX_x2APIC))
			{
				bX2APIC = false;
				Text::WriteLine("Your CPU doesn't support x2APIC! None-x2APIC-Mode currently not supported!");
				abort();
			}
			else
			{
				uint64_t base = msr_read(MSR_APIC_BASE) | APIC_BASE_ENABLED | APIC_BASE_X2_MODE;
				msr_write(MSR_APIC_BASE, base);
			}

			//Set the Spurious Interrupt Vector Register
			Write(APIC_SVR, SVR_ENABLED | SPURIOUS);
			//Set the Task Priority Register
			Write(APIC_TPR, 0);
			//Clear Errors
			Write(APIC_ESR, 0);
			//Set the Local Vector Table Registers
			Write(APIC_TIMER_DCR, 1);
			Write(APIC_LVT_TIMER, LVT_TIMER | LVT_TIMER_PERIODIC);
			Write(APIC_TIMER_ICR, 0xFFFFFF);
			Write(APIC_LVT_ERROR, LVT_TYPE_FIXED | LVT_ERROR);
			//Write(APIC_LVT_LINT0, WERT);
			//Write(APIC_LVT_LINT1, WERT);

			//Send EOI
			Write(APIC_EOI, 0);
		}
	}
	namespace IOAPIC
	{
		void Init()
		{
			Text::WriteLine("Initialising IO-APIC...");
		}
	}
}