
#pragma once

#include "control.h"

#define ALLEGRO_EVENT_BUTTON_CLICK					ALLEGRO_GET_EVENT_TYPE('B', 't', 'c', 'k')

class Label : public Control
{

	public:
		ALLEGRO_COLOR Background;
		ALLEGRO_COLOR Foreground;
		std::string Text;

		Label();
		virtual bool Event(ALLEGRO_EVENT *e);
		virtual void Update();
		virtual void Render();

};