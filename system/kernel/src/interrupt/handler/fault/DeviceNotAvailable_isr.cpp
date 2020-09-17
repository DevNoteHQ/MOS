
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>

namespace Interrupt::Handler {
	void DeviceNotAvailable(CPU::State *state) {
		Console::Write("\nFAULT: Device Not Available!");
		asm volatile("hlt");
	}
}
