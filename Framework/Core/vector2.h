
#pragma once

typedef struct Vector2
{
	float X;
	float Y;
} Vector2;

void RotateVector( Vector2* ToRotate, double AngleDegrees, Vector2* Output );
void RotateVector( double ToRotateX, double ToRotateY, double AngleDegrees, Vector2* Output );
void RotateVector( Vector2* ToRotate, double AngleDegrees, Vector2* Output, double AddXOffset, double AddYOffset );
void RotateVector( double ToRotateX, double ToRotateY, double AngleDegrees, Vector2* Output, double AddXOffset, double AddYOffset );