
#include "game.h"
#include "configure.h"
#include "Game/unit.h"
#include "Structures/buildings.h"
#include "results.h"

Game::~Game()
{
	// Due to the way I'm passing this to results, I can't use Game::Finish() to close off the GuiStage
	GuiStage::Finish();
}

void Game::Begin()
{
	GuiStage::Begin();

	ConfigFile* MapConfig = new ConfigFile( "Resource/NaturePath.txt" );

	// Load Map Data
	Level = new Map( this, MapConfig );

	Vector2 camStart;
	float camZoom;
	MapConfig->GetFloatValue( "CameraPosX", &camStart.X );
	MapConfig->GetFloatValue( "CameraPosY", &camStart.Y );
	MapConfig->GetFloatValue( "CameraZoom", &camZoom );
	MultiplyVector( &camStart, view->PixelsPerUnit );
	view->MoveTo( &camStart, 32.0 );
	view->ZoomTo( (double)camZoom, 0.04 );
	view->RotateOrigin.X = (double)Level->MapWidth / 2.0;
	view->RotateOrigin.Y = (double)Level->MapHeight / 2.0;
	view->SetCameraMinBounds( 0, 0 );
	view->SetCameraMaxBounds( Level->MapWidth * view->PixelsPerUnit, Level->MapHeight * view->PixelsPerUnit );
	MultiplyVector( &view->RotateOrigin, view->PixelsPerUnit );

	// Load Wave Data
	int WaveCount;
	WaveCount = MapConfig->GetArraySize( "Waves" );
	for( int wc = 1; wc <= WaveCount; wc++ )
	{
		char wavePath[255];
		std::string waveName;

		MapConfig->GetStringValue( "Waves", wc - 1, &waveName );
		sprintf( (char*)&wavePath, "Resource/%s.txt", waveName.c_str() );

		ConfigFile* waveCfg = new ConfigFile( (char*)&wavePath );
		Waves.push_back( new Wave( waveCfg ) );
		delete waveCfg;
	}

	overlayNextWaveUnit = 0;

	timerSpawn = 0;
	timerDelay = al_create_timer( 1.0 );
	al_register_event_source( EventQueue, al_get_timer_event_source( timerDelay ) );
	al_start_timer( timerDelay );

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
	// GuiStage::Finish();	// Dealt with in the destructor
}

void Game::Event(ALLEGRO_EVENT *e)
{
	char buffer[128];
	Wave* w;

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
				case ALLEGRO_KEY_Q:
					view->RotateTo( view->GetRotationDestination() - 15, 1 );
					break;
				case ALLEGRO_KEY_E:
					view->RotateTo( view->GetRotationDestination() + 15, 1 );
					break;
				case ALLEGRO_KEY_W:
					view->RotateTo( 0, 1 );
					break;
			}
			break;

		case ALLEGRO_EVENT_TIMER:
			w = Waves.front();

			if( e->timer.source == timerDelay )
			{
				if( overlayNextWaveUnit == 0 )
				{
					overlayNextWaveUnit = w->SpawnUnit( 0 );
					overlayNextWaveUnit->AbsolutePosition.X = 12 + (overlay->PixelsPerUnit / 2);
					overlayNextWaveUnit->AbsolutePosition.Y = 32 + (overlay->PixelsPerUnit / 2);
					sprintf((char*)&buffer, "%s x%d", w->UnitClass.c_str(), w->UnitCount );
					overlayNextWaveClass->Text = std::string(buffer);
					sprintf((char*)&buffer, "Health: %d", (int)overlayNextWaveUnit->GetCurrentHealth() );
					overlayNextWaveHealth->Text = std::string(buffer);
					sprintf((char*)&buffer, "Shield: %d", (int)overlayNextWaveUnit->GetCurrentShields() );
					overlayNextWaveShield->Text = std::string(buffer);
					// TODO: Position on screen
				}

				w->WaveDelay--;
				sprintf((char*)&buffer, "Spawn: %d sec", w->WaveDelay );
				overlayNextWaveTime->Text = std::string(buffer);
				if( w->WaveDelay == 0 )
				{
					overlayNextWaveTime->Text = "";
					al_stop_timer( timerDelay );
					timerSpawn = al_create_timer( w->SpawnDelay );
					al_register_event_source( EventQueue, al_get_timer_event_source( timerSpawn ) );
					al_start_timer( timerSpawn );
				}

			} else if( e->timer.source == timerSpawn ) {

				for( unsigned int p = 0; p < Level->Paths.size(); p++ )
				{
					if( w->UnitCount == 0 )
						break;
					Level->Units.push_back( Waves.front()->SpawnUnit( Level->Paths.at( p ) ) );
					w->UnitCount--;
				}

				if( w->UnitCount == 0 )
				{
					al_stop_timer( timerSpawn );
					al_unregister_event_source( EventQueue, al_get_timer_event_source( timerSpawn ) );
					al_destroy_timer( timerSpawn );
					Waves.pop_front();
					delete w;
					delete overlayNextWaveUnit;
					overlayNextWaveUnit = 0;

					if( Waves.size() > 0 )
						al_start_timer( timerDelay );
				}

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

		case ALLEGRO_EVENT_BUTTON_CLICK:
			if( e->user.data1 == (intptr_t)overlayNextWaveShowHide )
			{
				if( overlayNextWaveShowHideTargetHeight == ((overlayNextWavePanel->FontSize * 5) + (overlayNextWavePanel->BorderWidth * 2) + 6) )
				{
					overlayNextWaveShowHideTargetHeight = (overlayNextWavePanel->BorderWidth * 3) + overlayNextWavePanel->FontSize;
				} else {
					overlayNextWaveShowHideTargetHeight = (overlayNextWavePanel->FontSize * 5) + (overlayNextWavePanel->BorderWidth * 2) + 6;
				}
			}
			break;
	}
}

