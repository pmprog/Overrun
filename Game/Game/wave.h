
#pragma once

#include "../../Framework/Core/main.h"
#include "unit.h"

#ifndef Game
class Game;
#endif

class Wave
{
	public:
		std::string UnitClass;
		ConfigFile* UnitSpec;
		int					WaveDelay;
		float				SpawnDelay;
		int					UnitCount;

		Wave( ConfigFile* WaveData );
		~Wave();

		Unit* SpawnUnit( Path* FollowPath );

};
