#define _core
#include "main.h"
#include "../../Game/boot.h"
#include "../../Game/configure.h"

int main( int argc, char* argv[] )
{
	ALLEGRO_EVENT e;
	ALLEGRO_TIMER* t;
	int64_t framesToUpdate = 0;

	if( !al_init() )
	{
		return -1;
	}
	
	al_init_font_addon();
	if( !al_install_keyboard() || !al_install_mouse() || !al_init_primitives_addon() || !al_init_ttf_addon() || !al_init_image_addon() || !al_init_acodec_addon() || !al_install_audio() )
	{
		return -1;
	}

#if NETWORK_SUPPORT != 0
	if( !install_network() )
	{
		return -1;
	}
#endif

	voice = al_create_voice(44100, ALLEGRO_AUDIO_DEPTH_INT16, ALLEGRO_CHANNEL_CONF_2);
	if (!voice)
		return 1;
	mixer = al_create_mixer(44100, ALLEGRO_AUDIO_DEPTH_FLOAT32, ALLEGRO_CHANNEL_CONF_2);
	if (!mixer)
		return 1;
	if (!al_attach_mixer_to_voice(mixer, voice))
		return 1;


	// Random number is guarenteed to be random
	srand( 5 );

	GameStack = new StageStack();
	CurrentConfiguration = new Configuration();

	if( CurrentConfiguration->FullScreen )
		al_set_new_display_flags( ALLEGRO_FULLSCREEN );

	bool foundMode = false;
	int fallbackW = 800;
	int fallbackH = 480;
	for( int modeIdx = 0; modeIdx < al_get_num_display_modes(); modeIdx++ )
	{
		if( al_get_display_mode( modeIdx, &ScreenMode ) != NULL )
		{
			if( ScreenMode.width == CurrentConfiguration->ScreenWidth && ScreenMode.height == CurrentConfiguration->ScreenHeight )
			{
				foundMode = true;
			} else {
				fallbackW = ScreenMode.width;
				fallbackH = ScreenMode.height;
			}
		}

		if( foundMode )
			break;
	}


	if( foundMode )
	{
		Screen = al_create_display( CurrentConfiguration->ScreenWidth, CurrentConfiguration->ScreenHeight );
	} else {
		Screen = al_create_display( fallbackW, fallbackH );
	}

	al_hide_mouse_cursor( Screen );

	t = al_create_timer( 1.0 / SCREEN_FPS );
  if( t == NULL )
    Quit = true;
  al_start_timer( t );


	EventQueue = al_create_event_queue();
	al_register_event_source( EventQueue, al_get_display_event_source( Screen ) );
	al_register_event_source( EventQueue, al_get_keyboard_event_source() );
	al_register_event_source( EventQueue, al_get_mouse_event_source() );
	al_register_event_source( EventQueue, al_get_timer_event_source( t ) );
#if NETWORK_SUPPORT != 0
	al_register_event_source( EventQueue, get_network_event_source() );
#endif

	al_set_blender( ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA );

	GameStack->Push( (Stage*)new BootUp() );

	while( !Quit )
	{
		if( GameStack->IsEmpty() )
		{
			Quit = true;
		} else {
			while( al_get_next_event( EventQueue, &e ) )
			{
				switch( e.type )
				{
					case ALLEGRO_EVENT_DISPLAY_CLOSE:
						Quit = true;
						break;
					case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
						al_reconfigure_joysticks();
						break;
					case ALLEGRO_EVENT_TIMER:
						framesToUpdate++;
						break;
					default:
						if( !GameStack->IsEmpty() )
							GameStack->Current()->Event( &e );
						break;
				}
			}

			if( framesToUpdate > 0 )
			{
				for( int frmUp = 0; frmUp < framesToUpdate; frmUp++ )
				{
					if( !GameStack->IsEmpty() )
						GameStack->Current()->Update();
				}
				framesToUpdate = 0;
			}

			al_clear_to_color( al_map_rgb( 128, 128, 128 ) );
			if( !GameStack->IsEmpty() )
				GameStack->Current()->Render();
			al_flip_display();
		}
	}

	while( !GameStack->IsEmpty() )
	{
		GameStack->Pop();
	}

	al_destroy_event_queue( EventQueue );
	al_destroy_display( Screen );

#if NETWORK_SUPPORT != 0
	uninstall_network();
#endif
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();
	al_shutdown_ttf_addon();
	al_shutdown_image_addon();
	al_uninstall_audio();
	al_shutdown_font_addon();

	return 0;
}