
#include "panel.h"
#include "mouse.h"

Panel::Panel() : Control()
{
	Border = al_map_rgb( 0, 0, 0 );
	Background = al_map_rgba( 0, 0, 0, 128 );
	Foreground = al_map_rgb( 255, 255, 255 );
	HasTitle = false;
	BorderWidth = 4;
	CornerCut = 6;
}

bool Panel::Event(ALLEGRO_EVENT *e)
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
			if( Enabled && Visible && ((Vector2*)e->user.data2)->X >= Position.X && ((Vector2*)e->user.data2)->X < Position.X + Size.X && ((Vector2*)e->user.data2)->Y >= Position.Y && ((Vector2*)e->user.data2)->Y < Position.Y + Size.Y )
				return true;
			break;
	}
	return false;
}

void Panel::Render()
{
	if( !Visible )
		return;

	float pts[18] = {
		Position.X,																												Position.Y,
		Position.X,																												Position.Y + Size.Y,
		Position.X + Size.X,																							Position.Y + Size.Y,
		Position.X + Size.X,																							min( Position.Y + CornerCut, Position.Y + Size.Y ),
		max( Position.X + Size.X - CornerCut, Position.X ),								Position.Y,
		Position.X + BorderWidth,																					min( Position.Y + max( CornerCut, FontSize + BorderWidth ) + BorderWidth, Position.Y + Size.Y ),
		Position.X + Size.X - BorderWidth,																min( Position.Y + max( CornerCut, FontSize + BorderWidth ) + BorderWidth, Position.Y + Size.Y - BorderWidth ),
		Position.X + Size.X - BorderWidth,																Position.Y + Size.Y - BorderWidth,
		Position.X + BorderWidth,																					Position.Y + Size.Y - BorderWidth
	};
	int holes[2] = { 5, 9 };

	if( CornerCut == 0 )
	{
		al_draw_filled_rectangle( pts[0], pts[1], pts[4], pts[5], Background );
		if( HasTitle )
		{
			al_draw_filled_rectangle( pts[0], pts[1], pts[4], Position.Y + FontSize + BorderWidth, Border );
			al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), Foreground, Position.X + BorderWidth, Position.Y + BorderWidth, 0, Title.c_str() );
		}
		al_draw_rectangle( pts[0], pts[1], pts[4], pts[5], Border, BorderWidth );
	} else {
		if( HasTitle )
		{
			al_draw_filled_polygon_with_holes( (float*)&pts, 9, (int*)&holes, 2, Border );
			al_draw_filled_rectangle( pts[10], pts[11], pts[14], pts[15], Background );
			al_draw_text( Fonts->GetFont( FontName, FontSize, FontFlags ), Foreground, Position.X + BorderWidth, Position.Y + BorderWidth, 0, Title.c_str() );
		} else {
			al_draw_filled_polygon( (float*)&pts, 5, Background );
			al_draw_polygon( (float*)&pts, 5, ALLEGRO_LINE_JOIN_MITER, Border, BorderWidth, 2 );
		}
	}

}

void Panel::Update()
{
}
