
#include "mapdisp.h"
#include "configure.h"

void MapDisp::Begin()
{
	CameraPosition.X = 0;
	CameraPosition.Y = 0;
	CameraPositionDestination.X = 0;
	CameraPositionDestination.Y = 0;
	CameraZoom = 1.0;
	CameraZoomDestination = 1.0;
	CameraRotation = 0.0;
	CameraRotationDestination = 0.0;

	MapWidth = 15;
	MapHeight = 16;

	MapData = (uint8_t*)malloc( MapWidth * MapHeight * sizeof( uint8_t ) );

	uint8_t sourceMapData[16][15] = {
		0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2,
		0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 2,
		0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0,
		0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0,
		0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 0, 0,
		0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 0, 0,
		0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	memcpy( (void*)MapData, (void*)&sourceMapData, MapWidth * MapHeight * sizeof( uint8_t ) );

	GuiStage::Begin();

	frameIndex = 0;
}

void MapDisp::Pause()
{
}

void MapDisp::Resume()
{

}

void MapDisp::Finish()
{
	free( MapData );
	GuiStage::Finish();
}

void MapDisp::Event(ALLEGRO_EVENT *e)
{
	GuiStage::Event( e );
	if( e->any.timestamp == -1 )
		return;

	switch( e->type )
	{
		case ALLEGRO_EVENT_KEY_DOWN:
			switch( e->keyboard.keycode )
			{
				case ALLEGRO_KEY_ESCAPE:
					GameStack->Pop();
					break;
				case ALLEGRO_KEY_UP:
					//CameraPosition.X -= sin( CameraRotation ) / CameraZoom;
					CameraPositionDestination.Y += 10; // cos( CameraRotation ) / CameraZoom;
					break;
				case ALLEGRO_KEY_DOWN:
					//CameraPosition.X += sin( CameraRotation ) / CameraZoom;
					CameraPositionDestination.Y -= 10; // cos( CameraRotation ) / CameraZoom;
					break;
				case ALLEGRO_KEY_LEFT:
					CameraPositionDestination.X += 10; // cos( CameraRotation ) / CameraZoom;
					//CameraPosition.Y -= sin( CameraRotation ) / CameraZoom;
					break;
				case ALLEGRO_KEY_RIGHT:
					CameraPositionDestination.X -= 10;
					//CameraPosition.Y = sin( CameraRotation ) / CameraZoom;
					break;
				case ALLEGRO_KEY_A:
					if( CameraZoomDestination < 4.9 )
						CameraZoomDestination += 0.1;
					break;
				case ALLEGRO_KEY_Z:
					if( CameraZoomDestination > 0.3 )
						CameraZoomDestination -= 0.1;
					break;
				case ALLEGRO_KEY_S:
					CameraRotationDestination += 10.0;
					//if( CameraRotation > 360.0 )
					//	CameraRotation -= 360.0;
					break;
				case ALLEGRO_KEY_X:
					CameraRotationDestination -= 10.0;
					//if( CameraRotation < 0.0 )
					//	CameraRotation += 360.0;
					break;
			}
			break;

		case ALLEGRO_EVENT_BUTTON_CLICK:
			if( e->user.data1 == (intptr_t)testButton )
				delete GameStack->Pop();
			break;

		case ALLEGRO_EVENT_MOUSEEX_WHEEL:
			CameraZoomDestination += (double)e->user.data4 / 10;
			if( CameraZoomDestination > 5.0 )
				CameraZoomDestination = 5.0;
			if( CameraZoomDestination < 0.01 )
				CameraZoomDestination = 0.01;
			break;
	}
}

void MapDisp::Update()
{
	frameIndex++;
	switch( frameIndex )
	{
		case 1:
			CameraPositionDestination.X = -CurrentConfiguration->ScreenWidth / 2;
			CameraPositionDestination.Y = CurrentConfiguration->ScreenHeight / 2;
			CameraZoomDestination = 0.1;
			break;
		case 90:
			CameraPositionDestination.Y = -CurrentConfiguration->ScreenHeight / 4;
			CameraRotationDestination = 90;
			break;
		case 120:
			CameraZoomDestination = 0.7;
			break;
		case 250:
			CameraPositionDestination.X = CurrentConfiguration->ScreenWidth / 2;
			CameraPositionDestination.Y = 0;
			CameraRotationDestination = 220;
			CameraZoomDestination = 2.0;
			break;
		case 340:
			CameraZoomDestination = 0.7;
			break;
		case 500:
			CameraPositionDestination.X = 0;
			CameraPositionDestination.Y = 0;
			CameraRotationDestination = 360;
			CameraZoomDestination = 1.0;
			break;
	}


	int camTravel;
	if( CameraPositionDestination.X != CameraPosition.X )
	{
		camTravel = CameraPositionDestination.X - CameraPosition.X;
		if( camTravel < -2 )
			camTravel = -2;
		if( camTravel > 2 )
			camTravel = 2;
		CameraPosition.X += camTravel;
	}
	if( CameraPositionDestination.Y != CameraPosition.Y )
	{
		camTravel = CameraPositionDestination.Y - CameraPosition.Y;
		if( camTravel < -2 )
			camTravel = -2;
		if( camTravel > 2 )
			camTravel = 2;
		CameraPosition.Y += camTravel;
	}
	if( CameraZoomDestination != CameraZoom )
	{
		double zomDist = CameraZoomDestination - CameraZoom;
		if( zomDist < -0.01 )
			zomDist = -0.01;
		if( zomDist > 0.01 )
			zomDist = 0.01;
		CameraZoom += zomDist;
	}
	if( CameraRotationDestination != CameraRotation )
	{
		double rotDist = CameraRotationDestination - CameraRotation;
		if( rotDist < -1.0 )
			rotDist = -1.0;
		if( rotDist > 1.0 )
			rotDist = 1.0;
		CameraRotation += rotDist;
	} else {
		if( CameraRotation < 0 )
		{
			CameraRotation += 360.0;
			CameraRotationDestination += 360.0;
		}
		if( CameraRotation > 360.0 )
		{
			CameraRotation -= 360.0;
			CameraRotationDestination -= 360.0;
		}
	}
	GuiStage::Update();
	cursor->Update();
}

void MapDisp::Render()
{
	Vector2 pts[4];

	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	int RotOffX = (MapWidth * TILE_SIZE * CameraZoom) / 2;
	int RotOffY = (MapHeight * TILE_SIZE * CameraZoom) / 2;

	for( int y = 0; y < MapHeight; y++ )
	{
		int tYu = (y * TILE_SIZE * CameraZoom) - RotOffY;
		int tYl = ((y+1) * TILE_SIZE * CameraZoom) - RotOffY;
		for( int x = 0; x < MapWidth; x++ )
		{
			int tXu = (x * TILE_SIZE * CameraZoom) - RotOffX;
			int tXl = ((x+1) * TILE_SIZE * CameraZoom) - RotOffX;
			double rotSin = sin(CameraRotation * (ALLEGRO_PI/180.0));
			double rotCos = cos(CameraRotation * (ALLEGRO_PI/180.0));

			RotateVector( tXu, tYu, CameraRotation, &pts[0], (CurrentConfiguration->ScreenWidth / 2) + (CameraPosition.X * CameraZoom), (CurrentConfiguration->ScreenHeight / 2) + (CameraPosition.Y * CameraZoom) );
			RotateVector( tXu, tYl, CameraRotation, &pts[1], (CurrentConfiguration->ScreenWidth / 2) + (CameraPosition.X * CameraZoom), (CurrentConfiguration->ScreenHeight / 2) + (CameraPosition.Y * CameraZoom) );
			RotateVector( tXl, tYu, CameraRotation, &pts[2], (CurrentConfiguration->ScreenWidth / 2) + (CameraPosition.X * CameraZoom), (CurrentConfiguration->ScreenHeight / 2) + (CameraPosition.Y * CameraZoom) );
			RotateVector( tXl, tYl, CameraRotation, &pts[3], (CurrentConfiguration->ScreenWidth / 2) + (CameraPosition.X * CameraZoom), (CurrentConfiguration->ScreenHeight / 2) + (CameraPosition.Y * CameraZoom) );

			DrawGround( x, y, (Vector2*)&pts );
		}
	}


	GuiStage::Render();
	cursor->Render();
}

void MapDisp::InitialiseGui()
{
	cursor = new Mouse();
	cursor->AllowBoxing = true;

	testButton = new Button();
	testButton->Position.X = 4;
	testButton->Position.Y = 4;
	testButton->Size.X = 200;
	testButton->Size.Y = 32;
	testButton->Text = "Quit";
	testButton->FontSize = 16;
	testButton->BorderWidth = 2;
	Controls.push_back( testButton );
}

void MapDisp::UninitialiseGui()
{
	Controls.remove( testButton );
	delete testButton;

	delete cursor;
}


int MapDisp::GetMapElement( int X, int Y )
{
	if( X < 0 || Y < 0 || X >= MapWidth || Y >= MapHeight )
		return -1;
	return MapData[(Y * MapWidth) + X];
}

void MapDisp::DrawGround( int X, int Y, Vector2 BasePoints[] )
{

	float polyverts[8] = {
		BasePoints[2].X, BasePoints[2].Y,
		BasePoints[0].X, BasePoints[0].Y,
		BasePoints[1].X, BasePoints[1].Y,
		BasePoints[3].X, BasePoints[3].Y
	};

	switch( MapData[(Y * MapWidth) + X] )
	{
		case 0:	// buildable
			al_draw_filled_polygon( (float*)&polyverts, 4, al_map_rgb( 64, 128, 64 ) );
			break;
		case 1:
			al_draw_filled_polygon( (float*)&polyverts, 4, al_map_rgb( 64, 64, 64 ) );
			break;
		case 2:
			al_draw_filled_polygon( (float*)&polyverts, 4, al_map_rgb( 64, 64, 128 ) );
			break;
	}

	al_draw_line( BasePoints[0].X, BasePoints[0].Y, BasePoints[1].X, BasePoints[1].Y, al_map_rgb(128,128,128), 1 );
	al_draw_line( BasePoints[0].X, BasePoints[0].Y, BasePoints[2].X, BasePoints[2].Y, al_map_rgb(128,128,128), 1 );
	al_draw_line( BasePoints[3].X, BasePoints[3].Y, BasePoints[1].X, BasePoints[1].Y, al_map_rgb(128,128,128), 1 );
	al_draw_line( BasePoints[2].X, BasePoints[2].Y, BasePoints[3].X, BasePoints[3].Y, al_map_rgb(128,128,128), 1 );

}
