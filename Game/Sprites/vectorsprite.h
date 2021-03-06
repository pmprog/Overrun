
#pragma once

#include <list>
#include "../../Framework/Core/vector2.h"
#include "../Game/camera.h"

#ifndef VectorComponent
class VectorComponent;
#endif

class VectorSprite
{

	public:
		std::list<VectorComponent*> Components;

		~VectorSprite();

		void Update();
		void Render( Vector2* Position, Camera* View );

};