
#include "common.hpp"
#include "init.hpp"

#include <cpu/CPUID.hpp>
#include <cpu/msr.hpp>
#include <libMOS/convert/convert.hpp>
#include <terminal/text.hpp>

#define MSR_X2APIC_MMIO 0x800

/* common registers */
#define APIC_TPR        0x08
#define APIC_EOI        0x0B
#define APIC_SVR        0x0F
#define APIC_ESR        0x28
#define APIC_LVT_TIMER  0x32
#define APIC_LVT_LINT0  0x35
#define APIC_LVT_LINT1  0x36
#define APIC_LVT_ERROR  0x37
#define APIC_TIMER_ICR  0x38
#define APIC_TIMER_CCR  0x39
#define APIC_TIMER_DCR  0x3E

/* xAPIC only registers */
#define XAPIC_ICRL      0x30
#define XAPIC_ICRH      0x31

/* x2APIC only registers */
#define X2APIC_ICR      0x30
#define X2APIC_SELF_IPI 0x3F

/* LVT flags */
#define LVT_MASKED			0x00010000
#define LVT_TYPE_FIXED		0x00000000
#define LVT_TYPE_SMI		0x00000200
#define LVT_TYPE_NMI		0x00000400
#define LVT_TYPE_EXTINT		0x00000700
#define LVT_DELIVS			0x00001000
#define LVT_REMOTE_IRR		0x00004000
#define LVT_TRIGGER_LEVEL	0x00008000
#define LVT_TRIGGER_EDGE	0x00000000
#define LVT_TIMER_TSC		0x00040000
#define LVT_TIMER_PERIODIC	0x00020000
#define LVT_TIMER_ONE_SHOT	0x00000000

/* SVR flags */
#define SVR_ENABLED 0x100

/* ICR flags */
#define ICR_TYPE_FIXED        0x00000000
#define ICR_TYPE_SMI          0x00000200
#define ICR_TYPE_NMI          0x00000400
#define ICR_TYPE_INIT         0x00000500
#define ICR_TYPE_STARTUP      0x00000600
#define ICR_PHYSICAL          0x00000000
#define ICR_LOGICAL           0x00000800
#define ICR_DELIVS            0x00001000
#define ICR_DEASSERT          0x00000000
#define ICR_ASSERT            0x00004000
#define ICR_TRIGGER_EDGE      0x00000000
#define ICR_TRIGGER_LEVEL     0x00008000
#define ICR_DEST_SELF         0x00040000
#define ICR_DEST_ALL          0x00080000
#define ICR_DEST_ALL_EXC_SELF 0x000C0000

/* DCR values */
#define DCR_1   0xB
#define DCR_2   0x0
#define DCR_4   0x1
#define DCR_8   0x2
#define DCR_16  0x3
#define DCR_32  0x8
#define DCR_64  0x9
#define DCR_128 0xA

#define PIC1			0x20
#define PIC2			0xA0
#define PIC1_COMMAND	PIC1
#define PIC1_DATA		(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA		(PIC2+1)

#define ICW1_ICW4		0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE		0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL		0x08		/* Level triggered (edge) mode */
#define ICW1_INIT		0x10		/* Initialization - required! */

#define ICW4_8086		0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO		0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM		0x10		/* Special fully nested (not) */

//#define FORCE_PIC

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
			Assembler::IO::outb(PIC1, ICW1_INIT);
			Assembler::IO::outb(PIC1_DATA, IRQ00);
			Assembler::IO::outb(PIC1_DATA, 0x4);
			Assembler::IO::outb(PIC1_DATA, ICW1_ICW4);
			//Slave-PIC
			Assembler::IO::outb(PIC2, ICW1_INIT);
			Assembler::IO::outb(PIC2_DATA, IRQ08);
			Assembler::IO::outb(PIC2_DATA, 0x2);
			Assembler::IO::outb(PIC2_DATA, ICW1_ICW4);
		}

		void Activate()
		{
			Text::WriteLine("Activating PIC...");

			//Alle IRQs aktivieren
			Assembler::IO::outb(PIC1_DATA, 0x0);
			Assembler::IO::outb(PIC2_DATA, 0x0);
		}

		void Disable()
		{
			Text::WriteLine("Disabling PIC...");

			//Alle IRQs aktivieren
			Assembler::IO::outb(PIC1_DATA, 0xFF);
			Assembler::IO::outb(PIC2_DATA, 0xFF);
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
				Text::WriteLine("Your CPU doesn't support x2APIC! Aborting!");
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
			Write(APIC_LVT_TIMER, LVT_TIMER);
			Write(APIC_TIMER_ICR, 0xFFFFFFF);
			Write(APIC_LVT_ERROR, LVT_TYPE_FIXED | LVT_ERROR);
			//Write(APIC_LVT_LINT0, WERT);
			//Write(APIC_LVT_LINT1, WERT);

			//Reset Priority


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