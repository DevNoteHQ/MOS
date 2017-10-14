
#include "keys.hpp"

#include <terminal/shell.hpp>

namespace Keys
{
	void Init()
	{
		UpdateFocusedElement = &Shell::GetKeys;
	}

	void(*UpdateFocusedElement)(uint8_t, uint32_t, uint8_t);
}