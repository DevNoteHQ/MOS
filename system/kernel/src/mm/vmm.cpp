
#include <mm/vmm.hpp>
#include <common.hpp>

#define PL2E 512 //512 --> 512 * 2MB Pages per PL3 Entry --> 512 * 16 * 2MB Pages per Process
#define PL3E 16  //16 --> 16 GB max Pages per Process. 512 is just to big.
#define PL4E 512 //512 --> PID of the running process --> 512 processes possible

#define SIZE2M 0x000200000
#define SIZE1G 0x040000000

#define PG_PRESENT   0x1
#define PG_WRITABLE  0x2
#define PG_USER      0x4
#define PG_BIG       0x80
#define PG_NO_EXEC   0x8000000000000000
#define PG_ADDR_MASK 0xFFFFFFFFFF000

#define Proc_Kernel_VMA		0x000003E0000000 //The kernels base addres in each Process

#define PL2P 0x1F400000
#define PL3P 0x1FA00000
#define PL4P 0x1FC00000

namespace Paging
{
	uint64_t *PL2 = PL2P;
	uint64_t *PL3 = PL3P;
	uint64_t *PL4 = PL4P;

	void init(void)
	{
		
		//SetCR3((uint64_t) PL4);
	}
}