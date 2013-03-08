
#pragma once

#include <list>
#include "../Core/stage.h"
#include "control.h"

class GuiStage : public Stage
{
	public:
		std::list<Control*> Controls;

		virtual void Begin()
		{
			InitialiseGui();
		};

		virtual void Finish()
		{
			InitialiseGui();
		};

		virtual void Event(ALLEGRO_EVENT *e)
		{
			for( std::list<Control*>::reverse_iterator i = Controls.rbegin(); i != Controls.rend(); i++ )
			{
				Control* c = (Control*)(*i);
				if( c->Event( e ) )
				{
					e->any.timestamp = -1;
					break;
				}
			}
		};

    virtual void Update()
		{
			for( std::list<Control*>::iterator i = Controls.begin(); i != Controls.end(); i++ )
			{
				Control* c = (Control*)(*i);
				c->Update();
			}
		};

    virtual void Render()
		{
			for( std::list<Control*>::iterator i = Controls.begin(); i != Controls.end(); i++ )
			{
				Control* c = (Control*)(*i);
				c->Render();
			}
		};

		virtual void InitialiseGui() = 0;
		virtual void UninitialiseGui() = 0;
};