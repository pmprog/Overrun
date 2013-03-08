
#pragma once

#include "control.h"

#ifndef ALLEGRO_EVENT_BUTTON_CLICK
#define ALLEGRO_EVENT_BUTTON_CLICK					ALLEGRO_GET_EVENT_TYPE('B', 't', 'c', 'k')
#endif

class ImageButton : public Control
{
	private:
		bool Depressed;

	public:
		ALLEGRO_BITMAP* ImageNormal;
		ALLEGRO_BITMAP* ImageDepressed;
		ALLEGRO_BITMAP* ImageDisabled;
		bool UnloadImagesOnDelete;


		ImageButton( ALLEGRO_BITMAP* normal );
		ImageButton( ALLEGRO_BITMAP* normal, ALLEGRO_BITMAP* depressed, ALLEGRO_BITMAP* disabled );
		virtual ~ImageButton();
		virtual bool Event(ALLEGRO_EVENT *e);
		virtual void Update();
		virtual void Render();

};