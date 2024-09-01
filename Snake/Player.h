#pragma once

enum Direction { UP, DOWN, LEFT, RIGHT };
struct Coords { int top; int left; int bottom; int right; };

class Player {
	public:
		Player();
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
		int top = 10;
		int left = 10;
		int bottom = top + size;
		int right = left + size;

		// Game
		int health = 100;
		int length = 1;
		int dmgAmount = 25;
		Direction currDir = RIGHT;
		int score = 0;
};
