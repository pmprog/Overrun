
#pragma once

class Damagable
{

	protected:
		float HealthMax;
		float HealthCurrent;
		float HealthTarget;

		float ShieldsMax;
		float ShieldsCurrent;
		float ShieldsTarget;
		float ShieldsRegen;

	public:

		Damagable( int StartHealth, int StartShields, float ShieldRegenerateRate );
		virtual ~Damagable();
		virtual void Update();

		void TakeDamage( int DamageAmount, bool HitShields );
		void RegainHealth( int RestoreAmount );
		void BoostMax( int AdditionalAmount, bool BoostCurrent );

		float GetCurrentHealth();
		float GetCurrentShields();

};