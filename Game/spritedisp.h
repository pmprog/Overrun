
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"
#include "Sprites/vectorsprite.h"
#include "Sprites/vectorcomponent.h"

#define TILE_SIZE			48

class SpriteDisp : GuiStage // Stage
{
	private:
		Mouse* cursor;
		Button* testButton;
		double ScreenRot;
		double ScreenZoom;

		VectorSprite* circ;
		VectorSprite* wave;
		

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
