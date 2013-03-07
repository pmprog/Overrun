
#include "boot.h"
#include "configure.h"

void BootUp::Begin()
{
	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	cursor = new Mouse( EventQueue );
	cursor->AllowBoxing = true;
	r = 0;
	testPanel = new Panel();
	testPanel->Position.X = 60;
	testPanel->Position.Y = 60;
	testPanel->Size.X = 120;
	testPanel->Size.Y = 80;
	testPanel->HasTitle = false;

	testPanel2 = new Panel();
	testPanel2->Position.X = 300;
	testPanel2->Position.Y = 150;
	testPanel2->Size.X = 200;
	testPanel2->Size.Y = 600;
	testPanel2->HasTitle = true;
	testPanel2->Title = "Testing Panel";
	testPanel2->Background = al_map_rgba( 128, 128, 255, 128 );
	testPanel2->Border = al_map_rgb( 128, 128, 255 );
	//testPanel2->CornerCut = 16;
	testPanel2->FontSize = 24;
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
			r = (r + 64) % 256;
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
	testPanel->Update();
	testPanel2->Update();
	cursor->Update();

}

void BootUp::Render()
{
	al_clear_to_color( al_map_rgb( 48, 48, 48 ) );

	al_draw_text( Fonts->GetFont("Resource/forte.ttf", 24, 0), al_map_rgb( 255, 255, 255 ), 100, 300, 0, "RTesting Text dsvnjsdvnsjdvindivn uivnsduvin sduvndu sivn" );


	al_draw_filled_circle( 40, 60, 40, al_map_rgb( 128, 128, 128 ) );

	testPanel->Render();
	testPanel2->Render();
	cursor->Render();
}

