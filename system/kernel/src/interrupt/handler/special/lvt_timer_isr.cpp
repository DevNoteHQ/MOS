
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/apic.hpp>
#include <scheduler/scheduler.hpp>

namespace Interrupt::Handler {
	void LVT_Timer(CPU::State *state) {
		Scheduler::scheduler.executeNextTask(*state);

		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}