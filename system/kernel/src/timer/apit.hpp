
#ifndef TIMER_APIT_HPP
#define TIMER_APIT_HPP

namespace Timer::APIT {
	extern uint32_t Ticks10ms;
	void Calibrate();
	void Delay(uint32_t delayInMs);
}

#endif