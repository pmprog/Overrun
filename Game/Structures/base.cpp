
#include "base.h"

Base::Base( Game* CurrentGame, int StartHealth ) : Building( CurrentGame )
{
	HealthMax = StartHealth;
	HealthCurrent = StartHealth;

	TilesWide = 4;
	TilesHigh = 4;

	float* v;
	VectorComponent* vc;

	v = (float*)malloc(sizeof(float) * 8);
	v[0] = -1.0; v[1] = -1.0;
	v[2] = -1.0; v[3] =  1.0;
	v[4] =  1.0; v[5] =  1.0;
	v[6] =  1.0; v[7] = -1.0;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYGON, al_map_rgb( 220, 220, 220 ), v, 4 );
	vc->AnimateThicknessTo( 6 );
	sprite->Components.push_back( vc );
	free(v);
}

Base::~Base()
{
}
