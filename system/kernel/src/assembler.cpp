
#include <assembler.hpp>

namespace Assembler
{
	namespace IO
	{
		inline void outb(uint16_t port, uint8_t  data)
		{
			asm volatile("outb %%al, %%dx" :: "d" (port), "a" (data));
		}
		inline void outw(uint16_t port, uint16_t data)
		{
			asm volatile("outw %%ax, %%dx" :: "d" (port), "a" (data));
		}
		inline void outl(uint16_t port, uint32_t data)
		{
			asm volatile("outl %%eax, %%dx" :: "d" (port), "a" (data));
		}
		inline void outq(uint16_t port, uint64_t data)
		{
			asm volatile("outq %%rax, %%dx" :: "d" (port), "a" (data));
		}

		inline uint8_t  inb(uint16_t port)
		{
			uint8_t data; 
			asm volatile("inb %%dx, %%al" : "=a" (data) : "d" (port));
			return data;
		}
		inline uint16_t inw(uint16_t port)
		{
			uint16_t data;
			asm volatile("inw %%dx, %%ax" : "=a" (data) : "d" (port));
			return data;
		}
		inline uint32_t inl(uint16_t port)
		{
			uint32_t data;
			asm volatile("inl %%dx, %%eax" : "=a" (data) : "d" (port));
			return data;
		}
		inline uint64_t inq(uint16_t port)
		{
			uint64_t data;
			asm volatile("inq %%dx, %%rax" : "=a" (data) : "d" (port));
			return data;
		}
	}
}