
#include "vectorsprite.h"
#include "vectorcomponent.h"

void VectorSprite::Update()
{
	for( std::list<VectorComponent*>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		VectorComponent* c = (VectorComponent*)(*i);
		c->Update();
	}
}

void VectorSprite::Render( Vector2* Position, double ScreenRotation )
{
	for( std::list<VectorComponent*>::iterator i = Components.begin(); i != Components.end(); i++ )
	{
		VectorComponent* c = (VectorComponent*)(*i);
		c->Render( Position, ScreenRotation );
	}
}
