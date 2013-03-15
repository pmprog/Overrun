
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"
#include "../camera.h"
#include "../game.h"

class Building
{
	protected:
		VectorSprite* sprite;

	public:
		Game* GameStage;

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
		virtual void Render( int TileSize, Camera* camera );
};