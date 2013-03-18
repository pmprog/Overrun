
#pragma once

#include "../../Framework/Core/main.h"
#include "unit.h"

#ifndef Game
class Game;
#endif

class Wave
{
	private:
		std::string UnitClass;
		ConfigFile* UnitSpec;

	public:
		int WaveDelay;
		float SpawnDelay;
		int UnitCount;

		Wave( ConfigFile* WaveData );
		~Wave();

		Unit* SpawnUnit( Path* FollowPath );

};
