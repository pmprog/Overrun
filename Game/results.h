
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"

#ifndef Game
class Game;
#endif

class Results : GuiStage // Stage
{
	private:
		Mouse*  cursor;
		Game*		gameStage;
		bool		wasVictory;

		int			backgroundAlpha;
		Label*	labelResult;
		Button* buttonQuit;

  public:
		Results( Game* curGame, bool Victory );
		~Results();

    // Stage control
    void Begin();
    void Pause();
    void Resume();
    void Finish();
    void Event(ALLEGRO_EVENT *e);
    void Update();
    void Render();

		void InitialiseGui();
		void UninitialiseGui();
};
