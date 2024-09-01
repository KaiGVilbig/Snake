#pragma once
#include "Food.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

class Player {
	public:
		Player();
		Player(Coords);
		~Player();

		// Getters
		Coords getCoords();
		Direction getDirection();
		int getScore();
		int getHealth();
		int getSize();

		void dealDamage();
		void eat();
		void movePlayer(Direction);
		bool checkBoundry(int, int);
		void resetPlayerLoc(int, int);

	private:
		// Character
		int size = 20;
		Coords coord;

		// Game
		int health = 100;
		int length = 1;
		int dmgAmount = 25;
		Direction currDir = RIGHT;
		int score = 0;
};
