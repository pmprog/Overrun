
#include "imagebutton.h"
#include "mouse.h"

ImageButton::ImageButton( ALLEGRO_BITMAP* normal ) : Control()
{
	ImageNormal = normal;
	ImageDepressed = 0;
	ImageDisabled = 0;
	Size.X = al_get_bitmap_width( normal );
	Size.Y = al_get_bitmap_height( normal );
	Depressed = false;
	UnloadImagesOnDelete = true;
}

ImageButton::ImageButton( ALLEGRO_BITMAP* normal, ALLEGRO_BITMAP* depressed, ALLEGRO_BITMAP* disabled ) : Control()
{
	ImageNormal = normal;
	ImageDepressed = depressed;
	ImageDisabled = disabled;
	Size.X = al_get_bitmap_width( normal );
	Size.Y = al_get_bitmap_height( normal );
	Depressed = false;
	UnloadImagesOnDelete = true;
}

ImageButton::~ImageButton()
{
	if( UnloadImagesOnDelete )
	{
		al_destroy_bitmap( ImageNormal );
		if( ImageDepressed != 0 )
			al_destroy_bitmap( ImageDepressed );
		if( ImageDisabled != 0 )
			al_destroy_bitmap( ImageDisabled );
	}
}

bool ImageButton::Event(ALLEGRO_EVENT *e)
{
	ALLEGRO_EVENT ev;

	switch( e->type )
	{
		case ALLEGRO_EVENT_MOUSEEX_DOWN:
			if( Enabled && Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
			{
				((Mouse*)e->user.data1)->CancelBoxing();
				Depressed = true;
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_UP:
			if( Depressed )
				Depressed = false;
			if( Enabled && Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
		case ALLEGRO_EVENT_MOUSEEX_CLICK:
			if( Enabled && Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
			{
				ev.user.data1 = (intptr_t)this;
				ev.type = ALLEGRO_EVENT_BUTTON_CLICK;
				al_emit_user_event( &controlEventSource, &ev, 0 );
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_DOUBLECLICK:
			if( Enabled && Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
	}
	return false;
}

void ImageButton::Render()
{
	if( !Visible )
		return;

	if( !Enabled )
	{
		if( ImageDisabled != 0 )
			al_draw_bitmap( ImageDisabled, Position.X, Position.Y, 0 );
		else
			al_draw_tinted_bitmap( ImageNormal, al_map_rgb( 64, 64, 64 ), Position.X, Position.Y, 0 );
	} else if( Depressed ) {
		if( ImageDepressed != 0 )
		{
			al_draw_bitmap( ImageDepressed, Position.X, Position.Y, 0 );
		} else {
			al_draw_bitmap( ImageNormal, Position.X, Position.Y, 0 );
			al_draw_filled_rectangle( Position.X, Position.Y, Position.X + Size.X, Position.Y + Size.Y, al_map_rgba( 0, 0, 0, 128 ) );
		}
	} else {
		al_draw_bitmap( ImageNormal, Position.X, Position.Y, 0 );
	}
}

void ImageButton::Update()
{
}
