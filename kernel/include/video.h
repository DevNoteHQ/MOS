#ifndef VIDEO_H
#define VIDEO_H

#include "types.h"

namespace color
{
	enum type
	{
		black = 0x00,
		blue = 0x01,
		green = 0x02,
		cyan = 0x03,
		red = 0x04,
		magenta = 0x05,
		brown = 0x06,
		light_gray = 0x07,
		dark_gray = 0x08,
		light_blue = 0x09,
		light_green = 0x0A,
		light_cyan = 0x0B,
		light_red = 0x0C,
		light_magenta = 0x0D,
		yellow = 0x0E,
		white = 0x0F
	};
}

struct background
{
	inline background(color::type color)
		: m_color(color) {}

	color::type m_color;
};

class Video
{
public:
	// Konstruktor
	Video();

	// Destruktor
	~Video();

	// Leeren des Bildschirms, die Größe beträgt 80x25 Zeichen
	void clear();

	// Textausgabe
	Video& operator << (const char* s);

	// Vordergrundfarbe setzen
	Video& operator << (color::type color);

	// Hintergrundfarbe setzen
	Video& operator << (const background& color);

	// Ausgabe eines einzelnen Zeichens
	void put(char c);

private:
	// Zeiger auf den Videospeicher
	uint16_t* m_videomem;

	// Y-Position der Textausgabe, je volle Zeile +80
	unsigned int m_off;

	// X-Position der Textausgabe, ab Zeilenanfang
	unsigned int m_pos;

	// FB/BG-Farbe
	uint16_t m_color;
};

// Globale Instanz der Video-Klasse, Definition in Video.cpp
extern Video screen;

#endif