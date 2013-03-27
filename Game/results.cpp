
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
		backgroundAlpha += 4;
	} else {
		if( labelResult->Background.a < 1.0 )
		{
			labelResult->Background.a += 0.04;
			if( labelResult->Background.a > 1.0 )
				labelResult->Background.a = 1.0;
		}
		if( labelResult->Foreground.a < 1.0 )
		{
			labelResult->Foreground.a += 0.04;
			if( labelResult->Foreground.a > 1.0 )
				labelResult->Foreground.a = 1.0;
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
}

void Results::UninitialiseGui()
{
	delete cursor;
}
