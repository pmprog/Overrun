
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"
#include "../Game/camera.h"

#ifndef Game
class Game;
#endif

class Building
{
	protected:
		VectorSprite* sprite;

	public:
		Game* CurGame;

		Vector2 AbsolutePosition;

		bool Buildable;
		int  BuildingCost;
		int  BuildingTime;

		bool PlacedOnMap;

		int TilesWide;
		int TilesHigh;

		Building( Game* CurrentGame );
		~Building();
		virtual void Update();
		virtual void Render( Camera* View );
};