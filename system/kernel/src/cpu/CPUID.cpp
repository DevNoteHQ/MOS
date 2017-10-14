
#include "CPUID.hpp"
#include <libMOS/convert/convert.hpp>
#include <terminal/console.hpp>

namespace CPUID
{
	uint32_t CPUID_0[4][4];
	uint32_t CPUID_8[5][4];
	char cVendor[12];
	void GetCPUInfo()
	{
		for (int i = 0; i < 4; i++)
		{
			cpuid(i, CPUID_0[i][0], CPUID_0[i][1], CPUID_0[i][2], CPUID_0[i][3]);
		}
		for (int i = 0; i < 5; i++)
		{
			cpuid((i + 0x80000000), CPUID_8[i][0], CPUID_8[i][1], CPUID_8[i][2], CPUID_8[i][3]);
		}
		cVendor[0] =  (CPUID_0[0][1]) & 0xFF;
		cVendor[1] =  (CPUID_0[0][1] >> 8) & 0xFF;
		cVendor[2] =  (CPUID_0[0][1] >> 16) & 0xFF;
		cVendor[3] =  (CPUID_0[0][1] >> 24) & 0xFF;
		cVendor[4] =  (CPUID_0[0][3]) & 0xFF;
		cVendor[5] =  (CPUID_0[0][3] >> 8) & 0xFF;
		cVendor[6] =  (CPUID_0[0][3] >> 16) & 0xFF;
		cVendor[7] =  (CPUID_0[0][3] >> 24) & 0xFF;
		cVendor[8] =  (CPUID_0[0][2]) & 0xFF;
		cVendor[9] =  (CPUID_0[0][2] >> 8) & 0xFF;
		cVendor[10] = (CPUID_0[0][2] >> 16) & 0xFF;
		cVendor[11] = (CPUID_0[0][2] >> 24) & 0xFF;
	}
	void PasteCPUVendor()
	{
		Console::WriteLine("\nCPU Vendor String:");
		Console::WriteLine(cVendor);
		Console::WriteLine("");
	}
}