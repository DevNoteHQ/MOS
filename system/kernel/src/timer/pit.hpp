
#ifndef TIMER_PIT_HPP
#define TIMER_PIT_HPP

namespace Timer::PIT
{
	extern void(*Interrupt)();
	void TimeDelay(uint16_t ms);
	void IRQDelay();
	void Finish();
}

#endif