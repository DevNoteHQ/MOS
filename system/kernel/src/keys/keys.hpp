
#ifndef KEYS_KEYS_HPP
#define KEYS_KEYS_HPP

namespace Keys
{
	void Init();
	class Key
	{
	public:
		bool IsPressed;
		bool IsHeld;
		bool IsReleased;
	};

	extern void(*UpdateFocusedElement)();

	extern Key A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
}

#endif