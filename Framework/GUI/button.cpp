
#include "button.h"
#include "mouse.h"

Button::Button() // : Control()
{
	BorderHighlight = al_map_rgb( 255, 255, 255 );
	BorderLowlight = al_map_rgb( 96, 96, 96 );
	Background = al_map_rgb( 128, 128, 128 );
	Foreground = al_map_rgb( 255, 255, 255 );
	BorderWidth = 1;
	Depressed = false;
}

bool Button::Event(ALLEGRO_EVENT *e)
{
	ALLEGRO_EVENT ev;

	switch( e->type )
	{
		case ALLEGRO_EVENT_MOUSEEX_DOWN:
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
			{
				((Mouse*)e->user.data1)->CancelBoxing();
				Depressed = true;
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_UP:
			if( Depressed )
				Depressed = false;
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
		case ALLEGRO_EVENT_MOUSEEX_CLICK:
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
			{
				if( Enabled )
				{
					ev.user.data1 = (intptr_t)this;
					ev.type = ALLEGRO_EVENT_BUTTON_CLICK;
					al_emit_user_event( &controlEventSource, &ev, 0 );
				}
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_DOUBLECLICK:
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
	}
	return false;
}

void Button::Render()
{
	if( !Visible )
		return;

	al_draw_filled_rectangle( Position.X, Position.Y, Position.X + Size.X, Position.Y + Size.Y, Background );
	if( Depressed )
		al_draw_filled_rectangle( Position.X, Position.Y, Position.X + Size.X, Position.Y + Size.Y, al_map_rgba( 0, 0, 0, 128 ) );

	al_draw_line( Position.X, Position.Y, Position.X + Size.X, Position.Y, (Depressed ? BorderLowlight : BorderHighlight), BorderWidth );
	al_draw_line( Position.X, Position.Y, Position.X, Position.Y + Size.Y, (Depressed ? BorderLowlight : BorderHighlight), BorderWidth );
	al_draw_line( Position.X, Position.Y + Size.Y, Position.X + Size.X, Position.Y + Size.Y, (Depressed ? BorderHighlight : BorderLowlight), BorderWidth );
	al_draw_line( Position.X + Size.X, Position.Y, Position.X + Size.X, Position.Y+ Size.Y, (Depressed ? BorderHighlight : BorderLowlight), BorderWidth );


	al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), (Enabled ? Foreground : BorderLowlight), Position.X + (Size.X / 2) + (Depressed ? 2 : 0), Position.Y + (Size.Y / 2) - (FontSize / 2) + (Depressed ? 2 : 0), ALLEGRO_ALIGN_CENTRE, Text.c_str() );

}

void Button::Update()
{
}
