
#pragma once

#include "../consts.h"
#include "stagestack.h"
#include "vector2.h"

#ifndef Configuration
class Configuration;
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

#else

extern ALLEGRO_EVENT_QUEUE*	EventQueue;
extern bool									Quit;
extern StageStack*					GameStack;
extern Configuration*				CurrentConfiguration;
extern ALLEGRO_MIXER*				mixer;
extern ALLEGRO_VOICE*				voice;

#endif

