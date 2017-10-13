
#include "keys.hpp"

#include <video/video.hpp>

#include <terminal/text.hpp>

namespace Keys
{
	void Init()
	{
		switch (Video::VideoMode)
		{
		case Video::Mode::Text:
			UpdateFocusedElement = Text::Keyboard::GetKeys;
			break;
		case Video::Mode::VGA:

			break;
		default:
			UpdateFocusedElement = Text::Keyboard::GetKeys;
			break;
		}
	}

	void(*UpdateFocusedElement)();

	Key A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
}