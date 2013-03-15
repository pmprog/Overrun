
#include "map.h"

Map::Map( Game* CurrentGame, ConfigFile* LevelData )
{
	CurGame = CurrentGame;
	LevelData->GetIntegerValue( "Width", &MapWidth );
	LevelData->GetIntegerValue( "Height", &MapHeight );

	MapData = (uint8_t*)malloc( MapWidth * MapHeight * sizeof( uint8_t ) );
	for( int y = 0; y < MapHeight; y++ )
	{
		for( int x = 0; x < MapWidth; x++ )
		{
			int t;
			LevelData->GetIntegerValue( "Map", (y * MapWidth) + x, &t );
			MapData[(y * MapWidth) + x] = (uint8_t)t;
		}
	}
}

Map::~Map()
{
	free( MapData );
}

int Map::GetElement( int X, int Y )
{
	if( X < 0 || Y < 0 || X >= MapWidth || Y >= MapHeight )
		return -1;
	return MapData[(Y * MapWidth) + X];
}

bool Map::CanBuildOnTile( int X, int Y )
{
	if( GetElement( X, Y ) != 0 )
		return false;

	for(std::list<Building*>::iterator i = Buildings.begin(); i != Buildings.end(); i++ )
	{
		Building* b = (Building*)(*i);
		if( X < b->GridPosition.X + b->TilesWide && X > b->GridPosition.X - b->TilesWide && Y < b->GridPosition.Y + b->TilesHigh && Y > b->GridPosition.Y - b->TilesHigh )
			return false;
	}
	return true;
}

void Map::Update()
{
	for(std::list<Building*>::iterator i = Buildings.begin(); i != Buildings.end(); i++ )
	{
		Building* b = (Building*)(*i);
		// TODO: Process buildings - Base take damage, Turrets firing
	}
}

void Map::Render( Camera* View )
{
	Vector2 pts[4];
	for( int y = 0; y < MapHeight; y++ )
	{
		for( int x = 0; x < MapWidth; x++ )
		{
			pts[0].X = x * View->PixelsPerUnit;
			pts[1].X = x * View->PixelsPerUnit;
			pts[2].X = (x + 1) * View->PixelsPerUnit;
			pts[3].X = (x + 1) * View->PixelsPerUnit;
			pts[0].Y = y * View->PixelsPerUnit;
			pts[1].Y = (y + 1) * View->PixelsPerUnit;
			pts[2].Y = y * View->PixelsPerUnit;
			pts[3].Y = (y + 1) * View->PixelsPerUnit;
			View->AbsoluteToCameraOffset( &pts[0], &pts[0] );
			View->AbsoluteToCameraOffset( &pts[1], &pts[1] );
			View->AbsoluteToCameraOffset( &pts[2], &pts[2] );
			View->AbsoluteToCameraOffset( &pts[3], &pts[3] );
			RenderGround( x, y, (Vector2*)&pts );
		}
	}
	for(std::list<Building*>::iterator i = Buildings.begin(); i != Buildings.end(); i++ )
	{
		Building* b = (Building*)(*i);
		b->Render( View );
	}
}

void Map::RenderGround( int X, int Y, Vector2 BasePoints[] )
{
	float polyverts[8] = {
		BasePoints[2].X, BasePoints[2].Y,
		BasePoints[0].X, BasePoints[0].Y,
		BasePoints[1].X, BasePoints[1].Y,
		BasePoints[3].X, BasePoints[3].Y
	};

	switch( GetElement( X, Y ) )
	{
		case 0:	// Buildable
			al_draw_filled_polygon( (float*)&polyverts, 4, al_map_rgb( 64, 128, 64 ) );
			break;
		case 1: // Path
			al_draw_filled_polygon( (float*)&polyverts, 4, al_map_rgb( 64, 64, 64 ) );
			break;
		case 2: // Water
			al_draw_filled_polygon( (float*)&polyverts, 4, al_map_rgb( 64, 64, 128 ) );
			break;
	}

	al_draw_line( BasePoints[0].X, BasePoints[0].Y, BasePoints[1].X, BasePoints[1].Y, al_map_rgb( 64, 64, 64), 1 );
	al_draw_line( BasePoints[0].X, BasePoints[0].Y, BasePoints[2].X, BasePoints[2].Y, al_map_rgb( 64, 64, 64), 1 );
	al_draw_line( BasePoints[3].X, BasePoints[3].Y, BasePoints[1].X, BasePoints[1].Y, al_map_rgb( 64, 64, 64), 1 );
	al_draw_line( BasePoints[2].X, BasePoints[2].Y, BasePoints[3].X, BasePoints[3].Y, al_map_rgb( 64, 64, 64), 1 );
}
