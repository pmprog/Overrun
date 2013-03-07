
#pragma once

#include <list>
#include <string>

#ifndef ALLEGRO_SAMPLE
struct ALLEGRO_SAMPLE;
#endif
#ifndef ALLEGRO_AUDIO_STREAM
struct ALLEGRO_AUDIO_STREAM;
#endif

typedef struct SoundCache
{
	std::string* Path;
	double LastAccess;
	void* Reference;
} SoundCache;


class SoundManager
{
	private:
		std::list<SoundCache*> SfxCached;
		std::list<SoundCache*> MusicCached;

		void RemoveSfxCached( SoundCache* item );
		void RemoveMusicCached( SoundCache* item );

	public:
		double SfxCacheTime;
		double MusicCacheTime;

		SoundManager();
		~SoundManager();

		ALLEGRO_SAMPLE* GetSoundFX(std::string Filename);
		ALLEGRO_AUDIO_STREAM* GetMusic(std::string Filename);

		void Tidy();
};