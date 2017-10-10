
#ifndef INTERRUPT_INIT_H
#define INTERRUPT_INIT_H

namespace Interrupt
{
	void Init();

	namespace PIC
	{
		void Init();
		void Activate();
		void Disable();
	}
	namespace APIC
	{
		void Init();
		extern bool bX2APIC;
	}
	namespace IOAPIC
	{
		void Init();
	}
}
#endif