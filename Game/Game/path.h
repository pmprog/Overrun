
#pragma once

#include "../../Framework/Core/main.h"

class Path
{
	private:
		std::vector<Vector2*> points;

	public:
		Path( ConfigFile* LevelData, int PathNumber );
		~Path();

		int GetPathLength();
		Vector2* GetPathDestination( int Index );
};