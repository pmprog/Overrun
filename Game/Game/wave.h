
#pragma once

#include "../../Framework/Core/main.h"
#include "camera.h"

#ifndef Game
class Game;
#endif

class Wave
{
	private:
		Game* CurGame;

	public:
		Wave( Game* CurrentGame, ConfigFile* LevelData, int WaveNumber );
		~Wave();

		void InitialiseWave();

};
