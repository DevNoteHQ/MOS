
#include <assembler.hpp>

namespace IO {
	void outb(uint16_t port, uint8_t  data) {
		asm volatile("outb %%al, %%dx" :: "d" (port), "a" (data));
	}
	void outw(uint16_t port, uint16_t data) {
		asm volatile("outw %%ax, %%dx" :: "d" (port), "a" (data));
	}
	void outl(uint16_t port, uint32_t data) {
		asm volatile("outl %%eax, %%dx" :: "d" (port), "a" (data));
	}

	uint8_t  inb(uint16_t port) {
		uint8_t data;
		asm volatile("inb %%dx, %%al" : "=a" (data) : "d" (port));
		return data;
	}
	uint16_t inw(uint16_t port) {
		uint16_t data;
		asm volatile("inw %%dx, %%ax" : "=a" (data) : "d" (port));
		return data;
	}
	uint32_t inl(uint16_t port) {
		uint32_t data;
		asm volatile("inl %%dx, %%eax" : "=a" (data) : "d" (port));
		return data;
	}
}