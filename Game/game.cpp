
#include "game.h"
#include "configure.h"
#include "Units/unit.h"

void Game::Begin()
{
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
	GuiStage::Finish();
}

void Game::Event(ALLEGRO_EVENT *e)
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
			if( e->user.data1 == (intptr_t)testButton )
				delete GameStack->Pop();
			break;
	}
}

void Game::Update()
{
	GuiStage::Update();
	cursor->Update();
}

void Game::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	GuiStage::Render();
	cursor->Render();
}

void Game::InitialiseGui()
{
	view = new Camera();

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

void Game::UninitialiseGui()
{
	Controls.remove( testButton );
	delete testButton;

	delete cursor;
	delete view;
}
