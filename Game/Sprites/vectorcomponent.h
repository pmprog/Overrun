
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

	public:
		int ComponentType;
		ALLEGRO_COLOR DrawColour;
		int DrawThickness;
		double Rotation;
		double RotationPerFrame;

		VectorComponent( int Type, ALLEGRO_COLOR Colour, float* Verticies, int VertexCount );
		VectorComponent( int Type, ALLEGRO_COLOR Colour, std::list<Vector2*> Verticies );
		~VectorComponent();
		void Update();
		void Render( Vector2* Position, double ScreenRotation, double Zoom );
};