
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"
#include "Game/camera.h"
#include "Game/map.h"
#include "Game/wave.h"

class Game : GuiStage // Stage
{
	private:
		Mouse*  cursor;

		Camera* view;
		bool viewDrag;

		Map* Level;
		std::list<Wave*> Waves;

  public:
		int TileSize;

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
