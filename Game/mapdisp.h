
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"
#include "camera.h"

class MapDisp : GuiStage // Stage
{
	private:
		Mouse*  cursor;
		Button* testButton;
		Panel*  nextWave;

		Camera* Cam;
		bool CameraDrag;
		int TileSize;

		int MapWidth;
		int MapHeight;
		uint8_t* MapData;

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

		int GetMapElement( int X, int Y );
		void DrawGround( int X, int Y, Vector2 BasePoints[] );
};
