
#include "spinner.h"

Spinner::Spinner( ConfigFile* UnitConfig, Path* MapPath ) : Unit( UnitConfig, MapPath )
{
	float* v;
	VectorComponent* vc;
	ALLEGRO_COLOR neonGreen = al_map_rgb( 0, 220, 96 );

	v = (float*)malloc(sizeof(float) * 4);
	v[0] = 0; v[1] = 0;
	v[2] = 0.77; v[3] = 0.77;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgba( 0, 0, 0, 0 ), v, 2 );
	vc->AnimateThicknessTo( 2 );
	vc->AnimateColourTo( &neonGreen, 0.1 );
	sprite->Components.push_back( vc );
	free(v);

	for( int i = 0; i < 360; i += 60 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = -0.77;
		v[2] = 0; v[3] = -0.5;
		vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYLINE, al_map_rgba( 0, 0, 0, 0 ), v, 2 );
		vc->Rotation = i;
		vc->AnimateRotation( 1.4 );
		vc->AnimateColourTo( &neonGreen, 0.1 );
		sprite->Components.push_back( vc );
		free(v);
	}
}
