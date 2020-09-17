
#ifndef TERMINAL_TEXT_HPP
#define TERMINAL_TEXT_HPP

namespace Text {
	#ifdef __cplusplus

	enum class Color {
		Black = 0x00,
		Blue = 0x01,
		Green = 0x02,
		Cyan = 0x03,
		Red = 0x04,
		Magenta = 0x05,
		Brown = 0x06,
		LightGray = 0x07,
		DarkGray = 0x08,
		LightBlue = 0x09,
		LightGreen = 0x0A,
		LightCyan = 0x0B,
		LightRed = 0x0C,
		LightMagenta = 0x0D,
		Yellow = 0x0E,
		White = 0x0F
	};

	#endif

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

	void Scroll();

	void UpdateScreenColor();
}

#endif