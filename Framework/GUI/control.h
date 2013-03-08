
#pragma once

#include "../Core/main.h"

class Control
{
	protected:
		ALLEGRO_EVENT_SOURCE	controlEventSource;

	public:
		Vector2 Position;
		Vector2 Size;
		bool Enabled;
		bool Visible;

		std::string FontName;
		int FontSize;
		int FontFlags;

		Control();

		virtual ~Control()
		{
			al_unregister_event_source( EventQueue, &controlEventSource );
			al_destroy_user_event_source( &controlEventSource );
		};

		virtual bool Event(ALLEGRO_EVENT *e) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

};