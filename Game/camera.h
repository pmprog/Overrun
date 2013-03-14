
#pragma once

#include "../Framework/Core/main.h"
#include "configure.h"

class Camera
{
	private:
		Vector2 DestPosition;
		double  DestSpeedPosition;
		double  DestRotation;
		double  DestSpeedRotation;
		double  DestZoom;
		double  DestSpeedZoom;

	public:
		Vector2 Position;
		Vector2 RotateOrigin;
		double  Rotation;
		double  Zoom;

		Camera();
		void MoveTo( Vector2* Destination, double Speed );
		void RotateTo( double Destination, double Speed );
		void ZoomTo( double Destination, double Speed );
		void AbsoluteToCameraOffset( Vector2* Absolute, Vector2* Out );
		void Update();
};