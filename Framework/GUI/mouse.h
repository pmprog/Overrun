
#pragma once

#include "../Core/main.h"

#define ALLEGRO_EVENT_MOUSEEX_MOVE					ALLEGRO_GET_EVENT_TYPE('M', 'c', 'm', 'v')
#define ALLEGRO_EVENT_MOUSEEX_DOWN					ALLEGRO_GET_EVENT_TYPE('M', 'c', 'd', 'w')
#define ALLEGRO_EVENT_MOUSEEX_UP						ALLEGRO_GET_EVENT_TYPE('M', 'c', 'u', 'p')
#define ALLEGRO_EVENT_MOUSEEX_CLICK					ALLEGRO_GET_EVENT_TYPE('M', 'c', 'c', 'k')
#define ALLEGRO_EVENT_MOUSEEX_DOUBLECLICK		ALLEGRO_GET_EVENT_TYPE('M', 'c', 'd', 'b')
#define ALLEGRO_EVENT_MOUSEEX_BOXED					ALLEGRO_GET_EVENT_TYPE('M', 'c', 'b', 'x')

/*
	Mouse User Events:
		data1 = Mouse*		: Cursor
		data2 = Vector2*	: Position or Box.TopLeft
		data3 = Vector2*	: Box.BottomRight
		data4 = int				: Button Mask
*/

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