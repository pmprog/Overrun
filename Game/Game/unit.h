
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"
#include "../Game/camera.h"
#include "../../Framework/Resource/configfile.h"
#include "path.h"

class Unit
{
	protected:
		VectorSprite* sprite;
		VectorComponent* circShield;
		Path* path;
		int nextPathIndex;

	public:
		Vector2 AbsolutePosition;

		ALLEGRO_COLOR ShieldColour;

		float HealthMax;
		float HealthCurrent;
		float ShieldsMax;
		float ShieldsCurrent;
		float ShieldsRegen;

		int Reward;
		int DamageToBase;

		float SpeedCurrent;
		float SpeedMaxNormal;
		float SpeedMaxRestricted;
		float SpeedAcceleration;
		float SpeedDeceleration;

		Unit( ConfigFile* UnitConfig, Path* MapPath );
		~Unit();
		virtual void Update();
		virtual void Render( Camera* View );
};