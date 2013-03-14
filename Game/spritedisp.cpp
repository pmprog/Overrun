
#include "spritedisp.h"
#include "configure.h"

void SpriteDisp::Begin()
{
	VectorComponent* vc;
	float* v;

	GuiStage::Begin();

	ScreenZoom = 1.0;
	ScreenRot = 0.0;

	circ = new VectorSprite();
	wave = new VectorSprite();

	for( int y = -24; y < 24; y += 6 )
	{
		v = (float*)malloc(sizeof(float) * 10);
		v[0] = -24; v[1] = y;
		v[2] = -12; v[3] = y + 4;
		v[4] = 0; v[5] = y;
		v[6] = 12; v[7] = y + 4;
		v[8] = 24; v[9] = y;
		vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYLINE, al_map_rgb( 255, 128, 128 ), v, 5 );
		vc->RotationPerFrame = 0.8;
		wave->Components.push_back( vc );
		free(v);
	}
	
	v = (float*)malloc(sizeof(float) * 4);
	v[0] = 0; v[1] = 0;
	v[2] = 24; v[3] = 12;
	circShield = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgba( 128, 192, 220, 128 ), v, 2 );
	circShield->DrawThickness = 2;
	circ->Components.push_back( circShield );
	free(v);

	/*
	v = (float*)malloc(sizeof(float) * 8);
	v[0] = -12; v[1] = -12;
	v[2] = 12; v[3] = -12;
	v[4] = 12; v[5] = 12;
	v[6] = -12; v[7] = 12;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYGON, al_map_rgb( 128, 128, 128 ), v, 4 );
	vc->RotationPerFrame = 2.0;
	vc->DrawThickness = 4;
	circ->Components.push_back( vc );
	free(v);
	*/
	v = (float*)malloc(sizeof(float) * 4);
	v[0] = 0; v[1] = 0;
	v[2] = 18; v[3] = 18;
	vc = new VectorComponent( VECTORSPRITE_COMPONENT_CIRCLE, al_map_rgb( 0, 220, 96), v, 2 );
	vc->DrawThickness = 4;
	circ->Components.push_back( vc );
	free(v);

	for( int i = 0; i < 360; i += 20 )
	{
		v = (float*)malloc(sizeof(float) * 4);
		v[0] = 0; v[1] = -18;
		v[2] = 0; v[3] = -12;
		vc = new VectorComponent( VECTORSPRITE_COMPONENT_POLYLINE, al_map_rgb( 0, 220, 96), v, 2 );
		vc->DrawThickness = 2;
		vc->Rotation = i;
		vc->RotationPerFrame = 1.0;
		circ->Components.push_back( vc );
		free(v);
	}


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
	delete circ;
	delete wave;
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
				case ALLEGRO_KEY_W:
					circShield->ColourChangePerFrame.a = -0.1;
					break;
				case ALLEGRO_KEY_S:
					circShield->ColourChangePerFrame.a = 0.0;
					break;
				case ALLEGRO_KEY_X:
					circShield->ColourChangePerFrame.a = +0.1;
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
	circ->Update();
	wave->Update();
	GuiStage::Update();
	cursor->Update();
}

void SpriteDisp::Render()
{
	Vector2 pos;

	al_clear_to_color( al_map_rgb( 0, 0, 0 ) );

	pos.X = 200;
	pos.Y = 200;
	circ->Render( &pos, ScreenRot, ScreenZoom );
	pos.X = 350;
	pos.Y = 200;
	wave->Render( &pos, ScreenRot, ScreenZoom );

	GuiStage::Render();
	cursor->Render();
}

void SpriteDisp::InitialiseGui()
{
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
