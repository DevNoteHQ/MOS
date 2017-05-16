
#ifdef __cplusplus
namespace Assembler
{
	namespace IO
	{
		inline void outb(uint64_t port, uint8_t  data);
		inline void outw(uint64_t port, uint16_t data);
		inline void outl(uint64_t port, uint32_t data);
		inline void outq(uint64_t port, uint64_t data);

		inline uint8_t  inb(uint64_t port);
		inline uint16_t inw(uint64_t port);
		inline uint32_t inl(uint64_t port);
		inline uint64_t inq(uint64_t port);
	}
}
#endif