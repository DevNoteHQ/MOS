
#include "pit.hpp"

namespace Timer::PIT {
	uint16_t Delay;
	void(*Interrupt)();

	void TimeDelay(uint16_t ms) {
		Interrupt = &IRQDelay;
		Delay = ms;
		IRQDelay();

		while (Delay > 0) {
			asm volatile("nop");
		}
	}

	void IRQDelay() {
		uint16_t Counter = 0;
		if (Delay > 50) {
			Counter = (1193182 * 50) / 1000;
			IO::outb(0x43, 0x30);
			IO::outb(0x40, Counter & 0xFF);
			IO::outb(0x40, Counter >> 8);
			Delay -= 50;
		} else {
			Counter = (1193182 * Delay) / 1000;
			IO::outb(0x43, 0x30);
			IO::outb(0x40, Counter & 0xFF);
			IO::outb(0x40, Counter >> 8);
			Interrupt = &Finish;
		}
	}

	void Finish() {
		Interrupt = 0;
		Delay = 0;
	}
}