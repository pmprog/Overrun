
#pragma once

#include "control.h"

class Panel : public Control
{
	public:
		ALLEGRO_COLOR Border;
		ALLEGRO_COLOR Background;
		bool HasTitle;
		char* Title;
		int BorderWidth;
		int CornerCut;

		Panel();
		virtual void Event(ALLEGRO_EVENT *e);
		virtual void Render();
		virtual void Update();

};