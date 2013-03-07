
#include "imagemanager.h"
#include "../Core/main.h"

ImageManager::ImageManager()
{
	CacheTime = 120;
}

ImageManager::~ImageManager()
{
	ImageCache* fc;
	while( !Cached.empty() )
	{
		fc = Cached.back();
		Cached.pop_back();
		RemoveCached( fc );
	}
}

ALLEGRO_BITMAP* ImageManager::GetImage(std::string Filename)
{
	ImageCache* fc;

	if( !Cached.empty() )
	{
		for( std::list<ImageCache*>::iterator i = Cached.begin(); i != Cached.end(); i++ )
		{
			fc = (*i);
			if( fc->Path->compare( Filename ) == 0 )
			{
				fc->LastAccess = al_get_time();
				return fc->Image;
			}
		}
	}

	fc = (ImageCache*)malloc( sizeof(ImageCache) );
	fc->Path = new std::string(Filename);
	fc->Image = al_load_bitmap( Filename.c_str() );
	fc->LastAccess = al_get_time();
	Cached.push_front( fc );

	return fc->Image;
}

void ImageManager::Tidy()
{
	ImageCache* fc;
	if( !Cached.empty() )
	{
		for( std::list<ImageCache*>::reverse_iterator i = Cached.rbegin(); i != Cached.rend(); i++ )
		{
			fc = (*i);
			if( al_get_time() - fc->LastAccess > CacheTime )
			{
				Cached.remove( fc );
				RemoveCached( fc );
			}
		}
	}
}

void ImageManager::RemoveCached( ImageCache* item )
{
	al_destroy_bitmap( item->Image );
	delete item->Path;
	free( (void*)item );
}