
#ifndef TERMINAL_CONSOLE_HPP
#define TERMINAL_CONSOLE_HPP

#include "text.hpp"

namespace Console
{
	enum Mode
	{
		Text,
		VGA,
		VESA,
		GUI
	};
	extern Mode VideoMode;

	void Init();

	void Clear();

	void Cursor();

	void Write(const char* s);
	void Write(char cC);

	void WriteLine(const char* s);
	void WriteLine(char cC);

	void ForegroundColor(Text::Color color);

	void BackgroundColor(Text::Color color);

	void Putc(char cC);

	void UpdateScreenColor();
}

#endif