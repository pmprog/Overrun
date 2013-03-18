
#include "unit.h"

Unit::Unit( ConfigFile* UnitConfig, Path* MapPath )
{
	float* v;

	path = MapPath;

	AbsolutePosition.X = MapPath->GetPathDestination( 0 )->X;
	AbsolutePosition.Y = MapPath->GetPathDestination( 0 )->Y;
	nextPathIndex = 1;

	UnitConfig->GetFloatValue( "Health", &HealthMax );
	HealthCurrent = HealthMax;
	UnitConfig->GetFloatValue( "Shields", &ShieldsMax );
	ShieldsCurrent = ShieldsMax;
	UnitConfig->GetFloatValue( "ShieldRegenRate", &ShieldsRegen );

	UnitConfig->GetIntegerValue( "Reward", &Reward );
	UnitConfig->GetIntegerValue( "DamageToBase", &DamageToBase );

	SpeedCurrent = 0;
	UnitConfig->GetFloatValue( "MaxNormalSpeed", &SpeedMaxNormal );
	UnitConfig->GetFloatValue( "MaxSlowSpeed", &SpeedMaxRestricted );
	UnitConfig->GetFloatValue( "Acceleration", &SpeedAcceleration );
	UnitConfig->GetFloatValue( "Deceleration", &SpeedDeceleration );

	sprite = new VectorSprite();
	ShieldColour = al_map_rgba( 128, 192, 220, 220 );

	if( ShieldsMax > 0.0 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = 0;
		v[2] = 1.0; v[3] = 1.0;
		circShield = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, ShieldColour, v, 2 );
		circShield->LineThickness = 2;
		sprite->Components.push_back( circShield );
		free(v);
	} else {
		circShield = 0;
	}
};

Unit::~Unit()
{
	if( sprite != 0 )
		delete sprite;
};

void Unit::Update()
{
	sprite->Update();
	if( circShield != 0 )
	{
		ShieldsCurrent += ShieldsRegen;
		if( ShieldsCurrent <= 0.0 )
		{
			ALLEGRO_COLOR fadeout = al_map_rgba( ShieldColour.r, ShieldColour.g, ShieldColour.b, 0 );
			circShield->AnimateColourTo( &fadeout, 0.01 );
			circShield->AnimateScaleTo( 0.1, 0.01 );
		} else if ( circShield->Colour.a <= 0.0 ) {
			circShield->AnimateColourTo( &ShieldColour, 0.01 );
			circShield->AnimateScaleTo( 1.0, 0.01 );
		}
	}

	// TODO: Process movement
}

void Unit::Render( Camera* View )
{
	Vector2 screenPos;
	View->AbsoluteToCameraOffset( &AbsolutePosition, &screenPos );
	sprite->Render( &screenPos, View->Rotation, (View->PixelsPerUnit / 2) * View->Zoom );
}
