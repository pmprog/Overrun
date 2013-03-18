
#pragma once

#include "../../Framework/Core/main.h"
#include "camera.h"
#include "../Structures/building.h"
#include "path.h"

#ifndef Game
class Game;
#endif

class Map
{
	private:
		Game* CurGame;

		int MapWidth;
		int MapHeight;
		uint8_t* MapData;

	public:
		std::list<Building*> Buildings;
		std::vector<Path*> Paths;

		Map( Game* CurrentGame, ConfigFile* LevelData );
		~Map();

		int GetElement( int X, int Y );
		bool CanBuildOnTile( int X, int Y );

		void Update();
		void Render( Camera* View );
		void RenderGround( int X, int Y, Vector2 BasePoints[] );

};