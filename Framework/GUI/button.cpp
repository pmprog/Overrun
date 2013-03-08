
#include "button.h"
#include "mouse.h"

Button::Button() : Control()
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
	switch( e->type )
	{
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			if( Enabled && Visible && e->mouse.x >= Position.X && e->mouse.x < Position.X + Size.X && e->mouse.y >= Position.Y && e->mouse.y < Position.Y + Size.Y )
			{
				Depressed = true;
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			if( Depressed )
				Depressed = false;
			break;
		case ALLEGRO_EVENT_MOUSE_CLICK:
			if( Enabled && Visible && e->mouse.x >= Position.X && e->mouse.x < Position.X + Size.X && e->mouse.y >= Position.Y && e->mouse.y < Position.Y + Size.Y )
			{
				// TODO Emit ButtonClick
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_DOUBLECLICK:
			if( Enabled && Visible && e->mouse.x >= Position.X && e->mouse.x < Position.X + Size.X && e->mouse.y >= Position.Y && e->mouse.y < Position.Y + Size.Y )
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


	al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), Foreground, Position.X + (Size.X / 2), Position.Y, ALLEGRO_ALIGN_CENTRE, Text.c_str() );

}

void Button::Update()
{
}
