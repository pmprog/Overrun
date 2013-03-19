
#include "building.h"

Building::Building( Game* CurrentGame )
{
	CurGame = CurrentGame;

	sprite = new VectorSprite();

	Buildable = false;
	BuildingCost = 0;
	BuildingTime = 0;

	TilesWide = 1;
	TilesHigh = 1;

	PlacedOnMap = false;
	GridPosition.X = -1;
	GridPosition.Y = -1;
	AbsolutePosition.X = -1;
	AbsolutePosition.Y = -1;
}

Building::~Building()
{
}

void Building::Update()
{
}

void Building::Render( Camera* View )
{
	Vector2 screenPos;

	if( PlacedOnMap )
	{
		View->AbsoluteToCameraOffset( &AbsolutePosition, &screenPos );
		sprite->Render( &screenPos, View );
	} else {
		screenPos.X = AbsolutePosition.X + (View->PixelsPerUnit * (TilesWide / 2));
		screenPos.Y = AbsolutePosition.Y + (View->PixelsPerUnit * (TilesHigh / 2));
		sprite->Render( &screenPos, View );
	}
}
