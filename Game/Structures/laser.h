
#include "../Game/building.h"

class LaserTower : public Building
{

	private:


	public:
		LaserTower( Game* CurrentGame );
		virtual ~LaserTower();
		virtual void Update();

};