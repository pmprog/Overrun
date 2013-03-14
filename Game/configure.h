
#pragma once

#define _config
#include "../Framework/Core/main.h"
#include "../Framework/Resource/configfile.h"

class Configuration : Stage
{
	public:
		Configuration();
		~Configuration();

		// Settings
		void InitSettings();
		void LoadSettings();
		void SaveSettings();
		int ScreenWidth;
		int ScreenHeight;
		bool FullScreen;
		bool ForceResolution;
		bool WasLoaded;


		// Config Screen
    void Begin();
    void Pause();
    void Resume();
    void Finish();
    void Event(ALLEGRO_EVENT *e);
    void Update();
    void Render();

		ALLEGRO_FONT* configFont;

};