
#pragma once

#include "../../Framework/Core/main.h"

class Control
{

	public:
		Vector2 Position;
		Vector2 Size;
		bool Enabled;
		int Z;

		std::string FontName;
		int FontSize;
		int FontFlags;

		virtual void Event(ALLEGRO_EVENT *e) = 0;
		virtual void Render() = 0;
		virtual void Update() = 0;

};