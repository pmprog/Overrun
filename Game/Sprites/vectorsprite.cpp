
#include "vectorsprite.h"
#include "vectorcomponent.h"

VectorSprite::~VectorSprite()
{
	while( !Components.empty() )
	{
		delete Components.back();
		Components.pop_back();
	}
}

void VectorSprite::Update()
{
	for( std::list<VectorComponent*>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		VectorComponent* c = (VectorComponent*)(*i);
		c->Update();
	}
}

void VectorSprite::Render( Vector2* Position, Camera* View )
{
	for( std::list<VectorComponent*>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		VectorComponent* c = (VectorComponent*)(*i);
		c->Render( Position, View->Rotation, View->Zoom * (View->PixelsPerUnit / 2) );
	}
}
