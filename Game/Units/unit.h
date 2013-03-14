
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"

class Unit
{
	protected:
		VectorSprite* sprite;

	public:
		Vector2 AbsolutePosition;
		int CurrentPathIndex;

		double Health;
		double Shields;
		int Cash;

		Unit()
		{
			AbsolutePosition.X = 0;
			AbsolutePosition.Y = 0;
			CurrentPathIndex = 0;
			sprite = new VectorSprite();
			Health = 0;
			Shields = 0;
			Cash = 0;
		};

		~Unit()
		{
			if( sprite != 0 )
				delete sprite;
		};

		virtual void Update() = 0;
		virtual void Render( double ScreenRotation, double ScreenZoom )
		{
			if( sprite != 0 )
				sprite->Render( &AbsolutePosition, ScreenRotation, ScreenZoom );
		};
};