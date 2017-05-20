
#include <mm/vmm.hpp>
#include <mm/common.hpp>

#define PL2E 512 //512 --> 512 * 2MB Pages per PL3 Entry --> 512 * 16 * 2MB Pages per Process
#define PL3E 16  //16 --> 16 GB max Pages per Process. 512 is just to big.
#define PL4E 512 //512 --> PID of the running process --> 512 processes possible

#define PL2INITFLAGS 0b00001000000
#define PL3INITFLAGS 0b00000000001
#define PL4INITFLAGS 0b00000000001

namespace Paging
{
	uint64_t PL2[PL4E][PL3E][PL2E];
	uint64_t PL3[PL4E][PL3E];
	uint64_t PL4[PL4E];

	void init(void)
	{
		for (int i4 = 0; i4 <= PL4E; i4++)
		{
			PL4[i4] = ((((uint64_t) &PL3 + i4 * PL3E) << 12) | PL4INITFLAGS);
			for (int i3 = 0; i3 <= PL3E; i3++)
			{
				PL3[i4][i3] = ((((uint64_t) &PL2 + i4 * PL3E * PL2E + i3 * PL2E) << 12) | PL3INITFLAGS);
				for (int i2 = 0; i2 <= PL2E; i2++)
				{
					PL2[i4][i3][i2] = 0 | PL2INITFLAGS;
				}
			}
		}
	}
}