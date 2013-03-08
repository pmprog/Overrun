
#include "control.h"

Control::Control()
{
	Position.X = 0;
	Position.Y = 0;
	Size.X = 0;
	Size.Y = 0;
	Enabled = true;
	Visible = true;
	FontName = "Resource/visitor1.ttf";
	FontSize = 14;
	FontFlags = ALLEGRO_TTF_MONOCHROME;

	al_init_user_event_source( &controlEventSource );
	al_register_event_source( EventQueue, &controlEventSource );
}

/*
Control::~Control()
{
	al_unregister_event_source( EventQueue, &controlEventSource );
	al_destroy_user_event_source( &controlEventSource );
}
*/