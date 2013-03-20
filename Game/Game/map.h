
#pragma once

#include "../../Framework/Core/main.h"
#include "camera.h"
#include "building.h"
#include "path.h"
#include "unit.h"

#ifndef Game
class Game;
#endif

class Map
{
	private:
		Game* CurGame;

		uint8_t* MapData;

	public:
		std::vector<Unit*> Units;
		std::vector<Building*> Buildings;
		std::vector<Path*> Paths;
		int MapWidth;
		int MapHeight;

		Map( Game* CurrentGame, ConfigFile* LevelData );
		~Map();

		int GetElement( int X, int Y );
		bool CanBuildOnTile( int X, int Y );

		void Update();
		void Render( Camera* View );
		void RenderGround( int X, int Y, Vector2 BasePoints[] );

};