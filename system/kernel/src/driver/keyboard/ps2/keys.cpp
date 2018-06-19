
#include "keys.hpp"
#include "table/one.hpp"
#include "table/two.hpp"
#include "table/three.hpp"

#include <video/console.hpp>

namespace Keys
{
	void Init()
	{
		UpdateFocusedElement = &GetKeys;
	}
	
	char ScanCode(uint8_t iTable, uint32_t iFlags, uint8_t iCode)
	{
		switch (iTable)
		{
		case 1:  return Table::One  (iFlags, iCode); break;
		case 2:  return Table::Two  (iFlags, iCode); break;
		case 3:	 return Table::Three(iFlags, iCode); break;
		default: return Table::One  (iFlags, iCode); break;
		}
	}
	
	void GetKeys(uint8_t iTable, uint32_t iFlags, uint8_t iCode)
	{
		Console::Write(Keys::ScanCode(iTable, iFlags, iCode));
	}

	void(*UpdateFocusedElement)(uint8_t, uint32_t, uint8_t);
}