
#include "results.h"
#include "configure.h"
#include "game.h"

Results::Results( Game* curGame, bool Victory )
{
	gameStage = curGame;
	backgroundAlpha = 0;
	wasVictory = Victory;
}

Results::~Results()
{
	delete gameStage;
}

void Results::Begin()
{
	GuiStage::Begin();
}

void Results::Pause()
{
}

void Results::Resume()
{

}

void Results::Finish()
{
	GuiStage::Finish();
}

void Results::Event(ALLEGRO_EVENT *e)
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
					delete GameStack->Pop();
					break;
			}
			break;

	}
}

void Results::Update()
{
	if( backgroundAlpha < 192 )
	{
		gameStage->Level->Update();
		backgroundAlpha += 4;
	} else {
		if( labelResult->Background.a < 1.0 )
		{
			gameStage->Level->Update();
			labelResult->Background.a += 0.04;
			if( labelResult->Background.a > 1.0 )
				labelResult->Background.a = 1.0;
			labelResult->Foreground.a = labelResult->Background.a;
			buttonQuit->Background.a = labelResult->Background.a;
			buttonQuit->Foreground.a = labelResult->Background.a;
			buttonQuit->BorderHighlight.a = labelResult->Background.a;
			buttonQuit->BorderLowlight.a = labelResult->Background.a;
		}
	}

	GuiStage::Update();
	cursor->Update();
}

void Results::Render()
{
	gameStage->Render();
	al_draw_filled_rectangle( 0, 0, CurrentConfiguration->ScreenWidth, CurrentConfiguration->ScreenHeight, al_map_rgba( 0, 0, 0, backgroundAlpha ) );

	GuiStage::Render();
	cursor->Render();
}

void Results::InitialiseGui()
{
	cursor = new Mouse();

	labelResult = new Label();
	labelResult->TextAlignment = ALLEGRO_ALIGN_CENTRE;
	labelResult->Text = (wasVictory ? "Victory" : "Defeat" );
	labelResult->Position.X = 0;
	labelResult->Position.Y = CurrentConfiguration->ScreenHeight / 4;
	labelResult->Size.X = CurrentConfiguration->ScreenWidth;
	labelResult->Size.Y = CurrentConfiguration->ScreenHeight / 4;
	labelResult->FontSize = CurrentConfiguration->ScreenHeight / 4;
	labelResult->FontName = "Resource/visitor1.ttf";
	labelResult->Background.a = 0;
	labelResult->Foreground.a = 0;
	Controls.push_back( labelResult );

	buttonQuit = new Button();
	buttonQuit->Background = al_map_rgba( 192, 255, 192, 0 );
	buttonQuit->Foreground = al_map_rgba( 0, 0, 0, 0 );
	buttonQuit->BorderHighlight = al_map_rgba( 220, 255, 220, 0 );
	buttonQuit->BorderLowlight = al_map_rgba( 96, 128, 96, 0 );
	buttonQuit->Text = "Return To Menu";
	buttonQuit->Position.X = CurrentConfiguration->ScreenWidth - 172;
	buttonQuit->Position.Y = CurrentConfiguration->ScreenHeight - (buttonQuit->FontSize * 2) - 12;
	buttonQuit->Size.X = 160;
	buttonQuit->Size.Y = buttonQuit->FontSize * 2;
	Controls.push_back( buttonQuit );
}

void Results::UninitialiseGui()
{
	delete cursor;
}
