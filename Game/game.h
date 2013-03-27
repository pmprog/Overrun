
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
		Camera* overlay;
		bool viewDrag;

		Panel*	overlayNextWavePanel;
		Label*	overlayNextWaveClass;
		Label*	overlayNextWaveHealth;
		Label*	overlayNextWaveShield;
		Label*	overlayNextWaveTime;
		Unit*		overlayNextWaveUnit;
		Button*	overlayNextWaveShowHide;
		int			overlayNextWaveShowHideTargetHeight;

		Map* Level;
		std::list<Wave*>				Waves;

		ALLEGRO_TIMER* timerDelay;
		ALLEGRO_TIMER* timerSpawn;

  public:
		int TileSize;

		~Game();

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

		void NextWaveInitGui();
		void NextWaveUpdate();

		void CheckEndOfGameConditions();
};
