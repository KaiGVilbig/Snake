#include "Player.h"
#include <cstdlib>

Player::Player(){}

Player::Player(Coords coords) {
	coord = coords;
}

Player::~Player() {

}


Coords Player::getCoords() {
	return coord;
}

Direction Player::getDirection() {
	return currDir;
}

int Player::getScore() {
	return score;
}

int Player::getHealth() {
	return health;
}

int Player::getSize() {
	return size;
}


void Player::dealDamage() {
	health -= dmgAmount;
}

void Player::eat() {
	length += 1;
}

void Player::movePlayer(Direction direction) {

	switch (direction) {
		case UP:
			if (currDir != DOWN) {
				coord.top -= size;
				coord.bottom -= size;
				currDir = direction;
			}
			break;

		case DOWN:
			if (currDir != UP) {
				coord.top += size;
				coord.bottom += size;
				currDir = direction;
			}
			break;

		case LEFT:
			if (currDir != RIGHT) {
				coord.left -= size;
				coord.right -= size;
				currDir = direction;
			}
			break;

		case RIGHT:
			if (currDir != LEFT) {
				coord.left += size;
				coord.right += size;
				currDir = direction;
			}
			break;
	}
}

bool Player::checkBoundry(int windowWidth, int windowHeight) {
	bool inside = true;

	if (coord.top < 0 || coord.left < 0 || coord.bottom > windowHeight || coord.right > windowWidth) {
		inside = false;
	}

	return inside;
}

void Player::resetPlayerLoc(int newTop, int newLeft) {
	coord = { newTop, newLeft, newTop + size, newLeft + size };
	
	currDir = static_cast<Direction>(std::rand() % RIGHT);
}