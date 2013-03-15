
#include "game.h"
#include "configure.h"
#include "Units/unit.h"

void Game::Begin()
{
	Cam = new Camera();
	CameraDrag = false;

	TileSize = min( CurrentConfiguration->ScreenWidth / 8, CurrentConfiguration->ScreenHeight / 8 );

	ConfigFile* MapConfig = new ConfigFile( "Resource/NaturePath.txt" );

	MapConfig->GetIntegerValue( "Width", &MapWidth );
	MapConfig->GetIntegerValue( "Height", &MapHeight );

	MapData = (uint8_t*)malloc( MapWidth * MapHeight * sizeof( uint8_t ) );
	for( int y = 0; y < MapHeight; y++ )
	{
		for( int x = 0; x < MapWidth; x++ )
		{
			int t;
			MapConfig->GetIntegerValue( "Map", (y * MapWidth) + x, &t );
			MapData[(y * MapWidth) + x] = (uint8_t)t;
		}
	}

	int pos;
	float zm;
	MapConfig->GetIntegerValue( "CameraPosX", &pos );
	Cam->Position.X = pos * TileSize;
	MapConfig->GetIntegerValue( "CameraPosY", &pos );
	Cam->Position.Y = pos * TileSize;
	MapConfig->GetFloatValue( "CameraZoom", &zm );
	Cam->Zoom = zm;
	
	delete MapConfig;

	Cam->RotateOrigin.X = (TileSize * MapWidth) / 2;
	Cam->RotateOrigin.Y = (TileSize * MapHeight) / 2;

	GuiStage::Begin();
}

void Game::Pause()
{
}

void Game::Resume()
{

}

void Game::Finish()
{
	free( MapData );
	GuiStage::Finish();
	delete Cam;
}

void Game::Event(ALLEGRO_EVENT *e)
{
	Vector2 v;

	if( e->type == ALLEGRO_EVENT_MOUSEEX_UP && CameraDrag )
		CameraDrag = false;

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
				case ALLEGRO_KEY_HOME:
					Cam->MoveTo( &Cam->RotateOrigin, 4.0 );
					break;
				case ALLEGRO_KEY_END:
					Cam->MoveTo( &Cam->RotateOrigin, 3.0 );
					break;
				case ALLEGRO_KEY_PGUP:
					v.X = 0; v.Y = 0;
					Cam->MoveTo( &v, 0.2 );
					break;
				case ALLEGRO_KEY_INSERT:
					Cam->RotateTo( Cam->Rotation + 20, 3.0 );
					break;
				case ALLEGRO_KEY_DELETE:
					Cam->RotateTo( Cam->Rotation - 20, 3.0 );
					break;
			}
			break;

		case ALLEGRO_EVENT_BUTTON_CLICK:
			if( e->user.data1 == (intptr_t)testButton )
				delete GameStack->Pop();
			break;

		case ALLEGRO_EVENT_MOUSEEX_DOWN:
			if( e->user.data4 > 1 )
			{
				cursor->CancelBoxing();
				CameraDrag = true;
			} else {

				Vector2 absPos;
				Cam->CameraOffsetToAbsolute( ((Vector2*)e->user.data2), &absPos );

				absPos.X++;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_UP:
			if( CameraDrag )
				CameraDrag = false;
			break;

		case ALLEGRO_EVENT_MOUSEEX_WHEEL:
			Cam->ZoomTo( max( 0.4, min( 4.0, Cam->Zoom + ( ((double)e->user.data4 * 2.0) / 10 ) ) ), 0.02 );
			break;

		case ALLEGRO_EVENT_MOUSEEX_MOVE:
			if( CameraDrag )
			{
				Vector2* d = (Vector2*)e->user.data3;
				d->X = Cam->Position.X - (d->X / Cam->Zoom);
				d->Y = Cam->Position.Y - (d->Y / Cam->Zoom);
				Cam->MoveTo( d, 1000.0 );
			}
			break;

	}
}

void Game::Update()
{
	Cam->Update();
	GuiStage::Update();
	cursor->Update();
}

void Game::Render()
{
	Vector2 pts[4];

	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	for( int y = 0; y < MapHeight; y++ )
	{
		for( int x = 0; x < MapWidth; x++ )
		{
			pts[0].X = x * TileSize;
			pts[1].X = x * TileSize;
			pts[2].X = (x + 1) * TileSize;
			pts[3].X = (x + 1) * TileSize;
			pts[0].Y = y * TileSize;
			pts[1].Y = (y + 1) * TileSize;
			pts[2].Y = y * TileSize;
			pts[3].Y = (y + 1) * TileSize;
			Cam->AbsoluteToCameraOffset( &pts[0], &pts[0] );
			Cam->AbsoluteToCameraOffset( &pts[1], &pts[1] );
			Cam->AbsoluteToCameraOffset( &pts[2], &pts[2] );
			Cam->AbsoluteToCameraOffset( &pts[3], &pts[3] );
			DrawGround( x, y, (Vector2*)&pts );
		}
	}

	GuiStage::Render();
	cursor->Render();
}

void Game::InitialiseGui()
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

	nextWave = new Panel();
	nextWave->Position.X = CurrentConfiguration->ScreenWidth - 224;
	nextWave->Position.Y = 4;
	nextWave->Size.X = 220;
	nextWave->Size.Y = 96;
	nextWave->Background = al_map_rgba( 64, 128, 64, 128 );
	nextWave->Border = al_map_rgb( 96, 192, 96 );
	nextWave->BorderWidth = 2;
	nextWave->Title = "Next Wave";
	nextWave->HasTitle = true;
	Controls.push_back( nextWave );
}

void Game::UninitialiseGui()
{
	Controls.remove( nextWave );
	delete nextWave;

	Controls.remove( testButton );
	delete testButton;

	delete cursor;
}


int Game::GetMapElement( int X, int Y )
{
	if( X < 0 || Y < 0 || X >= MapWidth || Y >= MapHeight )
		return -1;
	return MapData[(Y * MapWidth) + X];
}

void Game::DrawGround( int X, int Y, Vector2 BasePoints[] )
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
