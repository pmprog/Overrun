
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"
#include "Game/wave.h"
#include "Units/spinner.h"

#define TILE_SIZE			48

class SpriteDisp : GuiStage // Stage
{
	private:
		Camera* cam;
		Mouse* cursor;
		Button* testButton;
		double ScreenRot;
		double ScreenZoom;

		Wave* spWave;
		Spinner* spUnit;

  public:
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
