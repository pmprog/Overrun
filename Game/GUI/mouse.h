
#pragma once

#include "../../Framework/Core/main.h"

#define ALLEGRO_EVENT_MOUSE_CLICK					ALLEGRO_GET_EVENT_TYPE('M', 'c', 'c', 'k')
#define ALLEGRO_EVENT_MOUSE_DOUBLECLICK		ALLEGRO_GET_EVENT_TYPE('M', 'c', 'd', 'b')
#define ALLEGRO_EVENT_MOUSE_BOXED					ALLEGRO_GET_EVENT_TYPE('M', 'c', 'b', 'x')

class Mouse
{
	private:
		ALLEGRO_EVENT_QUEUE*	mouseQueue;
		ALLEGRO_EVENT_SOURCE	mouseEventSource;

		bool isBoxing;
		bool blockBoxing;
		double lastClickTime;
		double lastDblClickTime;

		static void event_destructor(ALLEGRO_USER_EVENT* e);

	public:
		Vector2 mouseDownAt;
		unsigned int mouseDownButton;
		Vector2 Position;
		int ClickFidelity;
		double DoubleClickFidelity;
		bool AllowBoxing;

		Mouse();
		~Mouse();

		void Update();
		void Render();

		void CancelBoxing();

		ALLEGRO_EVENT_SOURCE* get_event_source();
};