
#include "apit.hpp"
#include "pit.hpp"

#include <interrupt/apic.hpp>

namespace Timer::APIT
{
	uint32_t Ticks10ms;
	void Calibrate()
	{
		Interrupt::APIC::Write(APIC_LVT_TIMER, LVT_MASKED | LVT_TIMER_ONE_SHOT);
		Interrupt::APIC::Write(APIC_TIMER_DCR, DCR_16);
		Interrupt::APIC::Write(APIC_TIMER_ICR, 0xFFFFFFFF);
		Timer::PIT::TimeDelay(10);
		Interrupt::APIC::Write(APIC_LVT_TIMER, LVT_MASKED);
		Ticks10ms = 0xFFFFFFFF - Interrupt::APIC::Read(APIC_TIMER_CCR);

	}
}