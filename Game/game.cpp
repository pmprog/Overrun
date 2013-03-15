
#include "game.h"
#include "configure.h"
#include "Game/unit.h"

void Game::Begin()
{
	GuiStage::Begin();

	ConfigFile* MapConfig = new ConfigFile( "Resource/NaturePath.txt" );

	// Load Map Data
	Level = new Map( this, MapConfig );

	Vector2 camStart;
	float camZoom;
	MapConfig->GetIntegerValue( "CameraPosX", &camStart.X );
	MapConfig->GetIntegerValue( "CameraPosY", &camStart.Y );
	MapConfig->GetFloatValue( "CameraZoom", &camZoom );
	camStart.X *= view->PixelsPerUnit;
	camStart.Y *= view->PixelsPerUnit;
	view->MoveTo( &camStart, 12.0 );
	view->ZoomTo( (double)camZoom, 0.04 );


	// Load Wave Data
	int WaveCount;
	WaveCount = MapConfig->GetArraySize( "WaveTypes" );
	for( int wc = 1; wc <= WaveCount; wc++ )
	{
		Waves.push_back( new Wave( this, MapConfig, wc - 1 ) );
	}

	delete MapConfig;
}

void Game::Pause()
{
}

void Game::Resume()
{

}

void Game::Finish()
{
	GuiStage::Finish();
}

void Game::Event(ALLEGRO_EVENT *e)
{
	if( e->type == ALLEGRO_EVENT_MOUSEEX_UP && viewDrag )
		viewDrag = false;

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
			}
			break;

		case ALLEGRO_EVENT_MOUSEEX_DOWN:
			if( e->user.data4 > 1 )
			{
				cursor->CancelBoxing();
				viewDrag = true;
			} else {

				Vector2 absPos;
				view->CameraOffsetToAbsolute( ((Vector2*)e->user.data2), &absPos );

				absPos.X++;
			}
			break;
		case ALLEGRO_EVENT_MOUSEEX_UP:
			if( viewDrag )
				viewDrag = false;
			break;

		case ALLEGRO_EVENT_MOUSEEX_WHEEL:
			view->ZoomTo( max( 0.4, min( 4.0, view->Zoom + ( ((double)e->user.data4 * 2.0) / 10 ) ) ), 0.02 );
			break;

		case ALLEGRO_EVENT_MOUSEEX_MOVE:
			if( viewDrag )
			{
				Vector2* d = (Vector2*)e->user.data3;
				d->X = view->Position.X - (d->X / view->Zoom);
				d->Y = view->Position.Y - (d->Y / view->Zoom);
				view->MoveTo( d, 1000.0 );
			}
			break;
	}
}

void Game::Update()
{
	GuiStage::Update();
	cursor->Update();
	view->Update();
}

void Game::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	Level->Render( view );

	GuiStage::Render();
	cursor->Render();
}

void Game::InitialiseGui()
{
	view = new Camera();
	viewDrag = false;

	cursor = new Mouse();
	cursor->AllowBoxing = true;
}

void Game::UninitialiseGui()
{
	delete cursor;
	delete view;
}
