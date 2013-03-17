
#include "spinner.h"

Spinner::Spinner( ConfigFile* UnitConfig, Vector2* StartPosition ) : Unit( UnitConfig, StartPosition )
{
	float* v;
	VectorComponent* vc;

	v = (float*)malloc(sizeof(float) * 4);
	v[0] = 0; v[1] = 0;
	v[2] = 18; v[3] = 18;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgb( 0, 220, 96 ), v, 2 );
	vc->DrawThickness = 4;
	sprite->Components.push_back( vc );
	free(v);

	for( int i = 0; i < 360; i += 60 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = -18;
		v[2] = 0; v[3] = -12;
		vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYLINE, al_map_rgb( 0, 220, 96 ), v, 2 );
		vc->DrawThickness = 2;
		vc->Rotation = i;
		vc->RotationPerFrame = 1.0;
		sprite->Components.push_back( vc );
		free(v);
	}
}
