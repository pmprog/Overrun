
#pragma once

#define MAX_STACK_SIZE			10
#define SCREEN_FPS					60

#define NETWORK_SUPPORT								1
#define NETWORK_ALLOWMULTICLIENT			0


#if NETWORK_SUPPORT != 0
// For some reason this has to be defined before any other include
#include <enet/enet.h>
#endif

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <list>
#include <string>
#include "Resource/fontmanager.h"
#include "Resource/imagemanager.h"

#if NETWORK_SUPPORT != 0
#include "Network/network.h"
#endif


