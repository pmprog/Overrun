
#pragma once

#include "../../Framework/Core/main.h"

#ifndef ControlHost
class ControlHost;
#endif

class Control
{

	public:
		Vector2 Position;
		Vector2 Size;
		bool Enabled;
		bool Visible;
		int Z;
		ControlHost* Parent;

		std::string FontName;
		int FontSize;
		int FontFlags;

		virtual void Event(ALLEGRO_EVENT *e) = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;

};