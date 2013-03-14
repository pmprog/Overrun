
#include "unit.h"

class Spinner : public Unit
{
	private:
		VectorComponent* circShield;

	public:
		Spinner( Vector2* StartPosition, float HealthMultiplier, float ShieldMultiplier, int CashReward );
		virtual void Update();
};