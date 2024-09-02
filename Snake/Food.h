#pragma once
#include "Enums.h"
#include "Coords.h"

class Food {
	public:
		Food();
		Food(int, int);
		~Food();

		Coords getCoord();
		bool getSpawned();
		int getSize();
		Models getModel();

		void newCoords(int, int, Models);

	private:
		Coords coord;
		int size = 38;
		bool spawned = false;
		Models model;
};