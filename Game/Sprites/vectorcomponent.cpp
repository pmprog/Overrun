
#include "vectorcomponent.h"

VectorComponent::VectorComponent( int Type, ALLEGRO_COLOR DrawColour, float* Verticies, int VertexCount ) : Points(0)
{
	ComponentType = Type;
	Colour = DrawColour;
	LineThickness = 1;
	Scale = 1.0;
	Rotation = 0.0;

	PointCount = VertexCount;
	Points = (float*)malloc( VertexCount * sizeof( float ) * 2 );
	memcpy( (void*)Points, (void*)Verticies, VertexCount * sizeof( float ) * 2 );

	InitDefaults();
}

VectorComponent::VectorComponent( int Type, ALLEGRO_COLOR DrawColour, std::list<Vector2*> Verticies ) : Points(0)
{
	ComponentType = Type;
	Colour = DrawColour;
	LineThickness = 1;
	Rotation = 0.0;

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

	InitDefaults();
}

void VectorComponent::InitDefaults()
{
	ColourTarget.a = Colour.a;
	ColourTarget.r = Colour.r;
	ColourTarget.g = Colour.g;
	ColourTarget.b = Colour.b;
	ColourDelta.a = 0;
	ColourDelta.r = 0;
	ColourDelta.g = 0;
	ColourDelta.b = 0;

	ScaleTarget = 1.0;
	ScaleDelta = 0.0;

	ThicknessTarget = LineThickness;

	RotationContinual = true;
	RotationTarget = 0.0;
	RotationDelta = 0.0;
}

VectorComponent::~VectorComponent()
{
	if( Points != 0 )
		free( (void*)Points );
}

void VectorComponent::Update()
{
	if( ColourTarget.a != Colour.a )
	{
		Colour.a += ( abs(ColourDelta.a) < abs(ColourTarget.a - Colour.a) ? ColourDelta.a : ColourTarget.a - Colour.a );
		Colour.a = max( 0.0, min(Colour.a, 1.0) );
	}
	if( ColourTarget.r != Colour.r )
	{
		Colour.r += ( abs(ColourDelta.r) < abs(ColourTarget.r - Colour.r) ? ColourDelta.r : ColourTarget.r - Colour.r );
		Colour.r = max( 0.0, min(Colour.r, 1.0) );
	}
	if( ColourTarget.g != Colour.g )
	{
		Colour.g += ( abs(ColourDelta.g) < abs(ColourTarget.g - Colour.g) ? ColourDelta.g : ColourTarget.g - Colour.g );
		Colour.g = max( 0.0, min(Colour.g, 1.0) );
	}
	if( ColourTarget.b != Colour.b )
	{
		Colour.b += ( abs(ColourDelta.b) < abs(ColourTarget.b - Colour.b) ? ColourDelta.b : ColourTarget.b - Colour.b );
		Colour.b = max( 0.0, min(Colour.b, 1.0) );
	}

	if( Scale != ScaleTarget )
		Scale += ( abs(ScaleDelta) < abs(ScaleTarget - Scale) ? ScaleDelta : ScaleTarget - Scale );

	if( ThicknessTarget > LineThickness )
		LineThickness++;
	else if( ThicknessTarget < LineThickness )
		LineThickness--;

	if( RotationContinual )
	{
		Rotation += RotationDelta;
	} else {
		double TravelDistance = RotationTarget - Rotation;
		if( Rotation < RotationTarget )
		{
			if( abs( (RotationTarget-360) - Rotation ) < abs(TravelDistance) )
				TravelDistance = (RotationTarget-360) - Rotation;
		} else {
			if( abs( RotationTarget - Rotation + 360 ) < abs(TravelDistance) )
				TravelDistance = RotationTarget - Rotation + 360;
		}
		TravelDistance = max( -RotationDelta, min( RotationDelta, TravelDistance ) );
		Rotation += TravelDistance;
	}
	if( Rotation >= 360.0 )
		Rotation -= 360.0;
	if( Rotation < 0.0 )
		Rotation += 360.0;
}

void VectorComponent::Render( Vector2* Position, double ScreenRotation, double Zoom )
{
	Vector2 vx;
	float* pts;

	// If invisible, don't bother
	if( Colour.a > 0.0 || Scale > 0.0 )
	{

		pts = (float*)malloc( PointCount * sizeof( float ) * 2 );
		for( int p = 0; p < PointCount; p++ )
		{
			Vector2 v;
			v.X = Points[p * 2];
			v.Y = Points[(p * 2) + 1];
			RotateVector( &v, Rotation + ScreenRotation, &vx );
			pts[p * 2] = (vx.X * Zoom * Scale) + Position->X;
			pts[(p * 2) + 1] = (vx.Y * Zoom * Scale) + Position->Y;
		}

		switch( ComponentType )
		{
			case VECTORSPRITE_COMPONENT_POLYLINE:
				al_draw_polyline( pts, PointCount, ALLEGRO_LINE_JOIN_ROUND, ALLEGRO_LINE_CAP_ROUND, Colour, LineThickness, 0 );
				break;
			case VECTORSPRITE_COMPONENT_CIRCLE:
				al_draw_circle( pts[0], pts[1], Points[2] * Zoom * Scale, Colour, LineThickness );
				break;
			case VECTORSPRITE_COMPONENT_POLYGON:
				al_draw_polygon( pts, PointCount, ALLEGRO_LINE_JOIN_ROUND, Colour, LineThickness, 0 );
				break;
			case VECTORSPRITE_COMPONENT_CIRCLE_FILLED:
				al_draw_filled_circle( pts[0], pts[1], Points[2] * Zoom * Scale, Colour );
				break;
			case VECTORSPRITE_COMPONENT_POLYGON_FILLED:
				al_draw_filled_polygon( pts, PointCount, Colour );
				break;
		}

		free( (void*)pts );
	}
	
}

void VectorComponent::AnimateColourTo( ALLEGRO_COLOR* Destination, double Speed )
{
	ColourTarget.a = Destination->a;
	ColourTarget.r = Destination->r;
	ColourTarget.g = Destination->g;
	ColourTarget.b = Destination->b;
	ColourDelta.a = Speed * ( Destination->a > Colour.a ? 1 : -1 );
	ColourDelta.r = Speed * ( Destination->r > Colour.r ? 1 : -1 );
	ColourDelta.g = Speed * ( Destination->g > Colour.g ? 1 : -1 );
	ColourDelta.b = Speed * ( Destination->b > Colour.b ? 1 : -1 );
}

void VectorComponent::AnimateScaleTo( double Destination, double Speed )
{
	ScaleDelta = Speed * ( Destination > Scale ? 1 : -1 );
	ScaleTarget = Destination;
}

void VectorComponent::AnimateThicknessTo( int Thickness )
{
	ThicknessTarget = Thickness;
}

void VectorComponent::AnimateRotationTo( double Angle, double Speed )
{
	RotationContinual = false;
	RotationTarget = Angle;
	RotationDelta = Speed;
}

void VectorComponent::AnimateRotation( double Speed )
{
	RotationContinual = true;
	RotationTarget = 0.0;
	RotationDelta = Speed;
}




