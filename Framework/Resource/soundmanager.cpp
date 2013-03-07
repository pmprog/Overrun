
#include "soundmanager.h"
#include "../Core/main.h"

SoundManager::SoundManager()
{
	SfxCacheTime = 240;
	MusicCacheTime = 600;
}

SoundManager::~SoundManager()
{
	SoundCache* fc;
	while( !SfxCached.empty() )
	{
		fc = SfxCached.back();
		SfxCached.pop_back();
		RemoveSfxCached( fc );
	}
	while( !MusicCached.empty() )
	{
		fc = MusicCached.back();
		MusicCached.pop_back();
		RemoveMusicCached( fc );
	}
}

ALLEGRO_SAMPLE* SoundManager::GetSoundFX(std::string Filename)
{
	SoundCache* fc;

	if( !SfxCached.empty() )
	{
		for( std::list<SoundCache*>::iterator i = SfxCached.begin(); i != SfxCached.end(); i++ )
		{
			fc = (*i);
			if( fc->Path->compare( Filename ) == 0 )
			{
				fc->LastAccess = al_get_time();
				return (ALLEGRO_SAMPLE*)fc->Reference;
			}
		}
	}

	fc = (SoundCache*)malloc( sizeof(SoundCache) );
	fc->Path = new std::string(Filename);
	fc->Reference = al_load_sample( Filename.c_str() );
	fc->LastAccess = al_get_time();
	SfxCached.push_front( fc );

	return (ALLEGRO_SAMPLE*)fc->Reference;
}

ALLEGRO_AUDIO_STREAM* SoundManager::GetMusic(std::string Filename)
{
	SoundCache* fc;

	if( !MusicCached.empty() )
	{
		for( std::list<SoundCache*>::iterator i = MusicCached.begin(); i != MusicCached.end(); i++ )
		{
			fc = (*i);
			if( fc->Path->compare( Filename ) == 0 )
			{
				fc->LastAccess = al_get_time();
				return (ALLEGRO_AUDIO_STREAM*)fc->Reference;
			}
		}
	}

	fc = (SoundCache*)malloc( sizeof(SoundCache) );
	fc->Path = new std::string(Filename);
	fc->Reference = al_load_audio_stream( Filename.c_str(), 4, 2048 );
	fc->LastAccess = al_get_time();
	MusicCached.push_front( fc );

	return (ALLEGRO_AUDIO_STREAM*)fc->Reference;
}

void SoundManager::Tidy()
{
	SoundCache* fc;
	if( !SfxCached.empty() )
	{
		for( std::list<SoundCache*>::reverse_iterator i = SfxCached.rbegin(); i != SfxCached.rend(); i++ )
		{
			fc = (*i);
			if( al_get_time() - fc->LastAccess > SfxCacheTime )
			{
				SfxCached.remove( fc );
				RemoveSfxCached( fc );
			}
		}
	}
	if( !MusicCached.empty() )
	{
		for( std::list<SoundCache*>::reverse_iterator i = MusicCached.rbegin(); i != MusicCached.rend(); i++ )
		{
			fc = (*i);
			if( al_get_time() - fc->LastAccess > MusicCacheTime )
			{
				MusicCached.remove( fc );
				RemoveMusicCached( fc );
			}
		}
	}
}

void SoundManager::RemoveSfxCached( SoundCache* item )
{
	al_destroy_sample( (ALLEGRO_SAMPLE*)item->Reference );
	delete item->Path;
	free( (void*)item );
}

void SoundManager::RemoveMusicCached( SoundCache* item )
{
	al_destroy_audio_stream( (ALLEGRO_AUDIO_STREAM*)item->Reference );
	delete item->Path;
	free( (void*)item );
}