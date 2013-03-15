
#include "boot.h"
#include "configure.h"
#include "mapdisp.h"
#include "spritedisp.h"

void BootUp::Begin()
{
	GuiStage::Begin();
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{

}

void BootUp::Finish()
{
	GuiStage::Finish();
}

void BootUp::Event(ALLEGRO_EVENT *e)
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
			}
			break;

		case ALLEGRO_EVENT_BUTTON_CLICK:
			if( e->user.data1 == (intptr_t)buttonQuit )
				delete GameStack->Pop();
			if( e->user.data1 == (intptr_t)buttonMapViewer )
				GameStack->Push( (Stage*)new MapDisp );
			if( e->user.data1 == (intptr_t)buttonSpriteViewer )
				GameStack->Push( (Stage*)new SpriteDisp );
			if( e->user.data1 == (intptr_t)buttonSaveSettings )
				CurrentConfiguration->SaveSettings();

			break;
	}
}

void BootUp::Update()
{
	GuiStage::Update();
	cursor->Update();
}

void BootUp::Render()
{
	al_clear_to_color( al_map_rgb( 48, 48, 48 ) );

	GuiStage::Render();

	cursor->Render();
}

void BootUp::InitialiseGui()
{
	cursor = new Mouse();
	cursor->AllowBoxing = true;

	panelMenu = new Panel();
	panelMenu->Position.X = CurrentConfiguration->ScreenWidth / 2 - 100;
	panelMenu->Position.Y = CurrentConfiguration->ScreenHeight / 2 - 200;
	panelMenu->Size.X = 200;
	panelMenu->Size.Y = 400;
	panelMenu->HasTitle = true;
	panelMenu->Title = "Overrun";
	panelMenu->FontSize = 24;
	panelMenu->Background = al_map_rgba( 128, 128, 255, 192 );
	panelMenu->Border = al_map_rgb( 192, 192, 255 );
	panelMenu->Foreground = al_map_rgb( 0, 0, 0 );
	panelMenu->CornerCut = 16;
	panelMenu->BorderWidth = 4;
	Controls.push_back( panelMenu );

	buttonMapViewer = new Button();
	buttonMapViewer->Position.X = CurrentConfiguration->ScreenWidth / 2 - 80;
	buttonMapViewer->Position.Y = CurrentConfiguration->ScreenHeight / 2 - 160;
	buttonMapViewer->Size.X = 160;
	buttonMapViewer->Size.Y = 32;
	buttonMapViewer->Text = "Map Viewer";
	buttonMapViewer->FontSize = 16;
	buttonMapViewer->BorderWidth = 2;
	buttonMapViewer->Background = al_map_rgb( 64, 64, 96 );
	buttonMapViewer->BorderHighlight = al_map_rgb( 192, 192, 255 );
	buttonMapViewer->BorderLowlight = al_map_rgb( 192, 192, 255 );
	buttonMapViewer->Foreground = al_map_rgb( 255, 255, 255 );
	Controls.push_back( buttonMapViewer );

	buttonSpriteViewer = new Button();
	buttonSpriteViewer->Position.X = CurrentConfiguration->ScreenWidth / 2 - 80;
	buttonSpriteViewer->Position.Y = CurrentConfiguration->ScreenHeight / 2 - 120;
	buttonSpriteViewer->Size.X = 160;
	buttonSpriteViewer->Size.Y = 32;
	buttonSpriteViewer->Text = "Sprite Viewer";
	buttonSpriteViewer->FontSize = 16;
	buttonSpriteViewer->BorderWidth = 2;
	buttonSpriteViewer->Background = al_map_rgb( 64, 64, 96 );
	buttonSpriteViewer->BorderHighlight = al_map_rgb( 192, 192, 255 );
	buttonSpriteViewer->BorderLowlight = al_map_rgb( 192, 192, 255 );
	buttonSpriteViewer->Foreground = al_map_rgb( 255, 255, 255 );
	Controls.push_back( buttonSpriteViewer );

	buttonGame = new Button();
	buttonGame->Position.X = CurrentConfiguration->ScreenWidth / 2 - 80;
	buttonGame->Position.Y = CurrentConfiguration->ScreenHeight / 2 - 80;
	buttonGame->Size.X = 160;
	buttonGame->Size.Y = 32;
	buttonGame->Text = "Play Wave";
	buttonGame->FontSize = 16;
	buttonGame->BorderWidth = 2;
	buttonGame->Background = al_map_rgb( 64, 64, 96 );
	buttonGame->BorderHighlight = al_map_rgb( 192, 192, 255 );
	buttonGame->BorderLowlight = al_map_rgb( 192, 192, 255 );
	buttonGame->Foreground = al_map_rgb( 255, 255, 255 );
	Controls.push_back( buttonGame );

	buttonSaveSettings = new Button();
	buttonSaveSettings->Position.X = CurrentConfiguration->ScreenWidth / 2 - 80;
	buttonSaveSettings->Position.Y = CurrentConfiguration->ScreenHeight / 2 + 120;
	buttonSaveSettings->Size.X = 160;
	buttonSaveSettings->Size.Y = 32;
	buttonSaveSettings->Text = "Save Settings";
	buttonSaveSettings->FontSize = 16;
	buttonSaveSettings->BorderWidth = 2;
	buttonSaveSettings->Background = al_map_rgb( 96, 64, 64 );
	buttonSaveSettings->BorderHighlight = al_map_rgb( 255, 192, 192 );
	buttonSaveSettings->BorderLowlight = al_map_rgb( 255, 192, 192 );
	buttonSaveSettings->Foreground = al_map_rgb( 255, 255, 255 );
	Controls.push_back( buttonSaveSettings );

	buttonQuit = new Button();
	buttonQuit->Position.X = CurrentConfiguration->ScreenWidth / 2 - 80;
	buttonQuit->Position.Y = CurrentConfiguration->ScreenHeight / 2 + 160;
	buttonQuit->Size.X = 160;
	buttonQuit->Size.Y = 32;
	buttonQuit->Text = "Quit";
	buttonQuit->FontSize = 16;
	buttonQuit->BorderWidth = 2;
	buttonQuit->Background = al_map_rgb( 96, 64, 64 );
	buttonQuit->BorderHighlight = al_map_rgb( 255, 192, 192 );
	buttonQuit->BorderLowlight = al_map_rgb( 255, 192, 192 );
	buttonQuit->Foreground = al_map_rgb( 255, 255, 255 );
	Controls.push_back( buttonQuit );

}

void BootUp::UninitialiseGui()
{
	Controls.remove( panelMenu );
	delete panelMenu;
	Controls.remove( buttonMapViewer );
	delete buttonMapViewer;
	Controls.remove( buttonSpriteViewer );
	delete buttonSpriteViewer;
	Controls.remove( buttonGame );
	delete buttonGame;
	Controls.remove( buttonSaveSettings );
	delete buttonSaveSettings;
	Controls.remove( buttonQuit );
	delete buttonQuit;
	delete cursor;
}
