
#include "boot.h"
#include "configure.h"
#include "mapdisp.h"

void BootUp::Begin()
{
	GuiStage::Begin();
	//al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
}

void BootUp::Pause()
{
}

void BootUp::Resume()
{

}

void BootUp::Finish()
{
	GuiStage::Finish();
	delete cursor;
}

void BootUp::Event(ALLEGRO_EVENT *e)
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
			}
			break;

		case ALLEGRO_EVENT_BUTTON_CLICK:
			if( e->user.data1 == (intptr_t)testButton )
				testPanel2->CornerCut = (testPanel2->CornerCut + 4) % 48;
			if( e->user.data1 == (intptr_t)testButtonD )
			{
				testButton->Enabled = !testButton->Enabled;
				testIBA->Enabled = !testIBA->Enabled;
				testIBB->Enabled = !testIBB->Enabled;
			}
			if( e->user.data1 == (intptr_t)testIBA )
				GameStack->Push( (Stage*)new MapDisp );
			break;
	}
}

void BootUp::Update()
{
	GuiStage::Update();
	cursor->Update();
}

void BootUp::Render()
{
	al_clear_to_color( al_map_rgb( 48, 48, 48 ) );

	GuiStage::Render();

	cursor->Render();
}

void BootUp::InitialiseGui()
{
	cursor = new Mouse();
	cursor->AllowBoxing = true;
	r = 0;
	testPanel = new Panel();
	testPanel->Position.X = 50;
	testPanel->Position.Y = 150;
	testPanel->Size.X = 200;
	testPanel->Size.Y = 60;
	testPanel->HasTitle = true;
	testPanel->Title = "Testing Panel";
	testPanel->FontSize = 24;
	Controls.push_back( testPanel );

	testPanel2 = new Panel();
	testPanel2->Position.X = 300;
	testPanel2->Position.Y = 150;
	testPanel2->Size.X = 200;
	testPanel2->Size.Y = 60;
	testPanel2->HasTitle = true;
	testPanel2->Title = "Testing Panel";
	testPanel2->Background = al_map_rgba( 128, 128, 255, 128 );
	testPanel2->Border = al_map_rgb( 128, 128, 255 );
	testPanel2->CornerCut = 0;
	testPanel2->FontSize = 24;
	Controls.push_back( testPanel2 );

	testButton = new Button();
	testButton->Position.X = 500;
	testButton->Position.Y = 100;
	testButton->Size.X = 140;
	testButton->Size.Y = 32;
	testButton->Text = "Test Button";
	testButton->FontSize = 16;
	testButton->BorderWidth = 2;
	Controls.push_back( testButton );

	testButtonD = new Button();
	testButtonD->Position.X = 500;
	testButtonD->Position.Y = 140;
	testButtonD->Size.X = 140;
	testButtonD->Size.Y = 32;
	testButtonD->Text = "Toggle";
	testButtonD->FontSize = 16;
	testButtonD->BorderWidth = 2;
	testButtonD->FontName = "Resource/forte.ttf";
	testButtonD->Background = al_map_rgb( 0, 128, 255 );
	testButtonD->BorderLowlight = al_map_rgb( 0, 24, 48 );
	testButtonD->BorderHighlight = al_map_rgb( 64, 192, 255 );
	Controls.push_back( testButtonD );


	testIBA = new ImageButton( al_load_bitmap( "Resource/button_normal.png" ) );
	testIBA->Position.X = 10;
	testIBA->Position.Y = 100;
	Controls.push_back( testIBA );

	testIBB = new ImageButton( al_load_bitmap( "Resource/button_normal.png" ), al_load_bitmap( "Resource/button_depress.png" ), al_load_bitmap( "Resource/button_disable.png" ) );
	testIBB->Position.X = 10;
	testIBB->Position.Y = 140;
	Controls.push_back( testIBB );

}

void BootUp::UninitialiseGui()
{
	Controls.remove( testPanel );
	delete testPanel;

	Controls.remove( testPanel2 );
	delete testPanel2;

	Controls.remove( testButton );
	delete testButton;
	Controls.remove( testButtonD );
	delete testButtonD;

	Controls.remove( testIBA );
	delete testIBA;
	Controls.remove( testIBB );
	delete testIBB;

}
