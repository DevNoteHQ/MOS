
#include "keys.hpp"

#include <terminal/console.hpp>

namespace Keys
{
	void Init()
	{
		UpdateFocusedElement = &Console::GetKeys;
	}

	void(*UpdateFocusedElement)(uint8_t, uint32_t, uint8_t);
}