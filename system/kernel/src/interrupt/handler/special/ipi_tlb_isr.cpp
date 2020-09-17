
#include <video/console.hpp>
#include <interrupt/handler/stubs.hpp>
#include <interrupt/apic.hpp>

namespace Interrupt::Handler {
	void IPI_Tlb(CPU::State *state) {
		Console::WriteLine("Interrupt");
		
		Interrupt::APIC::Write(APIC_EOI, 0);
	}
}