
#include "../Game/building.h"

class Base : public Building
{

	private:
		VectorComponent*	HealthBar;
		ALLEGRO_COLOR			HealthColourGood;
		ALLEGRO_COLOR			HealthColourMid;
		ALLEGRO_COLOR			HealthColourBad;

		float HealthMax;
		float HealthCurrent;
		float HealthTarget;

	public:

		Base( Game* CurrentGame, int StartHealth );
		virtual ~Base();
		virtual void Update();

		void TakeDamage( int DamageAmount );
		void RegainHealth( int RestoreAmount );
		void BoostMax( int AdditionalAmount, bool BoostCurrent );
};