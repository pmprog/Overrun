
#include "map.h"
#include "../game.h"

#include "../Structures/buildings.h"

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

	int pathcount;
	LevelData->GetIntegerValue( "Paths", &pathcount );
	for( int p = 1; p <= pathcount; p++ )
	{
		Paths.push_back( new Path( LevelData, p ) );
	}

	int buildingcount;
	buildingcount = LevelData->GetArraySize( "StartingStructures" );
	for( int i = 0; i < buildingcount; i++ )
	{
		Building* b = 0;
		std::string bname;

		LevelData->GetStringValue( "StartingStructures", i, &bname );
		if( bname == "Base" )
			b = new Base( CurGame, 1000 );
		// TODO: Add building classes here


		if( b != 0 )
		{
			LevelData->GetFloatValue( "StartingStrutPosX", i, &b->AbsolutePosition.X );
			LevelData->GetFloatValue( "StartingStrutPosY", i, &b->AbsolutePosition.Y );
			b->PlacedOnMap = true;
			Buildings.push_back( b );
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

	for(std::vector<Building*>::iterator i = Buildings.begin(); i != Buildings.end(); i++ )
	{
		Building* b = (Building*)(*i);
		if( X < b->AbsolutePosition.X + b->TilesWide && X > b->AbsolutePosition.X - b->TilesWide && Y < b->AbsolutePosition.Y + b->TilesHigh && Y > b->AbsolutePosition.Y - b->TilesHigh )
			return false;
	}
	return true;
}

void Map::Update()
{
	Unit* u;
	for( std::vector<Unit*>::iterator i = Units.begin(); i != Units.end(); i++ )
	{
		u = (*i);
		u->Update();
	}

	for(std::vector<Building*>::iterator i = Buildings.begin(); i != Buildings.end(); i++ )
	{
		Building* b = (Building*)(*i);
		Damagable* d = dynamic_cast<Damagable*>(b);

		// Process any damage if available
		if( d != 0 )
		{
			// TODO: http://en.wikipedia.org/wiki/Erase-remove_idiom
			for( std::vector<Unit*>::iterator i = Units.begin(); i != Units.end(); )
			{
				u = (*i);
				if( (int)u->AbsolutePosition.X >= (int)b->AbsolutePosition.X && (int)u->AbsolutePosition.Y >= (int)b->AbsolutePosition.Y &&
					(int)u->AbsolutePosition.X < (int)b->AbsolutePosition.X + b->TilesWide && (int)u->AbsolutePosition.Y < (int)b->AbsolutePosition.Y + b->TilesHigh )
				{
					u->InflictDamage( d );
					delete u;
					i = Units.erase( i );
				} else {
					i++;
				}
			}
		}
		b->Update();
	}
}

void Map::Render( Camera* View )
{
	Vector2 pts[4];
	for( int y = 0; y < MapHeight; y++ )
	{
		for( int x = 0; x < MapWidth; x++ )
		{
			pts[0].X = x * CurGame->TileSize;
			pts[1].X = x * CurGame->TileSize;
			pts[2].X = (x + 1) * CurGame->TileSize;
			pts[3].X = (x + 1) * CurGame->TileSize;
			pts[0].Y = y * CurGame->TileSize;
			pts[1].Y = (y + 1) * CurGame->TileSize;
			pts[2].Y = y * CurGame->TileSize;
			pts[3].Y = (y + 1) * CurGame->TileSize;
			View->AbsoluteToCameraOffset( &pts[0], &pts[0] );
			View->AbsoluteToCameraOffset( &pts[1], &pts[1] );
			View->AbsoluteToCameraOffset( &pts[2], &pts[2] );
			View->AbsoluteToCameraOffset( &pts[3], &pts[3] );
			RenderGround( x, y, (Vector2*)&pts );
		}
	}
	for( std::vector<Unit*>::iterator i = Units.begin(); i != Units.end(); i++ )
	{
		Unit* u = (*i);
		u->Render( View );
	}
	for(std::vector<Building*>::iterator i = Buildings.begin(); i != Buildings.end(); i++ )
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
