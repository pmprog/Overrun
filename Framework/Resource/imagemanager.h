
#pragma once

#include <list>
#include <string>

#ifndef ALLEGRO_BITMAP
struct ALLEGRO_BITMAP;
#endif

typedef struct ImageCache
{
	std::string* Path;
	double LastAccess;
	ALLEGRO_BITMAP* Image;
} ImageCache;


class ImageManager
{
	private:
		std::list<ImageCache*> Cached;

		void RemoveCached( ImageCache* item );

	public:
		double CacheTime;

		ImageManager();
		~ImageManager();

		ALLEGRO_BITMAP* GetImage(std::string Filename);

		void Tidy();
};