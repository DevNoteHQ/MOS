
#ifndef TERMINAL_CONSOLE_HPP
#define TERMINAL_CONSOLE_HPP

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

	void ForegroundColor(Color color);

	void BackgroundColor(Color color);

	void Putc(char cC);

	void UpdateScreenColor();

	void GetKeys(uint8_t iTable, uint32_t iFlags, uint8_t iCode);
}

#endif