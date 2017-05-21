
#ifndef TERMINAL_TEXT_H
#define TERMINAL_TEXT_H

namespace Text
{
	// Konstruktor
	void init();

	// Leeren des Bildschirms, die Größe beträgt 80x25 Zeichen
	void Clear();

	void ClearBuffer();

	void Cursor();

	// Textausgabe
	void Write(const char* s);

	// Vordergrundfarbe setzen
	void ForegroundColor(Color color);

	// Hintergrundfarbe setzen
	void BackgroundColor(Color color);

	// Ausgabe eines einzelnen Zeichens
	void Putc(char cC);

	void Scroll();

	namespace Simple
	{
		void Putc(char cC);
		void Write(const char* s);
	}
}

#endif