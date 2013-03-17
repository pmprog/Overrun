
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"
#include "../Game/camera.h"
#include "../../Framework/Resource/configfile.h"

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

		Unit( ConfigFile* UnitConfig, Vector2* StartPosition );
		~Unit();
		virtual void Update();
		virtual void Render( Camera* View );
};