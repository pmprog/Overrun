
#include "spritedisp.h"
#include "configure.h"

void SpriteDisp::Begin()
{
	GuiStage::Begin();

	ScreenZoom = 1.0;
	ScreenRot = 0.0;
}

void SpriteDisp::Pause()
{
}

void SpriteDisp::Resume()
{

}

void SpriteDisp::Finish()
{
	GuiStage::Finish();
}

void SpriteDisp::Event(ALLEGRO_EVENT *e)
{
	GuiStage::Event( e );
	if( e->any.timestamp == -1 )
		return;

	switch( e->type )
	{
		case ALLEGRO_EVENT_KEY_DOWN:
			switch( e->keyboard.keycode )
			{
				case ALLEGRO_KEY_ESCAPE:
					GameStack->Pop();
					break;
				case ALLEGRO_KEY_LEFT:
					ScreenRot -= 10.0;
					break;
				case ALLEGRO_KEY_RIGHT:
					ScreenRot += 10.0;
					break;
				case ALLEGRO_KEY_UP:
					ScreenRot -= 30.0;
					break;
				case ALLEGRO_KEY_DOWN:
					ScreenRot += 30.0;
					break;
				case ALLEGRO_KEY_A:
					if( ScreenZoom > 0.1 )
						ScreenZoom -= 0.1;
					break;
				case ALLEGRO_KEY_Z:
					if( ScreenZoom < 4.0 )
						ScreenZoom += 0.1;
					break;
			}
			if( ScreenRot < 0.0 )
				ScreenRot += 360.0;
			if( ScreenRot >= 360.0 )
				ScreenRot -= 360.0;
			break;

		case ALLEGRO_EVENT_BUTTON_CLICK:
			if( e->user.data1 == (intptr_t)testButton )
				delete GameStack->Pop();
			break;
	}
}

void SpriteDisp::Update()
{
	GuiStage::Update();
	cursor->Update();
}

void SpriteDisp::Render()
{
	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	GuiStage::Render();
	cursor->Render();
}

void SpriteDisp::InitialiseGui()
{
	cam = new Camera();

	cursor = new Mouse();
	cursor->AllowBoxing = true;

	testButton = new Button();
	testButton->Position.X = 4;
	testButton->Position.Y = 4;
	testButton->Size.X = 200;
	testButton->Size.Y = 32;
	testButton->Text = "Quit";
	testButton->FontSize = 16;
	testButton->BorderWidth = 2;
	Controls.push_back( testButton );
}

void SpriteDisp::UninitialiseGui()
{
	Controls.remove( testButton );
	delete testButton;

	delete cursor;
}
