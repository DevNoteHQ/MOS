
#include "convert.hpp"

static char* Convert::ToString(uint64_t iC)
{
	char sString[] = "                    ";
	Byte iBuffer = 0;
	int iX = 0;
	for (iX = 0; iC > 0; iX++)
	{
		iBuffer = iC % 10;
		iC /= 10;
		sString[iX] = iBuffer + 48;
	}
	sString[iX] = '\0';
	return sString;
}