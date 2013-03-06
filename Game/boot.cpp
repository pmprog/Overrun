
#include "boot.h"
#include "configure.h"

void BootUp::Begin()
{
	cursor = new Mouse( EventQueue );
	cursor->AllowBoxing = true;
	r = 0;
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{

}

void BootUp::Finish()
{
	delete cursor;
}

void BootUp::Event(ALLEGRO_EVENT *e)
{
	switch( e->type )
	{
		case ALLEGRO_EVENT_KEY_DOWN:
			switch( e->keyboard.keycode )
			{
				case ALLEGRO_KEY_ESCAPE:
					GameStack->Pop();
					break;
			}
			break;

		case ALLEGRO_EVENT_MOUSE_DOUBLECLICK:
			al_unref_user_event( &e->user );
			break;
		case ALLEGRO_EVENT_MOUSE_BOXED:
			al_unref_user_event( &e->user );
			break;
		case ALLEGRO_EVENT_MOUSE_CLICK:
			al_unref_user_event( &e->user );
			break;
	}
}

void BootUp::Update()
{
	cursor->Update();
}

void BootUp::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, r ) );


	
	cursor->Render();
}

