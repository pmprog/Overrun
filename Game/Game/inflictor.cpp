
#include "inflictor.h"
#include "../../Framework/Core/main.h"

Inflictor::Inflictor( float Damage, float ByPass )
{
	DamageAmount = Damage;
	ShieldByPassPercent = ByPass;
}

void Inflictor::InflictDamage( Damagable* Object )
{
	float ShieldDamage = min( DamageAmount * (1.0 - ShieldByPassPercent), Object->GetCurrentShields() );

	if( ShieldDamage > 0 )
		Object->TakeDamage( ShieldDamage, true );

	Object->TakeDamage( DamageAmount - ShieldDamage, false );
}
