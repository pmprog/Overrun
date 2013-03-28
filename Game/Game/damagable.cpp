
#include "damagable.h"
#include "../../Framework/Core/main.h"


Damagable::Damagable( int StartHealth, int StartShields, float ShieldRegenerateRate )
{
	HealthMax = StartHealth;
	HealthCurrent = StartHealth;
	HealthTarget = StartHealth;

	ShieldsMax = StartShields;
	ShieldsCurrent = StartShields;
	ShieldsTarget = StartShields;
	ShieldsRegen = ShieldRegenerateRate;
}

Damagable::~Damagable()
{
}

void Damagable::Update()
{
	float HealthMaxChange = HealthMax / 1000;
	if( abs(HealthTarget - HealthCurrent) / HealthMaxChange > 100 )
		HealthMaxChange *= 6.0;
	else if( abs(HealthTarget - HealthCurrent) / HealthMaxChange > 75 )
		HealthMaxChange *= 3.5;
	else if( abs(HealthTarget - HealthCurrent) / HealthMaxChange > 40 )
		HealthMaxChange *= 2.0;

	if( HealthCurrent != HealthTarget )
	{
		HealthCurrent += max( -HealthMaxChange, min( HealthMaxChange, HealthTarget - HealthCurrent ) );
	}

	float ShieldsMaxChange = (ShieldsMax / 30);
	ShieldsTarget = min( ShieldsTarget + ShieldsRegen, ShieldsMax );
	if( ShieldsCurrent != ShieldsTarget )
	{
		ShieldsCurrent += max( -ShieldsMaxChange, min( ShieldsMaxChange, ShieldsTarget - ShieldsCurrent ) );
	}
}

void Damagable::TakeDamage( int DamageAmount, bool HitShields )
{
	if( DamageAmount < 0 )
		RegainHealth( DamageAmount * -1 );
	else
		HealthTarget = max( 0, HealthTarget - DamageAmount );
}

void Damagable::RegainHealth( int RestoreAmount )
{
	if( RestoreAmount < 0 )
		TakeDamage( RestoreAmount * -1, true );
	else
		HealthTarget = min( HealthMax, HealthTarget + RestoreAmount );
}

void Damagable::BoostMax( int AdditionalAmount, bool BoostCurrent )
{
	HealthMax += AdditionalAmount;
	if( BoostCurrent )
		HealthTarget += AdditionalAmount;
}

float Damagable::GetCurrentHealth()
{
	return HealthTarget;
}

float Damagable::GetCurrentShields()
{
	return ShieldsTarget;
}

