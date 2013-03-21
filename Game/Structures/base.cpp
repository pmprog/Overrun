
#include "base.h"

Base::Base( Game* CurrentGame, int StartHealth ) : Building( CurrentGame ), Damagable( StartHealth, 0, 0 )
{
	HealthColourGood = al_map_rgb( 128, 255, 128 );
	HealthColourMid = al_map_rgb( 192, 128, 64 );
	HealthColourBad = al_map_rgb( 255, 0, 0 );

	TilesWide = 4;
	TilesHigh = 4;

	float* v;
	VectorComponent* vc;

	v = (float*)malloc(sizeof(float) * 8);
	v[0] = -3.8; v[1] = -1.0;
	v[2] = -3.8; v[3] =  3.0;
	v[4] =  3.0; v[5] =  3.0;
	v[6] =  3.0; v[7] = -1.0;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYGON, al_map_rgb( 128, 128, 220 ), v, 4 );
	vc->AnimateThicknessTo( 2 );
	sprite->Components.push_back( vc );
	free(v);

	v = (float*)malloc(sizeof(float) * 8);
	v[0] = -3.5; v[1] = -3.5;
	v[2] =  0.3; v[3] =  0.3;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgb( 128, 128, 220 ), v, 2 );
	sprite->Components.push_back( vc );
	free(v);
	v = (float*)malloc(sizeof(float) * 8);
	v[0] = -2.8; v[1] = -3.5;
	v[2] =  0.3; v[3] =  0.3;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgb( 128, 128, 220 ), v, 2 );
	sprite->Components.push_back( vc );
	free(v);

	v = (float*)malloc(sizeof(float) * 8);
	v[0] =  3.55; v[1] = -3.85;
	v[2] =  3.55; v[3] =  3.85;
	v[4] =  3.85; v[5] =  3.85;
	v[6] =  3.85; v[7] = -3.85;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYGON_FILLED, al_map_rgb( 0, 0, 0 ), v, 4 );
	sprite->Components.push_back( vc );

	free(v);

	v = (float*)malloc(sizeof(float) * 8);
	v[0] =  3.6; v[1] = -3.8;
	v[2] =  3.6; v[3] =  3.8;
	v[4] =  3.8; v[5] =  3.8;
	v[6] =  3.8; v[7] = -3.8;
	HealthBar = new VectorComponent( VECTORSPRITE_COMPONENT_POLYGON_FILLED, HealthColourGood, v, 4 );
	sprite->Components.push_back( HealthBar );
	free(v);

}

Base::~Base()
{
}

void Base::Update()
{
	float lifeSize = 3.8 - ((7.6 / HealthMax) * HealthCurrent);
	HealthBar->SetPoint( 0, true, lifeSize );
	HealthBar->SetPoint( 3, true, lifeSize );

	float lifePC = (float)HealthCurrent / (float)HealthMax;
	if( lifePC > 0.5 )
	{
		if( HealthBar->Colour.r != HealthColourGood.r || HealthBar->Colour.g != HealthColourGood.g || HealthBar->Colour.b != HealthColourGood.b )
			HealthBar->AnimateColourTo( &HealthColourGood, 0.02 );
	} else if( lifePC > 0.23 ) {
		if( HealthBar->Colour.r != HealthColourMid.r || HealthBar->Colour.g != HealthColourMid.g || HealthBar->Colour.b != HealthColourMid.b )
			HealthBar->AnimateColourTo( &HealthColourMid, 0.02 );
	} else {
		if( HealthBar->Colour.r != HealthColourBad.r || HealthBar->Colour.g != HealthColourBad.g || HealthBar->Colour.b != HealthColourBad.b )
			HealthBar->AnimateColourTo( &HealthColourBad, 0.02 );
	}

	Damagable::Update();
	Building::Update();
}


