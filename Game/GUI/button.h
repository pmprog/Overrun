
#pragma once

#include "control.h"

class Button : public Control
{
	public:
		ALLEGRO_COLOR BorderHighlight;
		ALLEGRO_COLOR BorderLowlight;
		ALLEGRO_COLOR Background;
		ALLEGRO_COLOR Foreground;
		std::string Text;
		int BorderWidth;

		Button();
		virtual void Event(ALLEGRO_EVENT *e);
		virtual void Update();
		virtual void Render();

};