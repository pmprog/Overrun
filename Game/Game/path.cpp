
#include "path.h"

Path::Path( ConfigFile* LevelData, int PathNumber )
{
	Vector2* pnt;
	int maxlength;
	char key[50];

	sprintf( (char*)&key, "Path%d", PathNumber );
	maxlength = LevelData->GetArraySize( (char*)&key );

	for( int i = 0; i < maxlength; i += 2 )
	{
		pnt = (Vector2*)malloc( sizeof( Vector2 ) );
		LevelData->GetFloatValue( (char*)&key, i, &pnt->X );
		LevelData->GetFloatValue( (char*)&key, i + 1, &pnt->Y );
		points.push_back( pnt );
	}
	
}

Path::~Path()
{
	while( points.size() > 0 )
	{
		free( points.back() );
		points.pop_back();
	}
}

Vector2* Path::GetPathDestination( int Index )
{
	return points.at( Index );
}
