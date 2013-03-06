
#pragma once

#include "../Framework/Core/main.h"
#include "GUI/mouse.h"

class BootUp : Stage
{
	private:
		Mouse* cursor;
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
