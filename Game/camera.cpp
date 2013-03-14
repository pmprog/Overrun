
#include "camera.h"

Camera::Camera()
{
	Position.X = 0;
	Position.Y = 0;
	RotateOrigin.X = 0;
	RotateOrigin.Y = 0;
	Rotation = 0.0;
	Zoom = 1.0;

	DestPosition.X = 0;
	DestPosition.Y = 0;
	DestSpeedPosition = 0.0;
	DestRotation = 0;
	DestSpeedRotation = 0.0;
	DestZoom = 1.0;
	DestSpeedZoom = 0.0;
}

void Camera::MoveTo( Vector2* Destination, double Speed )
{
	DestPosition.X = Destination->X;
	DestPosition.Y = Destination->Y;
	DestSpeedPosition = Speed;
}

void Camera::RotateTo( double Destination, double Speed )
{
	DestRotation = Destination;
	if( DestRotation < 0.0 )
		DestRotation += 360.0;
	if( DestRotation >= 360.0 )
		DestRotation -= 360.0;
	DestSpeedRotation = Speed;
}

void Camera::ZoomTo( double Destination, double Speed )
{
	DestZoom = Destination;
	DestSpeedZoom = Speed;
}

void Camera::AbsoluteToCameraOffset( Vector2* Absolute, Vector2* Out )
{
	// Camera Position is centre of the screen
	Vector2 Offset;

	// Rotate Position based on RotateOrigin
	Offset.X = Absolute->X - RotateOrigin.X;
	Offset.Y = Absolute->Y - RotateOrigin.Y;
	RotateVector( &Offset, Rotation, Out, RotateOrigin.X, RotateOrigin.Y );

	// Move camera on position
	Out->X -= Position.X;
	Out->Y -= Position.Y;

	// Zoom
	Out->X *= Zoom;
	Out->Y *= Zoom;

	// Centre on screen
	Out->X += CurrentConfiguration->ScreenWidth / 2;
	Out->Y += CurrentConfiguration->ScreenHeight / 2;
}

void Camera::CameraOffsetToAbsolute( Vector2* Offset, Vector2* Out )
{
	// Camera Position is centre of the screen
	Vector2 Temp;

	// Remove screen centre
	Temp.X = Offset->X - CurrentConfiguration->ScreenWidth / 2;
	Temp.Y = Offset->Y - CurrentConfiguration->ScreenHeight / 2;

	// UnZoom
	Temp.X /= Zoom;
	Temp.Y /= Zoom;

	// Move camera on position
	Temp.X += Position.X;
	Temp.Y += Position.Y;

	// UnRotate Position based on RotateOrigin
	Temp.X -= RotateOrigin.X;
	Temp.Y -= RotateOrigin.Y;
	RotateVector( &Temp, -Rotation, Out, RotateOrigin.X, RotateOrigin.Y );
}

void Camera::Update()
{
	double TravelDistance;

	// Update Camera Position
	if( DestPosition.X != Position.X )
	{
		TravelDistance = max( -DestSpeedPosition, min( DestSpeedPosition, DestPosition.X - Position.X ) );
		Position.X += TravelDistance;
	}
	if( DestPosition.Y != Position.Y )
	{
		TravelDistance = max( -DestSpeedPosition, min( DestSpeedPosition, DestPosition.Y - Position.Y ) );
		Position.Y += TravelDistance;
	}

	// Update Camera Rotation
	if( DestRotation != Rotation )
	{
		TravelDistance = DestRotation - Rotation;
		if( Rotation < DestRotation )
		{
			if( abs( (DestRotation-360) - Rotation ) < abs(TravelDistance) )
				TravelDistance = (DestRotation-360) - Rotation;
		} else {
			if( abs( DestRotation - Rotation + 360 ) < abs(TravelDistance) )
				TravelDistance = DestRotation - Rotation + 360;
		}
		TravelDistance = max( -DestSpeedRotation, min( DestSpeedRotation, TravelDistance ) );
		Rotation += TravelDistance;
		if( Rotation < 0.0 )
			Rotation += 360.0;
		if( Rotation >= 360.0 )
			Rotation -= 360.0;
	}

	// Update Camera Zoom
	if( DestZoom != Zoom )
	{
		// TODO: Fix zoom scaling
		TravelDistance = max( -DestSpeedZoom, min( DestSpeedZoom, DestZoom - Zoom ) );
		Zoom += TravelDistance;
	}
}
