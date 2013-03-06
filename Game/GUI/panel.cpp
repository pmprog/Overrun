
#include "panel.h"

Panel::Panel()
{
	Border = al_map_rgb( 0, 0, 0 );
	Background = al_map_rgba( 0, 0, 0, 128 );
	HasTitle = false;
	BorderWidth = 4;
	CornerCut = 16;
}

void Panel::Event(ALLEGRO_EVENT *e)
{
}

void Panel::Render()
{
	float pts[18];
	int holes[2] = { 5, 9 };

	pts[0] = min( Position.X + CornerCut, Position.X + Size.X );
	pts[1] = Position.Y;
	pts[2] = Position.X;
	pts[3] = min( Position.Y + CornerCut, Position.Y + Size.Y );
	pts[4] = Position.X;
	pts[5] = Position.Y + Size.Y;
	pts[6] = Position.X + Size.X;
	pts[7] = Position.Y + Size.Y;
	pts[8] = Position.X + Size.X;
	pts[9] = Position.Y;
	pts[10] = pts[2] + BorderWidth;
	pts[11] = pts[3];
	pts[12] = pts[6] - BorderWidth;
	pts[13] = pts[3];
	pts[14] = pts[6] - BorderWidth;
	pts[15] = pts[7] - BorderWidth;
	pts[16] = pts[2] + BorderWidth;
	pts[17] = pts[7] - BorderWidth;
	

	if( HasTitle )
	{
		al_draw_filled_polygon_with_holes( (float*)&pts, 9, (int*)&holes, 2, Border );
		al_draw_filled_rectangle( pts[2] + BorderWidth, pts[3], pts[6] - BorderWidth, pts[7] - BorderWidth, Background );
	} else {
		al_draw_filled_polygon( (float*)&pts, 5, Background );
		al_draw_polygon( (float*)&pts, 5, ALLEGRO_LINE_JOIN_MITER, Border, BorderWidth, 2 );
	}

}

void Panel::Update()
{
}
