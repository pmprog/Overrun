
#include "../Game/building.h"
#include "../Game/damagable.h"

class Base : public Building, public Damagable
{

	private:
		VectorComponent*	HealthBar;
		ALLEGRO_COLOR			HealthColourGood;
		ALLEGRO_COLOR			HealthColourMid;
		ALLEGRO_COLOR			HealthColourBad;

	public:
		Base( Game* CurrentGame, int StartHealth );
		virtual ~Base();
		virtual void Update();

};