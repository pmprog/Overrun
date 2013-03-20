
#pragma once

#include "../../Framework/Core/main.h"

#define VECTORSPRITE_COMPONENT_POLYLINE					0
#define VECTORSPRITE_COMPONENT_CIRCLE						1
#define VECTORSPRITE_COMPONENT_POLYGON					2
#define VECTORSPRITE_COMPONENT_CIRCLE_FILLED		3
#define VECTORSPRITE_COMPONENT_POLYGON_FILLED		4

class VectorComponent
{
	private:
		int PointCount;
		float* Points;

		ALLEGRO_COLOR ColourTarget;
		ALLEGRO_COLOR ColourDelta;

		double ScaleTarget;
		double ScaleDelta;

		int ThicknessTarget;

		bool RotationContinual;
		double RotationTarget;
		double RotationDelta;

		void InitDefaults();

	public:
		int ComponentType;
		ALLEGRO_COLOR Colour;
		int LineThickness;
		double Rotation;
		double Scale;

		VectorComponent( int Type, ALLEGRO_COLOR Colour, float* Verticies, int VertexCount );
		VectorComponent( int Type, ALLEGRO_COLOR Colour, std::list<Vector2*> Verticies );
		~VectorComponent();
		void Update();
		void Render( Vector2* Position, double ScreenRotation, double Zoom );

		void AnimateColourTo( ALLEGRO_COLOR* Destination, double Speed );
		void AnimateScaleTo( double Destination, double Speed );
		void AnimateThicknessTo( int Thickness );
		void AnimateRotationTo( double Angle, double Speed );
		void AnimateRotation( double Speed );

		float GetPoint( int PointIndex, bool WantYPosition );
		void SetPoint( int PointIndex, bool WantYPosition, float NewValue );
};