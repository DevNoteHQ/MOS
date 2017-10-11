
#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#ifdef __cplusplus

namespace IO
{
	void outb(uint16_t port, uint8_t  data);
	void outw(uint16_t port, uint16_t data);
	void outl(uint16_t port, uint32_t data);

	uint8_t  inb(uint16_t port);
	uint16_t inw(uint16_t port);
	uint32_t inl(uint16_t port);
}

#endif
#endif