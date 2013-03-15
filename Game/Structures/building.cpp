
#include "building.h"

Building::Building( Game* CurrentGame )
{
	GameStage = CurrentGame;

	sprite = new VectorSprite();

	Buildable = false;
	BuildingCost = 0;
	BuildingTime = 0;

	TilesWide = 1;
	TilesHigh = 1;

	PlacedOnMap = false;
}

Building::~Building()
{
}

void Building::Update()
{
}

void Building::Render(int TileSize, Camera *camera)
{
	Vector2 screenPos;

	if( PlacedOnMap )
	{
		camera->AbsoluteToCameraOffset( &AbsolutePosition, &screenPos );
		sprite->Render( &screenPos, camera->Rotation, (double)TileSize * camera->Zoom );
	} else {
		screenPos.X = AbsolutePosition.X + (TileSize * (TilesWide / 2));
		screenPos.Y = AbsolutePosition.Y + (TileSize * (TilesHigh / 2));
		sprite->Render( &screenPos, camera->Rotation, (double)TileSize * camera->Zoom );
	}
}
