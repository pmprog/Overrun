
#include "base.h"

Base::Base( Game* CurrentGame, int StartHealth ) : Building( CurrentGame )
{
	HealthMax = StartHealth;
	HealthCurrent = 0;
	HealthTarget = StartHealth;

	HealthColourGood = al_map_rgb( 192, 255, 192 );
	HealthColourMid = al_map_rgb( 255, 255, 192 );
	HealthColourBad = al_map_rgb( 255, 192, 192 );

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
	if( HealthCurrent != HealthTarget )
	{
		HealthCurrent += max( -5.0, min( 5.0, HealthTarget - HealthCurrent ) );
	}

	float lifeSize = 3.8 - ((7.6 / HealthMax) * HealthCurrent);
	HealthBar->SetPoint( 0, true, lifeSize );
	HealthBar->SetPoint( 3, true, lifeSize );

	float lifePC = (float)HealthCurrent / (float)HealthMax;
	if( lifePC > 0.5 )
	{
		if( HealthBar->Colour.r != HealthColourGood.r || HealthBar->Colour.g != HealthColourGood.g || HealthBar->Colour.b != HealthColourGood.b )
			HealthBar->AnimateColourTo( &HealthColourGood, 0.2 );
	} else if( lifePC > 0.23 ) {
		if( HealthBar->Colour.r != HealthColourMid.r || HealthBar->Colour.g != HealthColourMid.g || HealthBar->Colour.b != HealthColourMid.b )
			HealthBar->AnimateColourTo( &HealthColourMid, 0.2 );
	} else {
		if( HealthBar->Colour.r != HealthColourBad.r || HealthBar->Colour.g != HealthColourBad.g || HealthBar->Colour.b != HealthColourBad.b )
			HealthBar->AnimateColourTo( &HealthColourBad, 0.2 );
	}

	Building::Update();
}

void Base::TakeDamage( int DamageAmount )
{
	if( DamageAmount < 0 )
		RegainHealth( DamageAmount * -1 );
	else
		HealthTarget = max( 0, HealthTarget - DamageAmount );
}

void Base::RegainHealth( int RestoreAmount )
{
	if( RestoreAmount < 0 )
		TakeDamage( RestoreAmount * -1 );
	else
		HealthTarget = min( HealthMax, HealthTarget + RestoreAmount );
}

void Base::BoostMax( int AdditionalAmount, bool BoostCurrent )
{
	HealthMax += AdditionalAmount;
	if( BoostCurrent )
		HealthTarget += AdditionalAmount;
}

