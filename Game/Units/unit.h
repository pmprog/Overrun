
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"
#include "../camera.h"

class Unit
{
	protected:
		VectorSprite* sprite;
		VectorComponent* circShield;

	public:
		Vector2 AbsolutePosition;
		int CurrentPathIndex;

		double Health;
		double Shields;
		int Cash;

		Unit( double StartHealth, double StartShields, int CashReward );
		~Unit();
		virtual void Update();
		virtual void Render( int TileSize, Camera* camera );
};