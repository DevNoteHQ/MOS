
//Library Includes:



//Kernel Includes:

#include <scheduler/scheduler.hpp>
#include <mm/phy32.hpp>
#include <terminal/text.hpp>
#include <multiboot.h>
#include <init/idt.hpp>
#include <init/gdt.hpp>
#include <init/tss.hpp>
#include <cpu/msr.hpp>
#include <interrupt/apic.hpp>
#include <interrupt/init.hpp>

#define CPU_COUNT 8

void kernel_main(void)
{
	asm volatile("int $0x00");

	Text::Simple::Write(" Hello Fault!");

	scheduler CPU[CPU_COUNT];
	for(int i = 0; i < CPU_COUNT; i++)
	{
		CPU[i].init();
	}
	while (true)
	{

	}
}

extern "C"
{
	void init(uint32_t magic, multiboot_t *multiboot)
	{
		multiboot = phy32_to_virt(multiboot);

		GDT::remake();
		IDT::init();
		//TSS::init();

		Text::init();

		Interrupt::APIC::init();

		//asm volatile("sti");
		kernel_main();
	}
}