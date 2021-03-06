
#pragma once

#include "control.h"

class Panel : public Control
{
	public:
		ALLEGRO_COLOR Border;
		ALLEGRO_COLOR Background;
		ALLEGRO_COLOR Foreground;
		bool HasTitle;
		std::string Title;
		int BorderWidth;
		int CornerCut;

		Panel();
		virtual bool Event(ALLEGRO_EVENT *e);
		virtual void Update();
		virtual void Render();

		void GetClientArea( Vector2* TopLeft, Vector2* BottomRight );
};