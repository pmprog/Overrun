
#pragma once

#include "../consts.h"
#include "stagestack.h"

#ifndef Configuration
class Configuration;
#endif
#ifndef FontManager
class FontManager;
#endif
#ifndef ImageManager
class ImageManager;
#endif
#ifndef SoundManager
class SoundManager;
#endif


#ifdef _core

ALLEGRO_DISPLAY_MODE	ScreenMode;
ALLEGRO_DISPLAY*			Screen;
ALLEGRO_EVENT_QUEUE*	EventQueue;
bool									Quit = false;
StageStack*						GameStack;
Configuration*				CurrentConfiguration;
ALLEGRO_MIXER*				mixer;
ALLEGRO_VOICE*				voice;
FontManager*					Fonts;
ImageManager*					Images;
SoundManager*					Audio;

#else

extern ALLEGRO_EVENT_QUEUE*	EventQueue;
extern bool									Quit;
extern StageStack*					GameStack;
extern Configuration*				CurrentConfiguration;
extern ALLEGRO_MIXER*				mixer;
extern ALLEGRO_VOICE*				voice;
extern FontManager*					Fonts;
extern ImageManager*				Images;
extern SoundManager*				Audio;

#endif

