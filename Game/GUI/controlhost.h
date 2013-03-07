
#pragma once

#include <list>
#include "control.h"

class ControlHost : public Control
{
	public:
		std::list<Control*> Controls;

		ControlHost();
		ControlHost( ControlHost* parentHost );

		virtual void Event(ALLEGRO_EVENT *e);
		virtual void Update();
		virtual void Render();
};