
#pragma once

#include "damagable.h"

class Inflictor
{

	public:
		float DamageAmount;
		float ShieldByPassPercent;

		Inflictor( float Damage, float ByPass );
		void InflictDamage( Damagable* Object );

};