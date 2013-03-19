
#include "../Game/building.h"

class Base : public Building
{

	public:
		int HealthMax;
		int HealthCurrent;


		Base( Game* CurrentGame, int StartHealth );
		virtual ~Base();
};