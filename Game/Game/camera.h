
#pragma once

#include "../../Framework/Core/main.h"
#include "../configure.h"

class Camera
{
	private:
		Vector2 DestPosition;
		double  DestSpeedPosition;
		double  DestRotation;
		double  DestSpeedRotation;
		double  DestZoom;
		double  DestSpeedZoom;

		bool HasMinPos;
		Vector2 MinimumPosition;
		bool HasMaxPos;
		Vector2 MaximumPosition;

	public:
		Vector2 Position;
		Vector2 RotateOrigin;
		double  Rotation;
		double  Zoom;
		double	PixelsPerUnit;
		bool		OverlayMode;


		Camera();
		void MoveTo( Vector2* Destination, double Speed );
		void RotateTo( double Destination, double Speed );
		void ZoomTo( double Destination, double Speed );

		void AbsoluteToCameraOffset( Vector2* Absolute, Vector2* Out );
		void CameraOffsetToAbsolute( Vector2* Offset, Vector2* Out );

		void SetCameraBounds( Vector2* MinRange, Vector2* MaxRange );
		void SetCameraMinBounds( Vector2* MinRange );
		void SetCameraMinBounds( int X, int Y );
		void SetCameraMaxBounds( Vector2* MaxRange );
		void SetCameraMaxBounds( int X, int Y );

		double GetRotationDestination();

		void Update();
};