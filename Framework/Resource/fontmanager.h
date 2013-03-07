
#pragma once

#include <list>
#include <string>

#ifndef ALLEGRO_FONT
struct ALLEGRO_FONT;
#endif

typedef struct FontCache
{
	std::string* Path;
	int Size;
	int Flags;
	double LastAccess;
	ALLEGRO_FONT* Font;
} FontCache;


class FontManager
{
	private:
		std::list<FontCache*> Cached;
		
		void RemoveCached( FontCache* item );

	public:
		double CacheTime;

		FontManager();
		~FontManager();

		ALLEGRO_FONT* GetFont(std::string Filename, int Size, int Flags);

		void Tidy();
};