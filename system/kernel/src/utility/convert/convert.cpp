
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
		if (iBase > 16) return;
		char sBuffer[65];
		int iX = 0;
		int iV = 0;
		for (iX = 0; iC > 0; iX++)
		{
			iV = iC % iBase;
			switch (iV)
			{
			case 10: sBuffer[iX] = 'A'; break;
			case 11: sBuffer[iX] = 'B'; break;
			case 12: sBuffer[iX] = 'C'; break;
			case 13: sBuffer[iX] = 'D'; break;
			case 14: sBuffer[iX] = 'E'; break;
			case 15: sBuffer[iX] = 'F'; break;
			default: sBuffer[iX] = iV + '0'; break;
			}
			iC /= iBase;
		}
		iX--;
		for (int iY = 0; iX >= 0; iX--, iY++)
		{
			sString[iY] = sBuffer[iX];
		}
	}
}