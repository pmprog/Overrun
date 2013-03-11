
#pragma once

typedef struct Vector2
{
	int X;
	int Y;
} Vector2;

void RotateVector( Vector2* ToRotate, int AngleDegrees, Vector2* Output );
void RotateVector( int ToRotateX, int ToRotateY, int AngleDegrees, Vector2* Output );
void RotateVector( Vector2* ToRotate, int AngleDegrees, Vector2* Output, double AddXOffset, double AddYOffset );
void RotateVector( int ToRotateX, int ToRotateY, int AngleDegrees, Vector2* Output, double AddXOffset, double AddYOffset );