void Game::Update()
{
	Level->Update();


	GuiStage::Update();

	NextWaveUpdate();

	CheckEndOfGameConditions();

	cursor->Update();
	view->Update();
}

void Game::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	Level->Render( view );

	GuiStage::Render();


	Vector2 cBR;
	overlayNextWavePanel->GetClientArea( 0, &cBR );
	if( overlayNextWaveUnit != 0 && cBR.Y > overlayNextWaveUnit->AbsolutePosition.Y + (overlay->PixelsPerUnit / 2) )
		overlayNextWaveUnit->Render( overlay );

	cursor->Render();
}

void Game::InitialiseGui()
{
	view = new Camera();
	overlay = new Camera();
	overlay->OverlayMode = true;
	overlay->PixelsPerUnit = 32;

	TileSize = view->PixelsPerUnit;
	viewDrag = false;

	NextWaveInitGui();

	cursor = new Mouse();
	cursor->AllowBoxing = true;
}

void Game::UninitialiseGui()
{
	delete cursor;
	delete view;
	delete overlay;
}

void Game::NextWaveInitGui()
{
	overlayNextWavePanel = new Panel();
	overlayNextWavePanel->Position.X = 4;
	overlayNextWavePanel->Position.Y = 4;
	overlayNextWavePanel->Size.X = 240;
	overlayNextWavePanel->Size.Y = (overlayNextWavePanel->FontSize * 5) + (overlayNextWavePanel->BorderWidth * 2) + 6;
	overlayNextWavePanel->Title = "   Next Wave";
	overlayNextWavePanel->HasTitle = true;
	overlayNextWavePanel->Border = al_map_rgb( 192, 255, 192 );
	overlayNextWavePanel->Background = al_map_rgba( 48, 64, 48, 96 );
	overlayNextWavePanel->Foreground = al_map_rgb( 0, 0, 0 );
	Controls.push_back( overlayNextWavePanel );

	overlayNextWaveClass = new Label();
	overlayNextWaveClass->Background.a = 0;
	overlayNextWaveClass->Position.X = 12 + (overlayNextWavePanel->BorderWidth * 2) + overlay->PixelsPerUnit;
	overlayNextWaveClass->Position.Y = overlayNextWavePanel->FontSize + (overlayNextWavePanel->BorderWidth * 2) + 12;
	overlayNextWaveClass->Text = "";
	Controls.push_back( overlayNextWaveClass );

	overlayNextWaveHealth = new Label();
	overlayNextWaveHealth->Background.a = 0;
	overlayNextWaveHealth->Position.X = 12 + (overlayNextWavePanel->BorderWidth * 2) + overlay->PixelsPerUnit;
	overlayNextWaveHealth->Position.Y = (overlayNextWavePanel->FontSize * 2) + (overlayNextWavePanel->BorderWidth * 2) + 12;
	overlayNextWaveHealth->Text = "";
	Controls.push_back( overlayNextWaveHealth );

	overlayNextWaveShield = new Label();
	overlayNextWaveShield->Background.a = 0;
	overlayNextWaveShield->Position.X = 12 + (overlayNextWavePanel->BorderWidth * 2) + overlay->PixelsPerUnit;
	overlayNextWaveShield->Position.Y = (overlayNextWavePanel->FontSize * 3) + (overlayNextWavePanel->BorderWidth * 2) + 12;
	overlayNextWaveShield->Text = "";
	Controls.push_back( overlayNextWaveShield );

	overlayNextWaveTime = new Label();
	overlayNextWaveTime->Background.a = 0;
	overlayNextWaveTime->Position.X = 12 + (overlayNextWavePanel->BorderWidth * 2) + overlay->PixelsPerUnit;
	overlayNextWaveTime->Position.Y = (overlayNextWavePanel->FontSize * 4) + (overlayNextWavePanel->BorderWidth * 2) + 12 ;
	overlayNextWaveTime->Text = "";
	Controls.push_back( overlayNextWaveTime );

	overlayNextWaveShowHide = new Button();
	overlayNextWaveShowHide->Background = al_map_rgb( 192, 255, 192 );
	overlayNextWaveShowHide->Foreground = al_map_rgb( 0, 0, 0 );
	overlayNextWaveShowHide->BorderHighlight = al_map_rgb( 0, 0, 0 );
	overlayNextWaveShowHide->BorderLowlight = al_map_rgb( 0, 0, 0 );
	overlayNextWaveShowHide->FontName = "Resource/unicons.ttf";
	overlayNextWaveShowHide->FontSize = 18;
	overlayNextWaveShowHide->Text = "f";
	overlayNextWaveShowHide->Position.X = 6;
	overlayNextWaveShowHide->Position.Y = 6;
	overlayNextWaveShowHide->Size.X = 16;
	overlayNextWaveShowHide->Size.Y = 16;
	Controls.push_back( overlayNextWaveShowHide );

	overlayNextWaveShowHideTargetHeight = overlayNextWavePanel->Size.Y;
}

