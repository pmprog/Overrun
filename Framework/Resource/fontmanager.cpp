
#include "fontmanager.h"
#include "../Core/main.h"

FontManager::FontManager()
{
	CacheTime = 120;
}

FontManager::~FontManager()
{
	FontCache* fc;
	while( !Cached.empty() )
	{
		fc = Cached.back();
		Cached.pop_back();
		RemoveCached( fc );
	}
}

ALLEGRO_FONT* FontManager::GetFont(std::string Filename, int Size, int Flags)
{
	FontCache* fc;

	if( !Cached.empty() )
	{
		for( std::list<FontCache*>::iterator i = Cached.begin(); i != Cached.end(); i++ )
		{
			fc = (*i);
			if( fc->Path->compare( Filename ) == 0 && fc->Size == Size && fc->Flags == Flags )
			{
				fc->LastAccess = al_get_time();
				return fc->Font;
			}
		}
	}

	fc = (FontCache*)malloc( sizeof(FontCache) );
	fc->Path = new std::string(Filename);
	fc->Size = Size;
	fc->Flags = Flags;
	fc->Font = al_load_font( Filename.c_str(), Size, Flags );
	fc->LastAccess = al_get_time();
	Cached.push_front( fc );

	return fc->Font;
}

void FontManager::Tidy()
{
	FontCache* fc;
	if( !Cached.empty() )
	{
		for( std::list<FontCache*>::reverse_iterator i = Cached.rbegin(); i != Cached.rend(); i++ )
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


void FontManager::RemoveCached( FontCache* item )
{
	al_destroy_font( item->Font );
	delete item->Path;
	free( (void*)item );
}