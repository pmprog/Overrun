
#pragma once

#include <list>
#include "../../Framework/Core/vector2.h"

#ifndef VectorComponent
class VectorComponent;
#endif

class VectorSprite
{

	public:
		std::list<VectorComponent*> Components;

		void Update();
		void Render( Vector2* Position, double ScreenRotation );

};