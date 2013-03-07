
#include "button.h"

Button::Button()
{
	BorderHighlight = al_map_rgb( 255, 255, 255 );
	BorderLowlight = al_map_rgb( 96, 96, 96 );
	Background = al_map_rgb( 128, 128, 128 );
	Foreground = al_map_rgb( 255, 255, 255 );
	BorderWidth = 1;
	FontName = "Resource/visitor1.ttf";
	FontSize = 12;
	FontFlags = ALLEGRO_TTF_MONOCHROME;
}

void Button::Event(ALLEGRO_EVENT *e)
{

}

void Button::Render()
{
	if( !Visible )
		return;

	float pts[8] = {
		Position.X,																												Position.Y,
		Position.X,																												Position.Y + Size.Y,
		Position.X + Size.X,																							Position.Y + Size.Y,
		Position.X + Size.X,																							Position.Y
	};

	al_draw_filled_rectangle( Position.X, Position.Y, Position.X + Size.X, Position.Y + Size.Y, Background );
	al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), Foreground, Position.X + (Size.X / 2), Position.Y, ALLEGRO_ALIGN_CENTRE, Text.c_str() );

}

void Button::Update()
{
}
