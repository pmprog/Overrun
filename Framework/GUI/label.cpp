
#include "label.h"
#include "mouse.h"

Label::Label() // : Control()
{
	Background = al_map_rgb( 0, 0, 0 );
	Foreground = al_map_rgb( 255, 255, 255 );
	TextAlignment = ALLEGRO_ALIGN_LEFT;
}

bool Label::Event(ALLEGRO_EVENT *e)
{
	switch( e->type )
	{
		case ALLEGRO_EVENT_MOUSEEX_DOWN:
			if( Enabled && Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
			{
				((Mouse*)e->user.data1)->CancelBoxing();
				return true;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_UP:
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
		case ALLEGRO_EVENT_MOUSEEX_CLICK:
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
		case ALLEGRO_EVENT_MOUSEEX_DOUBLECLICK:
			if( Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
	}
	return false;
}

void Label::Render()
{
	if( !Visible )
		return;

	if( Background.a > 0.0 )
		al_draw_filled_rectangle( Position.X, Position.Y, Position.X + Size.X, Position.Y + Size.Y, Background );

	if( Foreground.a > 0.0 )
	{
		int drawXOrigin;
		switch( TextAlignment )
		{
			case ALLEGRO_ALIGN_LEFT:
				drawXOrigin = Position.X;
				break;
			case ALLEGRO_ALIGN_CENTRE:
				drawXOrigin = Position.X + (Size.X / 2);
				break;
			case ALLEGRO_ALIGN_RIGHT:
				drawXOrigin = Position.X + Size.X;
				break;
		}

		al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), Foreground, drawXOrigin, Position.Y + (Size.Y / 2) - (FontSize / 2), TextAlignment, Text.c_str() );
	}

}

void Label::Update()
{
}
