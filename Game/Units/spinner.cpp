
#include "spinner.h"

Spinner::Spinner( ConfigFile* UnitConfig, Path* MapPath ) : Unit( UnitConfig, MapPath )
{
	float* v;
	VectorComponent* vc;

	v = (float*)malloc(sizeof(float) * 4);
	v[0] = 0; v[1] = 0;
	v[2] = 0.8; v[3] = 0.8;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgb( 0, 220, 96 ), v, 2 );
	vc->LineThickness = 3;
	sprite->Components.push_back( vc );
	free(v);

	for( int i = 0; i < 360; i += 60 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = -0.8;
		v[2] = 0; v[3] = -0.5;
		vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYLINE, al_map_rgb( 0, 220, 96 ), v, 2 );
		vc->LineThickness = 1;
		vc->Rotation = i;
		vc->AnimateRotation( 1.4 );
		sprite->Components.push_back( vc );
		free(v);
	}
}
