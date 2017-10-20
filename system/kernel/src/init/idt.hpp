
#ifndef INIT_IDT_HPP
#define INIT_IDT_HPP

namespace IDT
{
	typedef struct
	{
		uint16_t offset_1; // offset bits 0..15
		uint16_t selector; // a code segment selector in GDT or LDT
		uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
		uint8_t flags; // type and attributes
		uint16_t offset_2; // offset bits 16..31
		uint32_t offset_3; // offset bits 32..63
		uint32_t zero;     // reserved
	} __attribute__((packed)) Descriptor;
	typedef struct
	{
		uint16_t len;
		uint64_t addr;
	} __attribute__((packed)) IDTR_t;

	void Init(void);
	void Set(Descriptor *descriptor, void(*handler)(struct cpu_state *state), uint8_t flags);
	void Sete(Descriptor *descriptor, void(*handler)(struct cpu_state *state, uint64_t error), uint8_t flags);
	
	extern "C" void idtr_install(IDTR_t *idtr);
}

#endif