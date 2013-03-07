
#include "panel.h"

Panel::Panel()
{
	Border = al_map_rgb( 0, 0, 0 );
	Background = al_map_rgba( 0, 0, 0, 128 );
	Foreground = al_map_rgb( 255, 255, 255 );
	HasTitle = false;
	BorderWidth = 4;
	CornerCut = 16;
	FontName = "Resource/visitor1.ttf";
	FontSize = 12;
	FontFlags = ALLEGRO_TTF_MONOCHROME;
}

void Panel::Event(ALLEGRO_EVENT *e)
{
}

void Panel::Render()
{
	float pts[18] = {
		Position.X,																												Position.Y,
		Position.X,																												Position.Y + Size.Y,
		Position.X + Size.X,																							Position.Y + Size.Y,
		Position.X + Size.X,																							min( Position.Y + CornerCut, Position.Y + Size.Y ),
		min( Position.X + Size.X - CornerCut, Position.X + Size.X ),			Position.Y,
		Position.X + BorderWidth,																					min( Position.Y + max( CornerCut, FontSize ) + BorderWidth, Position.Y + Size.Y ),
		Position.X + Size.X - BorderWidth,																min( Position.Y + max( CornerCut, FontSize ) + BorderWidth, Position.Y + Size.Y - BorderWidth ),
		Position.X + Size.X - BorderWidth,																Position.Y + Size.Y - BorderWidth,
		Position.X + BorderWidth,																					Position.Y + Size.Y - BorderWidth
	};
	int holes[2] = { 5, 9 };

	if( HasTitle )
	{
		al_draw_filled_polygon_with_holes( (float*)&pts, 9, (int*)&holes, 2, Border );
		al_draw_filled_rectangle( pts[2] + BorderWidth, pts[3], pts[6] - BorderWidth, pts[7] - BorderWidth, Background );
		al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), Foreground, Position.X + BorderWidth, Position.Y + BorderWidth, 0, Title.c_str() );
	} else {
		al_draw_filled_polygon( (float*)&pts, 5, Background );
		al_draw_polygon( (float*)&pts, 5, ALLEGRO_LINE_JOIN_MITER, Border, BorderWidth, 2 );
	}

}

void Panel::Update()
{
}
