
#ifndef TERMINAL_TEXT_HPP
#define TERMINAL_TEXT_HPP

namespace Text
{
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