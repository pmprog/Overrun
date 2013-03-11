
#pragma once

#include "../Framework/Core/main.h"
#include "../Framework/GUI/gui.h"

#define TILE_SIZE			48

class MapDisp : GuiStage // Stage
{
	private:
		Mouse* cursor;
		Button* testButton;

		uint8_t* MapData;

		Vector2 CameraPosition;
		Vector2 CameraPositionDestination;
		double CameraZoom;
		double CameraZoomDestination;
		double CameraRotation;
		double CameraRotationDestination;
		bool CameraDrag;

		int MapWidth;
		int MapHeight;

		int frameIndex;
		

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
