
#pragma once

#include <list>

#ifndef Control
class Control;
#endif
#ifndef Mouse
class Mouse;
#endif

class GuiHost
{
	private:
		ALLEGRO_EVENT_QUEUE*	guiQueue;

	public:
		Control* ActiveControl;
		std::list<Control*> Controls;
		Mouse* Cursor;
		bool Visible;
		

		GuiHost();
		~GuiHost();

		void Update();
		void Render();

};

/*******************************************

guiQueue handles keyboard, mouse, and cursor input

Need some custom FIFO event system

*******************************************/