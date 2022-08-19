
#ifndef TERMINAL_CONSOLE_HPP
#define TERMINAL_CONSOLE_HPP

#define VIDEO_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25
#define PAGES 5

#include <utility/base/string.hpp>

namespace Console {
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

	template<uint64_t S>
	void Write(STD::String<S> string) {
		Write(string.data);
	}
	void Write(uint64_t value, uint8_t base);
	void Write(uint64_t value);
	void Write(void *value, uint8_t base);
	void Write(void *value);

	void WriteLine(const char* s);
	void WriteLine(char cC);

	template<uint64_t S>
	void WriteLine(STD::String<S> string) {
		WriteLine(string.data);
	}
	void WriteLine(uint64_t value, uint8_t base);
	void WriteLine(uint64_t value);
	void WriteLine(void *value, uint8_t base);
	void WriteLine(void *value);

	void ForegroundColor(Color color);

	void BackgroundColor(Color color);

	void Putc(char cC);

	void Scroll();

	void UpdateScreenColor();
}

#endif