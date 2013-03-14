
#include "configure.h"

Configuration::Configuration()
{
	LoadSettings();
}

Configuration::~Configuration()
{
}

void Configuration::InitSettings()
{
	int curDev = al_get_new_display_adapter();
	ALLEGRO_MONITOR_INFO curMon;

	if( al_get_monitor_info(curDev, &curMon) )
	{
		ScreenWidth = curMon.x2 - curMon.x1;
		ScreenHeight = curMon.y2 - curMon.y1;
#ifdef _DEBUG
		FullScreen = false;
#else
		FullScreen = true;
#endif
	} else {
		ScreenWidth = 1024;
		ScreenHeight = 600;
		FullScreen = false;
	}
}

void Configuration::LoadSettings()
{
	ALLEGRO_FILE* fileHnd;

	fileHnd = al_fopen( "settings.cfg", "r" );
	if( fileHnd == 0 )
	{
		InitSettings();
	} else {
		al_fclose( fileHnd );
		ConfigFile* cfg;
		cfg = new ConfigFile( "settings.cfg" );
		cfg->GetIntegerValue( "ScreenWidth", &ScreenWidth );
		cfg->GetIntegerValue( "ScreenHeight", &ScreenHeight );
		cfg->GetBooleanValue( "ForceResolution", &ForceResolution );
		cfg->GetBooleanValue( "Fullscreen", &FullScreen );
		delete cfg;
		WasLoaded = true;
	}
}

void Configuration::SaveSettings()
{
	ConfigFile* cfg;
	cfg = new ConfigFile();
	cfg->SetIntegerValue( "ScreenWidth", ScreenWidth );
	cfg->SetIntegerValue( "ScreenHeight", ScreenHeight );
	cfg->SetBooleanValue( "ForceResolution", &ForceResolution );
	cfg->SetBooleanValue( "Fullscreen", FullScreen );
	cfg->Save( "settings.cfg" );
	delete cfg;
}


void Configuration::Begin()
{
}

void Configuration::Pause()
{
}

void Configuration::Resume()
{
}

void Configuration::Finish()
{
}

void Configuration::Event(ALLEGRO_EVENT *e)
{
}

void Configuration::Update()
{
}

void Configuration::Render()
{
}
