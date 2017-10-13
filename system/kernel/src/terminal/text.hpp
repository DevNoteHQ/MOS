
#ifndef TERMINAL_TEXT_H
#define TERMINAL_TEXT_H

namespace Text
{
	// Konstruktor
	void Init();

	// Leeren des Bildschirms, die Größe beträgt 80x25 Zeichen
	void Clear();

	void Cursor();

	// Textausgabe
	void Write(const char* s);

	void WriteLine(const char* s);

	// Vordergrundfarbe setzen
	void ForegroundColor(Color color);

	// Hintergrundfarbe setzen
	void BackgroundColor(Color color);

	// Ausgabe eines einzelnen Zeichens
	void Putc(char cC);

	void Scroll();

	void UpdateScreenColor();
}

#endif