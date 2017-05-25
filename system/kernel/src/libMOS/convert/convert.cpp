
#include "convert.hpp"

static void Convert::OldToString(uint64_t iC, char sString[])
{
	char sBuffer[20];
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