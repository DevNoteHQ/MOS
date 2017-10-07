
#ifndef INTERRUPT_INIT_H
#define INTERRUPT_INIT_H

namespace Interrupt
{
	namespace APIC
	{
		void init();
	}
	namespace IOAPIC
	{
		void init();
	}
}
#endif