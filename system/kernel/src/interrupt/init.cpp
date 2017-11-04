
#include "init.hpp"
#include "common.hpp"
#include "handler/handler.hpp"

#include <cpu/CPUID.hpp>
#include <cpu/msr.hpp>
#include <libMOS/convert/convert.hpp>

namespace Interrupt
{
	void Init()
	{
		Handler::SetDefault();

		if (!(CPUID::CPUID_0[1][3] & CPUID::EAX1::EDX_APIC))
		{
			PIC::Init();
			PIC::Activate();
		}
		else
		{
			PIC::Init();
			PIC::Activate();
			APIC::Init();
		}
	}

	namespace PIC
	{
		void Init()
		{
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
			IO::outb(0x43, 0x30);
		}

		void Activate()
		{
			//Alle IRQs aktivieren
			IO::outb(PIC1_DATA, 0x0);
			IO::outb(PIC2_DATA, 0x0);
		}

		void Disable()
		{
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
			if (!(CPUID::CPUID_0[1][2] & CPUID::EAX1::ECX_x2APIC))
			{
				bX2APIC = false;
				//abort();
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

			//Send EOI
			Write(APIC_EOI, 0);
		}
	}
	namespace IOAPIC
	{
		void Init()
		{
			PIC::Disable();
		}
	}
}