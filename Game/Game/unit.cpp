
#include "unit.h"

Unit::Unit( ConfigFile* UnitConfig, Path* MapPath ) : Damagable( 0, 0, 0 ), Inflictor( 0.0, 0.0 )
{
	float* v;

	path = MapPath;

	AbsolutePosition.X = MapPath->GetPathDestination( 0 )->X;
	AbsolutePosition.Y = MapPath->GetPathDestination( 0 )->Y;
	nextPathIndex = 1;

	UnitConfig->GetFloatValue( "Health", &HealthMax );
	HealthCurrent = HealthMax;
	HealthTarget = HealthMax;
	UnitConfig->GetFloatValue( "Shields", &ShieldsMax );
	ShieldsCurrent = ShieldsMax;
	ShieldsTarget = ShieldsMax;
	UnitConfig->GetFloatValue( "ShieldRegenRate", &ShieldsRegen );

	UnitConfig->GetIntegerValue( "Reward", &Reward );
	UnitConfig->GetFloatValue( "DamageToBase", &DamageAmount );
	ShieldByPassPercent = 0.0;

	SpeedCurrent = 0;
	UnitConfig->GetFloatValue( "MaxNormalSpeed", &SpeedMaxNormal );
	UnitConfig->GetFloatValue( "MaxSlowSpeed", &SpeedMaxRestricted );
	UnitConfig->GetFloatValue( "Acceleration", &SpeedAcceleration );
	UnitConfig->GetFloatValue( "Deceleration", &SpeedDeceleration );

	sprite = new VectorSprite();
	ShieldColour = al_map_rgba( 128, 192, 220, 220 );
	ShieldColourFaded = al_map_rgba( 128, 192, 220, 0 );

	if( ShieldsMax > 0.0 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = 0;
		v[2] = 0.95; v[3] = 0.95;
		circShield = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, ShieldColourFaded, v, 2 );
		circShield->AnimateThicknessTo( 2 );
		circShield->AnimateColourTo( &ShieldColour, 0.1 );
		sprite->Components.push_back( circShield );
		free(v);
	} else {
		circShield = 0;
	}
};

Unit::~Unit()
{
	delete sprite;
};

void Unit::Update()
{
	sprite->Update();
	if( circShield != 0 )
	{
		ShieldsCurrent += ShieldsRegen;
		if( ShieldsCurrent <= 0.0 && circShield->Colour.a > 0.0 )
		{
			circShield->AnimateColourTo( &ShieldColourFaded, 0.02 );
			circShield->AnimateScaleTo( 0.1, 0.01 );
		} else if ( circShield->Colour.a <= 0.0 ) {
			circShield->AnimateColourTo( &ShieldColour, 0.02 );
			circShield->AnimateScaleTo( 1.0, 2.0 );
		}
	}

	Vector2* nextPoint = path->GetPathDestination( nextPathIndex );
	if( nextPoint != 0 )
	{
		// TODO: Fix speed control
		SpeedCurrent = 0.05;
		AbsolutePosition.X += ( abs(SpeedCurrent) < abs(nextPoint->X - AbsolutePosition.X) ? (nextPoint->X > AbsolutePosition.X ? SpeedCurrent : -SpeedCurrent) : nextPoint->X - AbsolutePosition.X );
		AbsolutePosition.Y += ( abs(SpeedCurrent) < abs(nextPoint->Y - AbsolutePosition.Y) ? (nextPoint->Y > AbsolutePosition.Y ? SpeedCurrent : -SpeedCurrent) : nextPoint->Y - AbsolutePosition.Y );

		if( (int)AbsolutePosition.X == (int)nextPoint->X && (int)AbsolutePosition.Y == (int)nextPoint->Y )
			nextPathIndex++;
	}
}

void Unit::Render( Camera* View )
{
	Vector2 screenPos;
	screenPos.X = AbsolutePosition.X; screenPos.Y = AbsolutePosition.Y;
	MultiplyVector( &screenPos, View->PixelsPerUnit );
	View->AbsoluteToCameraOffset( &screenPos, &screenPos );
	sprite->Render( &screenPos, View );
}
