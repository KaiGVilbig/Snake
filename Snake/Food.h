#pragma once

struct Coords { int top; int left; int bottom; int right; };

class Food {
	public:
		Food();
		Food(int, int);
		~Food();

		Coords getCoord();
		bool getSpawned();
		int getSize();

		void newCoords(int, int);

	private:
		Coords coord;
		int size = 10;
		bool spawned = false;
};