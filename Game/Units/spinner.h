
#pragma once

#include "../Game/unit.h"

class Spinner : public Unit
{
	public:
		Spinner( ConfigFile* UnitConfig, Path* MapPath );
		virtual ~Spinner();
};