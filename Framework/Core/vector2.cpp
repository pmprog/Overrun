
#include "vector2.h"
#include "../consts.h"

void RotateVector( Vector2* ToRotate, double AngleDegrees, Vector2* Output )
{
	RotateVector( ToRotate->X, ToRotate->Y, AngleDegrees, Output, 0, 0 );
}

void RotateVector( double ToRotateX, double ToRotateY, double AngleDegrees, Vector2* Output )
{
	RotateVector( ToRotateX, ToRotateY, AngleDegrees, Output, 0, 0 );
}

void RotateVector( Vector2* ToRotate, double AngleDegrees, Vector2* Output, double AddXOffset, double AddYOffset )
{
	RotateVector( ToRotate->X, ToRotate->Y, AngleDegrees, Output, AddXOffset, AddYOffset );
}

void RotateVector( double ToRotateX, double ToRotateY, double AngleDegrees, Vector2* Output, double AddXOffset, double AddYOffset )
{
	double rotSin = sin(AngleDegrees * (ALLEGRO_PI/180.0));
	double rotCos = cos(AngleDegrees * (ALLEGRO_PI/180.0));
	Output->X = (ToRotateX * rotCos) - (ToRotateY * rotSin) + AddXOffset;
	Output->Y = (ToRotateY * rotCos) + (ToRotateX * rotSin) + AddYOffset;
}

void MultiplyVector( Vector2* ToMultiply, double Value )
{
	ToMultiply->X *= Value;
	ToMultiply->Y *= Value;
}