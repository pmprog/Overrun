
#include "mouse.h"


Mouse::Mouse() : AllowBoxing(false), ClickFidelity(3), isBoxing(false), DoubleClickFidelity(0.4), blockBoxing(false)
{
	mouseQueue = al_create_event_queue();
	al_register_event_source( mouseQueue, al_get_mouse_event_source() );

	al_init_user_event_source( &mouseEventSource );
	al_register_event_source( EventQueue, &mouseEventSource );

	ALLEGRO_MOUSE_STATE state;
	al_get_mouse_state( &state );
	
	Position.X = state.x;
	Position.Y = state.y;
	mouseDownAt.X = 0;
	mouseDownAt.Y = 0;
	mouseDownButton = 0;
	lastClickTime = 0;

}

Mouse::~Mouse()
{
	al_unregister_event_source( EventQueue, &mouseEventSource );
	al_destroy_event_queue( mouseQueue );
	al_destroy_user_event_source( &mouseEventSource );
}

void Mouse::Update()
{
	ALLEGRO_EVENT e;
	ALLEGRO_EVENT ev;
	while( al_get_next_event( mouseQueue, &e ) )
	{
		switch( e.type )
		{
			case ALLEGRO_EVENT_MOUSE_AXES:
				Position.X = e.mouse.x;
				Position.Y = e.mouse.y;
				if( mouseDownButton != 0 && AllowBoxing && !blockBoxing )
					isBoxing = true;
				if( !AllowBoxing && isBoxing )
					isBoxing = false;	// Cancel boxing if it has been disabled

				if( e.mouse.dx != 0 || e.mouse.dy != 0 )
				{
					ev.user.data1 = (intptr_t)this;
					ev.user.data2 = (intptr_t)malloc( sizeof( Position ) );
					memcpy( (void*)ev.user.data2, (void*)&Position, sizeof( Position ) );
					ev.user.data3 = (intptr_t)malloc( sizeof( Position ) );
					((Vector2*)ev.user.data3)->X = e.mouse.dx;
					((Vector2*)ev.user.data3)->Y = e.mouse.dy;
					ev.user.data4 = e.mouse.button;
					ev.type = ALLEGRO_EVENT_MOUSEEX_MOVE;
					al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );
				}
				if( e.mouse.dz != 0 )
				{
					ev.user.data1 = (intptr_t)this;
					ev.user.data2 = (intptr_t)malloc( sizeof( Position ) );
					memcpy( (void*)ev.user.data2, (void*)&Position, sizeof( Position ) );
					ev.user.data3 = 0;
					ev.user.data4 = e.mouse.dz;
					ev.type = ALLEGRO_EVENT_MOUSEEX_WHEEL;
					al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );
				}
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				Position.X = e.mouse.x;
				Position.Y = e.mouse.y;
				mouseDownAt.X = e.mouse.x;
				mouseDownAt.Y = e.mouse.y;
				mouseDownButton = e.mouse.button;

				ev.user.data1 = (intptr_t)this;
				ev.user.data2 = (intptr_t)malloc( sizeof( Position ) );
				memcpy( (void*)ev.user.data2, (void*)&Position, sizeof( Position ) );
				ev.user.data3 = 0;
				ev.user.data4 = e.mouse.button;
				ev.type = ALLEGRO_EVENT_MOUSEEX_DOWN;
				al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );
				break;
			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				blockBoxing = false;
				Position.X = e.mouse.x;
				Position.Y = e.mouse.y;

				ev.user.data1 = (intptr_t)this;
				ev.user.data2 = (intptr_t)malloc( sizeof( Position ) );
				memcpy( (void*)ev.user.data2, (void*)&Position, sizeof( Position ) );
				ev.user.data3 = 0;
				ev.user.data4 = e.mouse.button;
				ev.type = ALLEGRO_EVENT_MOUSEEX_UP;
				al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );

				if( mouseDownButton == e.mouse.button )
				{
					if( abs( e.mouse.x - mouseDownAt.X ) < ClickFidelity && abs( e.mouse.y - mouseDownAt.Y ) < ClickFidelity )
					{
						ev.user.data2 = (intptr_t)malloc( sizeof( mouseDownAt ) );
						memcpy( (void*)ev.user.data2, (void*)&mouseDownAt, sizeof( mouseDownAt ) );
						ev.type = ALLEGRO_EVENT_MOUSEEX_CLICK;
						al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );

						if( al_get_time() - lastClickTime < DoubleClickFidelity && al_get_time() - lastDblClickTime > DoubleClickFidelity )
						{
							ev.user.data2 = (intptr_t)malloc( sizeof( mouseDownAt ) );
							memcpy( (void*)ev.user.data2, (void*)&mouseDownAt, sizeof( mouseDownAt ) );
							ev.type = ALLEGRO_EVENT_MOUSEEX_DOUBLECLICK;
							al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );
							lastDblClickTime = al_get_time();
						}
						lastClickTime = al_get_time();

					}
					if( isBoxing )
					{
						ev.user.data2 = (intptr_t)malloc( sizeof( mouseDownAt ) );
						((Vector2*)ev.user.data2)->X = min(mouseDownAt.X, Position.X);
						((Vector2*)ev.user.data2)->Y = min(mouseDownAt.Y, Position.Y);
						ev.user.data3 = (intptr_t)malloc( sizeof( mouseDownAt ) );
						((Vector2*)ev.user.data3)->X = min(mouseDownAt.X, Position.X);
						((Vector2*)ev.user.data3)->Y = min(mouseDownAt.Y, Position.Y);
						ev.type = ALLEGRO_EVENT_MOUSEEX_BOXED;
						al_emit_user_event( &mouseEventSource, &ev, &Mouse::event_destructor );
						isBoxing = false;
					}
					mouseDownButton = 0;
				}
				break;
		}
	}
}

void Mouse::Render()
{
	ALLEGRO_COLOR mouseCol;

	if( mouseDownButton & 1 )
		mouseCol = al_map_rgb( 255, 255, 0 );
	else if( mouseDownButton & 2 )
		mouseCol = al_map_rgb( 255, 128, 0 );
	else
		mouseCol = al_map_rgb( 255, 255, 255 );

	if( isBoxing )
	{
		al_draw_rectangle( min(mouseDownAt.X, Position.X), min(mouseDownAt.Y, Position.Y), max(mouseDownAt.X, Position.X), max(mouseDownAt.Y, Position.Y), mouseCol, 1 );
	}

	al_draw_filled_triangle( Position.X, Position.Y, Position.X + 16, Position.Y + 16, Position.X, Position.Y + 25, mouseCol );
	al_draw_triangle( Position.X, Position.Y, Position.X + 16, Position.Y + 16, Position.X, Position.Y + 25, al_map_rgb( 0, 0, 0 ), 1 );
}

void Mouse::event_destructor(ALLEGRO_USER_EVENT* e)
{
	free( (void*)e->data2 );
	if( e->data3 != 0 )
		free( (void*)e->data3 );
}

void Mouse::CancelBoxing()
{
	isBoxing = false;
	blockBoxing = true;
}
