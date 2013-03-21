
#pragma once

#include "../Sprites/vectorcomponent.h"
#include "../Sprites/vectorsprite.h"
#include "../Game/camera.h"
#include "../../Framework/Resource/configfile.h"
#include "path.h"
#include "inflictor.h"

class Unit : public Damagable, public Inflictor
{
	protected:
		VectorSprite* sprite;
		VectorComponent* circShield;
		Path* path;
		int nextPathIndex;

	public:
		Vector2 AbsolutePosition;

		ALLEGRO_COLOR ShieldColour;
		ALLEGRO_COLOR ShieldColourFaded;

		int Reward;
		// int DamageToBase;

		float SpeedCurrent;
		float SpeedMaxNormal;
		float SpeedMaxRestricted;
		float SpeedAcceleration;
		float SpeedDeceleration;

		Unit( ConfigFile* UnitConfig, Path* MapPath );
		virtual ~Unit();
		virtual void Update();
		virtual void Render( Camera* View );
};