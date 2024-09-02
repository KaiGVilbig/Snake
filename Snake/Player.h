#pragma once
#include "Food.h"
#include "Body.h"


class Player {
	public:
		Player();
		Player(Coords);
		~Player();

		// Getters
		Coords getCoords();
		Coords getLastCoord();
		Direction getDirection();
		Direction getLastDirection();
		int getScore();
		int getHealth();
		int getSize();
		int getLength();
		bool getJustAte();

		void setJustAte(bool);

		void dealDamage();
		void eat();
		void changeDirection(Direction, Node*);
		void movePlayer(Direction, Node*);
		bool checkBoundry(int, int);
		bool checkIntersect(Node*);
		void resetPlayerLoc(int, int);
		bool checkEat(Coords);

	private:
		// Character
		int size = 40;
		Coords coord;
		Coords lastCoord;

		// Game
		int health = 100;
		int length = 0;
		int dmgAmount = 25;
		Direction currDir = RIGHT;
		Direction lastDirection = RIGHT;
		int score = 0;
		bool justAte = false;
};
