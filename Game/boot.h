
#pragma once

#include "../Framework/Core/main.h"
#include "GUI/mouse.h"
#include "GUI/panel.h"

class BootUp : Stage
{
	private:
		Mouse* cursor;
		Panel* testPanel;
		Panel* testPanel2;
		int r;
  public:
    // Stage control
    void Begin();
    void Pause();
    void Resume();
    void Finish();
    void Event(ALLEGRO_EVENT *e);
    void Update();
    void Render();
};
