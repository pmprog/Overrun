
#include "vectorcomponent.h"

VectorComponent::VectorComponent( int Type, ALLEGRO_COLOR Colour, float* Verticies, int VertexCount ) : Points(0)
{
	PointCount = 0;
	ComponentType = Type;
	DrawColour = Colour;
	DrawThickness = 1;
	Rotation = 0.0;
	RotationPerFrame = 0.0;

	PointCount = VertexCount;
	Points = (float*)malloc( VertexCount * sizeof( float ) * 2 );
	memcpy( (void*)Points, (void*)Verticies, VertexCount * sizeof( float ) * 2 );
}

VectorComponent::VectorComponent( int Type, ALLEGRO_COLOR Colour, std::list<Vector2*> Verticies ) : Points(0)
{
	ComponentType = Type;
	DrawColour = Colour;
	DrawThickness = 1;
	Rotation = 0.0;
	RotationPerFrame = 0.0;

	int pnt = 0;
	PointCount = Verticies.size();
	Points = (float*)malloc( Verticies.size() * sizeof( float ) * 2 );
	for( std::list<Vector2*>::iterator i = Verticies.begin(); i != Verticies.end(); i++ )
	{
		Vector2* v = (Vector2*)(*i);
		Points[pnt] = (float)v->X;
		Points[pnt + 1] = (float)v->Y;
		pnt += 2;
	}
}

VectorComponent::~VectorComponent()
{
	if( Points != 0 )
		free( (void*)Points );
}

void VectorComponent::Update()
{
	Rotation += RotationPerFrame;
	if( Rotation >= 360.0 )
		Rotation -= 360.0;
	if( Rotation < 0.0 )
		Rotation += 360.0;
};

void VectorComponent::Render( Vector2* Position, double ScreenRotation, double Zoom )
{
	Vector2 vx;
	float* pts;

	pts = (float*)malloc( PointCount * sizeof( float ) * 2 );
	for( int p = 0; p < PointCount; p++ )
	{
		Vector2 v;
		v.X = Points[p * 2];
		v.Y = Points[(p * 2) + 1];
		RotateVector( &v, Rotation + ScreenRotation, &vx );
		pts[p * 2] = (vx.X * Zoom) + Position->X;
		pts[(p * 2) + 1] = (vx.Y * Zoom) + Position->Y;
	}

	switch( ComponentType )
	{
		case VECTORSPRITE_COMPONENT_POLYLINE:
			al_draw_polyline( pts, PointCount, ALLEGRO_LINE_JOIN_ROUND, ALLEGRO_LINE_CAP_ROUND, DrawColour, DrawThickness, 0 );
			break;
		case VECTORSPRITE_COMPONENT_CIRCLE:
			al_draw_circle( pts[0], pts[1], Points[2] * Zoom, DrawColour, DrawThickness );
			break;
		case VECTORSPRITE_COMPONENT_POLYGON:
			al_draw_polygon( pts, PointCount, ALLEGRO_LINE_JOIN_ROUND, DrawColour, DrawThickness, 0 );
			break;
		case VECTORSPRITE_COMPONENT_CIRCLE_FILLED:
			al_draw_filled_circle( pts[0], pts[1], Points[2] * Zoom, DrawColour );
			break;
		case VECTORSPRITE_COMPONENT_POLYGON_FILLED:
			al_draw_filled_polygon( pts, PointCount, DrawColour );
			break;
	}

	free( (void*)pts );
};