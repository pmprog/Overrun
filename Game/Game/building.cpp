
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
	screenPos.X = AbsolutePosition.X + ((double)TilesWide / 2);
	screenPos.Y = AbsolutePosition.Y + ((double)TilesHigh / 2);
	MultiplyVector( &screenPos, View->PixelsPerUnit );

	if( PlacedOnMap )
	{
		View->AbsoluteToCameraOffset( &screenPos, &screenPos );
	} else {
		screenPos.X = screenPos.X + (View->PixelsPerUnit * (TilesWide / 2));
		screenPos.Y = screenPos.Y + (View->PixelsPerUnit * (TilesHigh / 2));
	}
	sprite->Render( &screenPos, View );
}
