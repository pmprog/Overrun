
#include "vectorcomponent.h"

VectorComponent::VectorComponent( int Type, ALLEGRO_COLOR Colour, std::list<Vector2*> Verticies )
{
	ComponentType = Type;
	DrawColour = Colour;
	DrawThickness = 1;
	Rotation = 0.0;
	RotationPerFrame = 0.0;
	Points = Verticies;
}

void VectorComponent::Update()
{
	Rotation += RotationPerFrame;
	if( Rotation >= 360.0 )
		Rotation -= 360.0;
	if( Rotation < 0.0 )
		Rotation += 360.0;
};

void VectorComponent::Render( Vector2* Position, double ScreenRotation )
{
	Vector2 vx;
	float* pts;

	pts = (float*)malloc( Points.size() * sizeof( float ) );
	int idx = 0;
	for( std::list<Vector2*>::iterator i = Points.begin(); i != Points.end(); i++ )
	{
		Vector2* v = (Vector2*)(*i);
		RotateVector( v, Rotation + ScreenRotation, &vx );
		pts[idx] = vx.X + Position->X;
		pts[idx + 1] = vx.Y + Position->Y;
		idx += 2;
	}

	switch( ComponentType )
	{
		case VECTORSPRITE_COMPONENT_POLYLINE:
			al_draw_polyline( pts, Points.size(), ALLEGRO_LINE_JOIN_ROUND, ALLEGRO_LINE_CAP_ROUND, DrawColour, DrawThickness, 0 );
			break;
		case VECTORSPRITE_COMPONENT_CIRCLE:
			al_draw_circle( Position->X, Position->Y, Points.front()->X, DrawColour, DrawThickness );
			break;
		case VECTORSPRITE_COMPONENT_POLYGON:
			al_draw_polygon( pts, Points.size(), ALLEGRO_LINE_JOIN_ROUND, DrawColour, DrawThickness, 0 );
			break;
		case VECTORSPRITE_COMPONENT_CIRCLE_FILLED:
			al_draw_filled_circle( Position->X, Position->Y, Points.front()->X, DrawColour );
			break;
		case VECTORSPRITE_COMPONENT_POLYGON_FILLED:
			al_draw_filled_polygon( pts, Points.size(), DrawColour );
			break;
	}

	free( (void*)pts );
};