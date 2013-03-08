
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"

class BootUp : GuiStage // Stage
{
	private:
		Mouse* cursor;
		Panel* testPanel;
		Panel* testPanel2;
		Button* testButton;
		Button* testButtonD;
		ImageButton* testIBA;
		ImageButton* testIBB;
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

		void InitialiseGui();
		void UninitialiseGui();
};
