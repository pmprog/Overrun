
#include "vector2.h"
#include "../consts.h"

void RotateVector( Vector2* ToRotate, int AngleDegrees, Vector2* Output )
{
	RotateVector( ToRotate->X, ToRotate->Y, AngleDegrees, Output );
}

void RotateVector( int ToRotateX, int ToRotateY, int AngleDegrees, Vector2* Output )
{
	double rotSin = sin(AngleDegrees * (ALLEGRO_PI/180.0));
	double rotCos = cos(AngleDegrees * (ALLEGRO_PI/180.0));
	Output->X = (ToRotateX * rotCos) - (ToRotateY * rotSin);
	Output->Y = (ToRotateY * rotCos) + (ToRotateX * rotSin);
}