void Game::NextWaveUpdate()
{
	Vector2 cBR;
	overlayNextWavePanel->GetClientArea( 0, &cBR );

	// Hide/Show next wave window
	if( overlayNextWaveShowHideTargetHeight != overlayNextWavePanel->Size.Y )
		overlayNextWavePanel->Size.Y += (overlayNextWaveShowHideTargetHeight > overlayNextWavePanel->Size.Y ? 1 : -1);
	if( overlayNextWaveUnit != 0 )
		overlayNextWaveUnit->Update();

	if( cBR.Y < overlayNextWaveTime->Position.Y + overlayNextWaveTime->Size.Y )
		overlayNextWaveTime->Visible = false;
	else
		overlayNextWaveTime->Visible = true;
	if( cBR.Y < overlayNextWaveShield->Position.Y + overlayNextWaveShield->Size.Y )
		overlayNextWaveShield->Visible = false;
	else
		overlayNextWaveShield->Visible = true;
	if( cBR.Y < overlayNextWaveHealth->Position.Y + overlayNextWaveHealth->Size.Y )
		overlayNextWaveHealth->Visible = false;
	else
		overlayNextWaveHealth->Visible = true;
	if( cBR.Y < overlayNextWaveClass->Position.Y + overlayNextWaveClass->Size.Y )
		overlayNextWaveClass->Visible = false;
	else
		overlayNextWaveClass->Visible = true;

}

void Game::CheckEndOfGameConditions()
{
	Results* resultsStage;

	for(std::vector<Building*>::iterator i = Level->Buildings.begin(); i != Level->Buildings.end(); i++ )
	{
		Building* b = (Building*)(*i);
		Base* plyBase = dynamic_cast<Base*>(b);
		if( plyBase != 0 )
		{
			// TODO: If we want to support multiple bases later on, we'll need to change this condition
			if( plyBase->GetCurrentShields() <= 0.0 && plyBase->GetCurrentHealth() <= 0.0 )
			{
				resultsStage = new Results( (Game*)GameStack->Pop(), false );	// Send player to the results screen for this game, and pop it out of the stack
				cursor->Position.X = -20;
				GameStack->Push( (Stage*)resultsStage );
				return;
			}
			break;
		}
	}
}