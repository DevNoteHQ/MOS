
#include "convert.hpp"

namespace Convert
{
	void ToString(uint64_t iC, char sString[])
	{
		char sBuffer[100];
		int iX = 0;
		for (iX = 0; iC > 0; iX++)
		{
			sBuffer[iX] = iC % 10 + '0';
			iC /= 10;
		}
		iX--;
		for (int iY = 0; iX >= 0; iX--, iY++)
		{
			sString[iY] = sBuffer[iX];
		}
	}

	void ToString(uint64_t iC, char sString[], uint8_t iBase)
	{
		char sBuffer[70];
		int iX = 0;
		for (iX = 0; iC > 0; iX++)
		{
			sBuffer[iX] = iC % iBase + '0';
			iC /= iBase;
		}
		iX--;
		for (int iY = 0; iX >= 0; iX--, iY++)
		{
			sString[iY] = sBuffer[iX];
		}
	}
}