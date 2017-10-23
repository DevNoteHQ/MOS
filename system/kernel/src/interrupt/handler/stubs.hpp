

#include <cpu/cpu.hpp>

#ifndef INTERRUPT_HANDLER_STUBS_HPP
#define INTERRUPT_HANDLER_STUBS_HPP

extern "C"
{
	void fault0();
	void fault1();
	void fault2();
	void fault3();
	void fault4();
	void fault5();
	void fault6();
	void fault7();
	void fault8();
	void fault9();
	void fault10();
	void fault11();
	void fault12();
	void fault13();
	void fault14();
	void fault15();
	void fault16();
	void fault17();
	void fault18();
	void fault19();
	void fault20();
	void fault21();
	void fault22();
	void fault22();
	void fault23();
	void fault24();
	void fault25();
	void fault26();
	void fault27();
	void fault28();
	void fault29();
	void fault30();
	void fault31();

	void irq0();
	void irq1();
	void irq2();
	void irq3();
	void irq4();
	void irq5();
	void irq6();
	void irq7();
	void irq8();
	void irq9();
	void irq10();
	void irq11();
	void irq12();
	void irq13();
	void irq14();
	void irq15();
	void irq16();
	void irq17();
	void irq18();
	void irq19();
	void irq20();
	void irq21();
	void irq22();
	void irq23();

	void ipi_route();
	void ipi_panic();
	void ipi_tlb();
	void lvt_timer();
	void lvt_error();
	void spurious();
}

#endif