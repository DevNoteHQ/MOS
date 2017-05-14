
#ifndef INIT_IDT_H
#define INIT_IDT_H

namespace IDT
{
	typedef struct IDTDescr 
	{
		uint16_t offset_1; // offset bits 0..15
		uint16_t selector; // a code segment selector in GDT or LDT
		uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
		uint8_t flags; // type and attributes
		uint16_t offset_2; // offset bits 16..31
		uint32_t offset_3; // offset bits 32..63
		uint32_t zero;     // reserved
	} __attribute__((packed));
	typedef struct IDTR_t
	{
		uint16_t len;
		uint64_t addr;
	} __attribute__((packed));

	void init(void);
	void set(IDTDescr *descriptor, void(*handler)(void), uint8_t flags);
	
	extern "C" void idtr_install(IDTR_t *idtr);
}

#endif