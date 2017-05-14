
#ifndef INTERRUPT_INIT_H
#define INTERRUPT_INIT_H

namespace Interrupt
{
	namespace APIC
	{
		bool check();
		void init(void);
	}
	namespace IOAPIC
	{
		void init(void);
	}
}
#endif