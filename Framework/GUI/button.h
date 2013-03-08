
#pragma once

#include "control.h"

#define ALLEGRO_EVENT_BUTTON_CLICK					ALLEGRO_GET_EVENT_TYPE('B', 't', 'c', 'k')

class Button : public Control
{
	private:
		bool Depressed;

	public:
		ALLEGRO_COLOR BorderHighlight;
		ALLEGRO_COLOR BorderLowlight;
		ALLEGRO_COLOR Background;
		ALLEGRO_COLOR Foreground;
		std::string Text;
		int BorderWidth;

		Button();
		virtual bool Event(ALLEGRO_EVENT *e);
		virtual void Update();
		virtual void Render();

};