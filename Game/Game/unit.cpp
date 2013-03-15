
#include "unit.h"

Unit::Unit( double StartHealth, double StartShields, int CashReward )
{
	float* v;

	AbsolutePosition.X = 0;
	AbsolutePosition.Y = 0;
	CurrentPathIndex = 0;
	sprite = new VectorSprite();
	Health = StartHealth;
	Shields = StartShields;
	Cash = CashReward;

	if( Shields > 0.0 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = 0;
		v[2] = 1.0; v[3] = 1.0;
		circShield = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgba( 128, 192, 220, 128 ), v, 2 );
		circShield->DrawThickness = 2;
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
	if( Shields == 0.0 && circShield != 0 )
		circShield->ColourChangePerFrame.a = -0.05;
}

void Unit::Render( Camera* View )
{
	Vector2 screenPos;
	View->AbsoluteToCameraOffset( &AbsolutePosition, &screenPos );
	sprite->Render( &screenPos, View->Rotation, View->PixelsPerUnit * View->Zoom );
}
