
#include <cpu/CPUID.h>

uint32_t unused;

namespace CPUID
{
	void printregs(int eax, int ebx, int ecx, int edx, char* string) 
	{
		int j;
		string[16] = '\0';
		for (j = 0; j < 4; j++) 
		{
			string[j] = eax >> (8 * j);
			string[j + 4] = ebx >> (8 * j);
			string[j + 8] = ecx >> (8 * j);
			string[j + 12] = edx >> (8 * j);
		}
	}
}